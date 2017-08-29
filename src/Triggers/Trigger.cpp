#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Utils/TypeUtils.hpp>

namespace obe
{
    namespace Triggers
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

        void Trigger::registerEnvironment(unsigned int envIndex, const std::string& callbackName)
        {
            m_registeredEnvs.emplace_back(envIndex, callbackName);
            std::cout << "Registering : " << envIndex << std::endl;
            Script::ScriptEngine["__ENVIRONMENTS"][envIndex]["LuaCore"]["FTCP"][this->getNamespace() + "__" + this->getGroup() + "__" + m_name] = kaguya::NewTable();
        }

        void Trigger::unregisterEnvironment(unsigned envIndex)
        {
            m_registeredEnvs.erase(std::remove_if(m_registeredEnvs.begin(), m_registeredEnvs.end(), 
                [&envIndex](const std::pair<unsigned int, std::string>& env) { return env.first == envIndex; }
            ), m_registeredEnvs.end());
        }

        void Trigger::execute() const
        {
            unsigned envAmount = m_registeredEnvs.size();
            for (unsigned int i = 0; i < envAmount; i++)
            {
                // Problem when GameObjects are deleted <REVISION>
                std::pair<unsigned int, std::string> rEnv = m_registeredEnvs[i];
                Script::ScriptEngine["ExecuteStringOnEnv"]("LuaCore.FuncInjector(" + rEnv.second + ", \"" + this->getTriggerLuaTableName() + "\")", rEnv.first);
                //Script::ScriptEngine["__ENVIRONMENTS"][rEnv.first]["LuaCore"]["FuncInjector"](rEnv.second, this->getTriggerLuaTableName());
                Script::ScriptEngine["__ENVIRONMENTS"][rEnv.first]["LuaCore"]["FTCP"][this->getTriggerLuaTableName()] = kaguya::NewTable();
            }
        }

        void Trigger::pushParameterFromLua(const std::string& name, kaguya::LuaRef parameter)
        {
            for (auto& rEnv : m_registeredEnvs)
            {
                Script::ScriptEngine["__ENVIRONMENTS"][rEnv.first]["LuaCore"]["FTCP"][this->getTriggerLuaTableName()][name] = parameter;
            }
        }
    }
}
