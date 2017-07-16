#pragma once

#include <kaguya/kaguya.hpp>

#include <Types/Any.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Triggers
    {
        class TriggerGroup;
        /**
         * \brief A Class that does represents a triggerable event
         */
        class Trigger
        {
        private:
            TriggerGroup* m_parent;
            std::string m_name;
            std::map<std::string, std::pair<std::string, Types::Any>> m_triggerParameters;
            bool m_enabled = false;
            bool m_toEnable = false;
            bool m_toDisable = false;
            bool m_permanent = false;
            void clearParameters();
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
            void pushParameter(std::string name, P parameter);
        public:
            /**
             * \brief Creates a new Trigger
             * \param parent Pointer to the parent TriggerGroup
             * \param name Name of the Trigger
             * \param startState State of the Trigger when created (enabled / disabled)
             * \param permanent If equals to true, when the Trigger will be enabled it will stay enabled
             */
            explicit Trigger(TriggerGroup* parent, const std::string& name, bool startState = false, bool permanent = false);
            /**
             * \brief Get the State of the Trigger (enabled / disabled)
             * \return true if the Trigger is enabled, false otherwise
             */
            bool getState() const;
            /**
             * \brief Get if the Trigger is in permanent state (stays enabled)
             * \return true is the Trigger is permanent, false otherwise
             */
            bool isPermanent() const;
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
            std::map<std::string, std::pair<std::string, Types::Any>>* getParameters();
        };

        /**
         * \brief Injects the parameter contained in a Trigger to a Lua VM
         * \param trigger Reference to the Trigger
         * \param lua Lua VM where to inject the parameters
         * \return Empty string if everything went fine, name of the parameter that caused a problem otherwise
         */
        std::string injectParameters(Trigger& trigger, kaguya::State& lua);

        template <typename P>
        void Trigger::pushParameter(std::string name, P parameter)
        {
            std::vector<std::string> splittedTypeName = Utils::String::split(typeid(parameter).name(), " ");
            std::string datatype = Utils::Vector::join(splittedTypeName, "", 1);
            m_triggerParameters[name] = std::pair<std::string, Types::Any>(datatype, Types::Any(parameter));
        }
    }
}