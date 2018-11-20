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
        Script::ScriptEngine["__TRIGGER_ARG_TABLE"][this->getTriggerLuaTableName()] = kaguya::NewTable();
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
        Debug::Log->trace("<Trigger> Registering Lua Environment {0} in Trigger {1} associated to callback {2}", envIndex, m_name, callbackName);
        m_registeredEnvs.emplace_back(envIndex, callbackName, envActive);
        
        Script::ScriptEngine["__ENVIRONMENTS"][envIndex]["LuaCore"]["TriggerList"][this->getTriggerLuaTableName()] = kaguya::NewTable();
        Script::ScriptEngine["__ENVIRONMENTS"][envIndex]["LuaCore"]["TriggerList"][this->getTriggerLuaTableName()]["callback"] = callbackName;
    }

    void Trigger::unregisterEnvironment(unsigned int envIndex)
    {
        Debug::Log->trace("<Trigger> Unregistering Lua Environment {0} from Trigger {1}", envIndex, m_name);
        Script::ScriptEngine["__ENVIRONMENTS"][envIndex]["LuaCore"]["TriggerList"][this->getTriggerLuaTableName()] = kaguya::NilValue();
        if (m_currentlyTriggered)
        {
            m_envsToRemove.push_back(envIndex);
        }
        else
        {
            m_registeredEnvs.erase(std::remove_if(m_registeredEnvs.begin(), m_registeredEnvs.end(),
                [&envIndex](TriggerEnv& env) { return env.envIndex == envIndex; }
            ), m_registeredEnvs.end());
        }
    }

    void Trigger::execute()
    {
        m_currentlyTriggered = true;
        Debug::Log->trace("<Trigger> Executing Trigger {0}", m_name);
        const unsigned int envAmount = m_registeredEnvs.size();
        for (unsigned int i = 0; i < envAmount; i++)
        {
            auto& rEnv = m_registeredEnvs[i];
            if (*rEnv.envActive)
            {
                Debug::Log->trace("<Trigger> Calling Trigger Callback {0} on Lua Environment {1} from Trigger {2}", rEnv.callbackName, rEnv.envIndex, m_name);
                Script::ScriptEngine("EnvFuncInjector(" + std::to_string(rEnv.envIndex) + ", \"" + this->getTriggerLuaTableName() + "\")");
            }
        }
        Script::ScriptEngine["__TRIGGER_ARG_TABLE"][this->getTriggerLuaTableName()] = kaguya::NewTable();
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
        Script::ScriptEngine["__TRIGGER_ARG_TABLE"][this->getTriggerLuaTableName()][name] = parameter;
    }
}
