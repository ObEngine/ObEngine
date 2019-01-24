#pragma once

#include <kaguya/kaguya.hpp>

#include <Debug/Logger.hpp>
#include <Script/GlobalState.hpp>

namespace obe::Triggers
{
    class TriggerGroup;

    class TriggerEnv
    {
    public:
        unsigned int envIndex;
        std::string callbackName;
        bool* envActive = nullptr;
        TriggerEnv(unsigned int envIndex, const std::string& callbackName, bool* envActive)
            : envIndex(envIndex), callbackName(callbackName), envActive(envActive) {}
    };

    /**
    * \brief A Class that does represents a triggerable event
    * @Bind
    */
    class Trigger
    {
    private:
        TriggerGroup* m_parent;
        std::string m_name;
        std::string m_fullName;
        std::vector<TriggerEnv> m_registeredEnvs;
        std::vector<unsigned int> m_envsToRemove;
        bool m_currentlyTriggered = false;
        bool m_enabled = false;
        std::function<void(const TriggerEnv&)> m_onRegisterCallback;
        std::function<void(const TriggerEnv&)> m_onUnregisterCallback;
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
        /**
        * \brief Pushes a parameter on the Trigger from a Lua VM
        * \param name Name of the Parameter to push
        * \param parameter Value of the parameter (LuaRef can be anything)
        */
        void pushParameterFromLua(const std::string& name, const kaguya::LuaRef& parameter) const;
        /**
        * \brief Gets the Lua Table path used to store Trigger Parameters
        * \return The path to the Lua Table used to store Trigger Parameters
        */
        std::string getTriggerLuaTableName() const;
    public:
        /**
        * \brief Creates a new Trigger
        * \param parent Pointer to the parent TriggerGroup
        * \param name Name of the Trigger
        * \param startState State of the Trigger when created (enabled / disabled)
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
        * \param callbackName Name of the callback to register
        * \param envActive Pointer to the boolean that indicate if an environment is active or not
        */
        void registerEnvironment(unsigned int envIndex, const std::string& callbackName, bool* envActive);
        /**
        * \brief Removes an environment from Trigger Execution
        * \param envIndex Index of the Lua environment
        */
        void unregisterEnvironment(unsigned int envIndex);
        /**
        * \brief Triggers callbacks
        */
        void execute();
        void onRegister(std::function<void(const TriggerEnv&)> callback);
        void onUnregister(std::function<void(const TriggerEnv&)> callback);
    };

    template <typename P>
    void Trigger::pushParameter(const std::string& name, P parameter)
    {
        Debug::Log->trace("<Trigger> Pushing parameter {0} to Trigger {1}", name, m_fullName);
        Script::ScriptEngine["LuaCore"]["TriggerArgTable"][this->getTriggerLuaTableName()][name] = parameter;
    }
}

