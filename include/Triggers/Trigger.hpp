#pragma once

#include <queue>

#include <kaguya/kaguya.hpp>

#include <Script/GlobalState.hpp>
#include <Types/Any.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/TypeUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Triggers
    {
        class TriggerGroup;

        using ParameterTable = std::map<std::string, std::pair<std::string, Types::Any>>;
        /**
         * \brief A Class that does represents a triggerable event
         * @Bind
         */
        class Trigger
        {
        private:
            TriggerGroup* m_parent;
            std::string m_name;
            std::vector<std::pair<unsigned int, std::string>> m_registeredEnvs;
            bool m_enabled = false;
            friend class TriggerGroup;
            friend class TriggerDatabase;
        protected:
            /**
             * \brief Pushes a parameter to the Trigger
             * \tparam P Type of the Parameter to push
             * \param name Name of the Parameter
             * \param parameter Value of the Parameter
             */
            template <typename P>
            void pushParameter(const std::string& name, P parameter);
            void pushParameterFromLua(const std::string& name, kaguya::LuaRef parameter);
            std::string getTriggerLuaTableName() const;
        public:
            /**
             * \brief Creates a new Trigger
             * \param parent Pointer to the parent TriggerGroup
             * \param name Name of the Trigger
             * \param startState State of the Trigger when created (enabled / disabled)
             * \param permanent If equals to true, when the Trigger will be enabled it will stay enabled
             */
            explicit Trigger(TriggerGroup* parent, const std::string& name, bool startState = false);
            /**
             * \brief Get the State of the Trigger (enabled / disabled)
             * \return true if the Trigger is enabled, false otherwise
             */
            bool getState() const;
            /**
             * \brief Get the name of the TriggerGroup which is the parent of the Trigger
             * \return A std::string containing the name of the TriggerGroup which is the parent of the Trigger
             */
            std::string getGroup() const;
            /**
             * \brief Get the name of the Trigger
             * \return A std::string containing the name of the Trigger
             */
            std::string getName() const;
            /**
             * \brief Get the name of the namespace of the parent (TriggerGroup) of the Trigger
             * \return A std::string containing the name of the namespace of the parent (TriggerGroup) of the Trigger
             */
            std::string getNamespace() const;
            /**
             * \brief Registers a Lua State that will be triggered
             * \param envIndex Index of the Lua Env to register
             */
            void registerEnvironment(unsigned int envIndex, const std::string& callbackName);
            /**
             * \brief Triggers callbacks
             */
            void execute() const;
        };

        template <typename P>
        void Trigger::pushParameter(const std::string& name, P parameter)
        {
            for (auto& rEnv : m_registeredEnvs)
            {
                // Future Trigger Call Parameters
                Script::ScriptEngine["__ENVIRONMENTS"][rEnv.first]["LuaCore"]["FTCP"][this->getTriggerLuaTableName()][name] = parameter;
            }
        }
    }
}
