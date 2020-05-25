#pragma once

#include <memory>

#include <vili/node.hpp>

#include <Input/InputAction.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerManager.hpp>
#include <Types/Togglable.hpp>

namespace obe::Input
{
    /**
     * \brief Class used to manage KeyClass and KeyboardAction
     * \bind{InputManager}
     */
    class InputManager : public Types::Togglable
    {
    private:
        bool m_refresh = true;
        std::unordered_map<std::string, std::unique_ptr<InputButton>> m_inputs;
        std::vector<std::weak_ptr<InputButtonMonitor>> m_monitors;
        std::vector<std::shared_ptr<InputButtonMonitor>> m_key_monitors;
        Triggers::TriggerGroupPtr t_actions;
        Triggers::TriggerGroupPtr t_inputs;
        std::vector<std::shared_ptr<InputAction>> m_allActions {};
        std::vector<InputAction*> m_currentActions {};
        bool isActionCurrentlyInUse(const std::string& actionId);
        void createInputMap();
        void createGamepadMap();
        void createTriggerGroups(Triggers::TriggerManager& triggers);
        std::vector<std::string> getAllInputButtonNames() const;

    public:
        /**
         * \brief Creates a new KeyboardManager
         */
        InputManager();
        void init(Triggers::TriggerManager& triggers);
        /**
         * \brief Get if a KeyboardAction exists
         * \param actionId Id of the KeyboardAction to check the existence
         * \return true if the KeyboardAction is found in the KeyboardManager,
         *         false otherwise
         */
        bool actionExists(const std::string& actionId);
        /**
         * \brief Adds a new context the KeyboardManager will use
         * \param context Name of the context to add
         * \return A reference to the KeyboardManager (to chain calls)
         */
        InputManager& addContext(const std::string& context);
        /**
         * \brief Get the KeyboardAction identified by actionId if it exists
         * \param actionId Id of the KeyboardAction to retrieve
         * \return A reference to the KeyboardAction if found
         */
        InputAction& getAction(const std::string& actionId);
        /**
         * \brief Gets all the contexts currently used by the InputManager
         * \return A std::vector of std::string containing all the contexts used
         *         by the InputManager
         */
        std::vector<std::string> getContexts();
        /**
         * \brief Clears all Actions
         */
        void clear();
        /**
         * \brief Clear all contexts the KeyboardManager is using
         */
        void clearContexts();
        /**
         * \brief Configure KeyboardAction from a vili configuration file
         * \param config Reference to the vili ComplexAttribute used to
         *        configure the KeyboardManager
         */
        void configure(vili::node& config);
        /**
         * \brief Removes a context in use
         * \param context Name of the context to remove
         * \return A reference to the InputManager (to chain calls)
         */
        InputManager& removeContext(const std::string& context);
        /**
         * \brief Cleans all the contexts and adds a new one
         * \param context Name of the only context to use
         */
        void setContext(const std::string& context);
        /**
         * \brief Updates the KeyboardManager
         */
        void update();
        /**
         * \brief Get an InputButton from the given key
         * \param key Name of the InputButton you want to get
         * \return A reference to the InputButton with the given name
         */
        InputButton& getInput(const std::string& key);
        /**
         * \brief Get a list of all InputButtons
         * \return A list of pointers to all InputButtons
         */
        std::vector<InputButton*> getInputs();
        /**
         * \brief Get a list of all InputButtons with a given type
         * \param filter Type the InputButtons you want to get
         * \return A list of pointers to all InputButtons with given type
         */
        std::vector<InputButton*> getInputs(InputType filter);
        /**
         * \brief Get a list of all InputButtons which are pressed
         * \return A list of pointers to all InputButtons which are pressed
         */
        std::vector<InputButton*> getPressedInputs();

        InputButtonMonitorPtr monitor(const std::string& name);
        InputButtonMonitorPtr monitor(InputButton& input);
        void requireRefresh();
        /**
         * TODO: Fix this nobind
         * \nobind
         */
        InputCombination makeCombination(const std::string& code);
    };
} // namespace obe::Input
