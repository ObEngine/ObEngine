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

        void Trigger::registerState(kaguya::State* state)
        {
            m_registeredStates.push_back(state);
            (*state)["LuaCore"]["FTCP"][this->getNamespace() + "__" + this->getGroup() + "__" + m_name] = kaguya::NewTable();
            (*state)["LuaCore"]["FTCP"][this->getNamespace() + "__" + this->getGroup() + "__" + m_name][m_stackSize] = kaguya::NewTable();
        }

        void Trigger::prepareNewCall()
        {
            m_stackSize++;
            for (auto& registeredState : m_registeredStates)
            {
                (*registeredState)["LuaCore"]["FTCP"][this->getTriggerLuaTableName()][m_stackSize] = kaguya::NewTable();
            }
        }

        void Trigger::execute(kaguya::State* lua, const std::string& funcName) const
        {
            for (unsigned int i = 1; i < m_stackSize; i++)
            {
                (*lua)["LuaCore"]["FuncInjector"](funcName, this->getTriggerLuaTableName(), i);
            }
        }

        void Trigger::clear()
        {
            m_stackSize = 1;
            for (auto& registeredState : m_registeredStates)
            {
                (*registeredState)["LuaCore"]["FTCP"][this->getTriggerLuaTableName()] = kaguya::NewTable();
                (*registeredState)["LuaCore"]["FTCP"][this->getTriggerLuaTableName()][1] = kaguya::NewTable();
            }
        }

        void Trigger::pushParameterFromLua(const std::string& name, kaguya::LuaRef parameter)
        {
            for (auto& registeredState : m_registeredStates)
            {
                // Future Trigger Call Parameters
                (*registeredState)["LuaCore"]["FTCP"][this->getTriggerLuaTableName()][m_stackSize][name] = parameter;
            }
        }
    }
}
