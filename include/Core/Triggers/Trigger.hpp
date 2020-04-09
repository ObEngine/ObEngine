#pragma once

#include <Debug/Logger.hpp>
#include <sol/sol.hpp>
#include <utility>

namespace obe::Triggers
{
    class TriggerGroup;

    class TriggerEnv
    {
    public:
        std::string id;
        sol::environment environment;
        std::string callback;
        bool* active = nullptr;
        sol::protected_function call;
        TriggerEnv(std::string id, sol::environment environment, std::string callback,
            bool* active)
            : id(std::move(id))
            , environment(std::move(environment))
            , callback(std::move(callback))
            , active(active)
        {
        }
    };

    /**
     * \brief A Class that does represents a triggerable event
     */
    class Trigger
    {
    private:
        TriggerGroup& m_parent;
        std::string m_name;
        std::string m_fullName;
        std::vector<TriggerEnv> m_registeredEnvs;
        std::vector<sol::environment> m_envsToRemove;
        bool m_currentlyTriggered = false;
        bool m_enabled = false;
        std::function<void(const TriggerEnv&)> m_onRegisterCallback;
        std::function<void(const TriggerEnv&)> m_onUnregisterCallback;
        sol::state_view m_lua;
        friend class TriggerGroup;
        friend class TriggerManager;

    protected:
        /**
         * \brief Pushes a parameter to the Trigger
         * \tparam P Type of the Parameter to push
         * \param name Name of the Parameter
         * \param parameter Value of the Parameter
         */
        template <typename P> void pushParameter(const std::string& name, P parameter);
        /**
         * \brief Pushes a parameter on the Trigger from a Lua VM
         * \param name Name of the Parameter to push
         * \param parameter Value of the parameter (LuaRef can be anything)
         */
        void pushParameterFromLua(const std::string& name, sol::object parameter);
        /**
         * \brief Triggers callbacks
         */
        void execute();
        void onRegister(std::function<void(const TriggerEnv&)> callback);
        void onUnregister(std::function<void(const TriggerEnv&)> callback);

    public:
        /**
         * \brief Creates a new Trigger
         * \param parent Pointer to the parent TriggerGroup
         * \param name Name of the Trigger
         * \param startState State of the Trigger when created (enabled /
         *        disabled)
         */
        explicit Trigger(
            TriggerGroup& parent, const std::string& name, bool startState = false);
        /**
         * \brief Get the State of the Trigger (enabled / disabled)
         * \return true if the Trigger is enabled, false otherwise
         */
        bool getState() const;
        /**
         * \brief Get the name of the TriggerGroup which is the parent of the
         * Trigger \return A std::string containing the name of the TriggerGroup
         * which is the parent of the Trigger
         */
        [[nodiscard]] std::string getGroup() const;
        /**
         * \brief Get the name of the Trigger
         * \return A std::string containing the name of the Trigger
         */
        [[nodiscard]] std::string getName() const;
        /**
         * \brief Get the name of the namespace of the parent (TriggerGroup) of
         * the Trigger \return A std::string containing the name of the
         * namespace of the parent (TriggerGroup) of the Trigger
         */
        [[nodiscard]] std::string getNamespace() const;
        /**
         * \brief Registers a Lua State that will be triggered
         * \param environment Lua Environment to register
         * \param callback Name of the callback to register
         * \param active Pointer to the boolean that indicate if an
         *        environment is active or not
         */
        void registerEnvironment(const std::string& id, sol::environment environment,
            const std::string& callback, bool* active);
        /**
         * \brief Removes an environment from Trigger Execution
         * \param environment Lua Environment to unregister
         */
        void unregisterEnvironment(sol::environment environment);
        /**
         * \brief Gets the Lua Table path used to store Trigger Parameters
         * \return The path to the Lua Table used to store Trigger Parameters
         */
        [[nodiscard]] std::string getTriggerLuaTableName() const;
    };

    template <typename P>
    void Trigger::pushParameter(const std::string& name, P parameter)
    {
        Debug::Log->trace(
            "<Trigger> Pushing parameter {0} to Trigger {1}", name, m_fullName);
        m_lua["__TRIGGERS"][this->getTriggerLuaTableName()]["ArgTable"][name] = parameter;
        /*Script::ScriptEngine["LuaCore"]["TriggerArgTable"][this->getTriggerLuaTableName()]
                            [name]
            = parameter;*/
    }
} // namespace obe::Triggers
