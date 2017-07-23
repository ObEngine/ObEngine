#pragma once

#include <queue>

#include <kaguya/kaguya.hpp>

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
            std::vector<ParameterTable> m_triggerParameters;
            bool m_enabled = false;
            bool m_toEnable = false;
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
            void clear();

            template <class T>
            void execute(kaguya::State& lua, T callback);
        };

        /**
         * \brief Injects the current ParameterTable contained in a Trigger to a Lua VM
         * \param parameters Reference to the Trigger ParameterTable
         * \param lua Lua VM where to inject the parameters
         */
        void injectParameters(const std::string& triggerName, ParameterTable& parameters, kaguya::State& lua);

        template <typename P>
        void Trigger::pushParameter(const std::string& name, P parameter)
        {
            std::cout << "Pushed Parameter " << name << " at " << this->getNamespace() << "." << this->getGroup() << "." << m_name << std::endl;
            m_triggerParameters.back()[name] = std::pair<std::string, Types::Any>(Utils::Type::getClassType<P>(), Types::Any(parameter));
        }

        template <class T>
        void Trigger::execute(kaguya::State& lua, T callback)
        {
            unsigned int index = 0;
            for (ParameterTable& pTable : m_triggerParameters)
            {
                injectParameters(m_name, pTable, lua);
                T(index++);
            }
        }
    }
}
