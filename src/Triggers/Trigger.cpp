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


        Trigger::Trigger(TriggerGroup* parent, const std::string& name, bool startState, bool permanent)
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

        void Trigger::registerState(kaguya::State* state, const std::string& callbackName)
        {
            m_registeredStates.emplace_back(state, callbackName);
            (*state)["LuaCore"]["FTCP"][this->getNamespace() + "__" + this->getGroup() + "__" + m_name] = kaguya::NewTable();
        }

        void Trigger::execute() const
        {
            for (auto& rState : m_registeredStates)
            {
                (*rState.first)["LuaCore"]["FuncInjector"](rState.second, this->getTriggerLuaTableName());
                (*rState.first)["LuaCore"]["FTCP"][this->getNamespace() + "__" + this->getGroup() + "__" + m_name] = kaguya::NewTable();
            }
        }

        void Trigger::pushParameterFromLua(const std::string& name, kaguya::LuaRef parameter)
        {
            for (auto& registeredState : m_registeredStates)
            {
                (*registeredState.first)["LuaCore"]["FTCP"][this->getTriggerLuaTableName()][name] = parameter;
            }
        }
    }
}
