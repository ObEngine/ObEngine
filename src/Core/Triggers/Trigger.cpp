#include <Script/GameObject.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Utils/TypeUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Triggers
{
    std::string Trigger::getTriggerLuaTableName() const
    {
        return this->getNamespace() + "__" + this->getGroup() + "__" + m_name;
    }


    Trigger::Trigger(TriggerGroup* parent, const std::string& name, bool startState)
    {
        m_name = name;
        m_parent = parent;
        m_enabled = startState;
        m_fullName = this->getNamespace() + "." + this->getGroup() + "." + m_name;
        Script::ScriptEngine["LuaCore"]["TriggerArgTable"][this->getTriggerLuaTableName()] = kaguya::NewTable();
        Debug::Log->trace("<Trigger> Creating Trigger {0} @{1}", m_fullName, fmt::ptr(this));
    }

    bool Trigger::getState() const
    {
        return m_enabled;
    }

    std::string Trigger::getGroup() const
    {
        return m_parent->getName();
    }

    std::string Trigger::getName() const
    {
        return m_name;
    }

    std::string Trigger::getNamespace() const
    {
        return m_parent->getNamespace();
    }

    void Trigger::registerEnvironment(unsigned int envIndex, const std::string& callbackName, bool* envActive)
    {
        Debug::Log->trace(
            "<Trigger> Registering Lua Environment {0} in Trigger {1} associated to callback {2}", 
            envIndex, 
            m_name, 
            callbackName);
        m_registeredEnvs.emplace_back(envIndex, callbackName, envActive);
        
        Script::ScriptEngine
            ["__ENVIRONMENTS"]
            [envIndex]
            ["__TRIGGERS"]
            [this->getTriggerLuaTableName()] = kaguya::NewTable();
        Script::ScriptEngine
            ["__ENVIRONMENTS"]
            [envIndex]
            ["__TRIGGERS"]
            [this->getTriggerLuaTableName()]
            ["callback"] = callbackName;
        if (m_onRegisterCallback)
        {
            Debug::Log->trace("<Trigger> Calling onRegister callback of Trigger {0}", m_fullName);
            m_onRegisterCallback(m_registeredEnvs.back());
        } 
    }

    void Trigger::unregisterEnvironment(unsigned int envIndex)
    {
        Debug::Log->trace(
            "<Trigger> Unregistering Lua Environment {0} from Trigger {1}", 
            envIndex, 
            m_fullName);
        Script::ScriptEngine
            ["__ENVIRONMENTS"]
            [envIndex]
            ["__TRIGGERS"]
            [this->getTriggerLuaTableName()] = kaguya::NilValue();
        for (const TriggerEnv& triggerEnv : m_registeredEnvs)
        {
            if (triggerEnv.envIndex == envIndex)
            {
                if (m_onUnregisterCallback)
                {
                    Debug::Log->trace(
                        "<Trigger> Calling onUnregister callback of Trigger {0}", 
                        m_fullName);
                    m_onUnregisterCallback(triggerEnv);
                }
            }
        }
        if (m_currentlyTriggered)
        {
            m_envsToRemove.push_back(envIndex);
        }
        else
        {
            m_registeredEnvs.erase(std::remove_if(m_registeredEnvs.begin(), m_registeredEnvs.end(),
                [&envIndex](TriggerEnv& env) { 
                    return env.envIndex == envIndex; 
                }
            ), m_registeredEnvs.end());
        }
    }

    void Trigger::execute()
    {
        m_currentlyTriggered = true;
        Debug::Log->trace("<Trigger> Executing Trigger {0}", m_fullName);
        const unsigned int envAmount = m_registeredEnvs.size();
        for (unsigned int i = 0; i < envAmount; i++)
        {
            auto& rEnv = m_registeredEnvs[i];
            if (*rEnv.envActive)
            {
                Debug::Log->trace(
                    "<Trigger> Calling Trigger Callback {0} on Lua Environment {1} from Trigger {2}", 
                    rEnv.callbackName, 
                    rEnv.envIndex, 
                    m_fullName);
                Script::ScriptEngine(
                    "LuaCore.EnvFuncInjector(" 
                    + std::to_string(rEnv.envIndex) 
                    + ", \"" + this->getTriggerLuaTableName() 
                    + "\")"
                );
            }
        }
        Script::ScriptEngine
            ["LuaCore"]
            ["TriggerArgTable"]
            [this->getTriggerLuaTableName()] = kaguya::NewTable();
        if (!m_envsToRemove.empty())
        {
            for (unsigned int envToRemove : m_envsToRemove)
            {
                m_registeredEnvs.erase(std::remove_if(m_registeredEnvs.begin(), m_registeredEnvs.end(),
                    [&envToRemove](TriggerEnv& env) { return env.envIndex == envToRemove; }
                ), m_registeredEnvs.end());
            }
        }
        m_currentlyTriggered = false;
    }

    void Trigger::pushParameterFromLua(const std::string& name, const kaguya::LuaRef& parameter) const
    {
        Debug::Log->trace("<Trigger> Pushing parameter {0} to Trigger {1} (From Lua)", name, m_fullName);
        Script::ScriptEngine["LuaCore"]["TriggerArgTable"][this->getTriggerLuaTableName()][name] = parameter;
    }

    void Trigger::onRegister(std::function<void(const TriggerEnv&)> callback)
    {
        Debug::Log->trace("<Trigger> Add onRegister callback to Trigger {0}", m_fullName);
        m_onRegisterCallback = callback;

    }

    void Trigger::onUnregister(std::function<void(const TriggerEnv&)> callback)
    {
        Debug::Log->trace("<Trigger> Add onUnregister callback to Trigger {0}", m_fullName);
        m_onUnregisterCallback = callback;
    }
}
