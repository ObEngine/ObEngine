#pragma once

#include <memory>

#include <vili/node.hpp>

#include <Event/EventNamespace.hpp>
#include <Input/InputAction.hpp>
#include <Types/Togglable.hpp>

namespace obe::input
{
    /**
     * \brief Class used to manage KeyClass and KeyboardAction
     */
    class InputManager : public Types::Togglable
    {
    private:
        bool m_refresh = true;
        std::unordered_map<std::string, std::unique_ptr<InputButton>> m_inputs;
        std::vector<std::weak_ptr<InputButtonMonitor>> m_monitors;
        std::vector<std::shared_ptr<InputButtonMonitor>> m_key_monitors;
        event::EventGroupPtr e_actions;
        event::EventGroupPtr e_inputs;
        std::vector<std::shared_ptr<InputAction>> m_all_actions {};
        std::vector<InputAction*> m_current_actions {};
        bool is_action_currently_in_use(const std::string& action_id);
        void create_input_map();
        void create_events();
        [[nodiscard]] std::vector<std::string> get_all_input_button_names() const;

    public:
        /**
         * \brief Creates a new KeyboardManager
         */
        InputManager(event::EventNamespace& event_namespace);
        /**
         * \brief Get if a KeyboardAction exists
         * \param action_id Id of the KeyboardAction to check the existence
         * \return true if the KeyboardAction is found in the KeyboardManager,
         *         false otherwise
         */
        bool action_exists(const std::string& action_id) const;
        /**
         * \brief Adds a new context the KeyboardManager will use
         * \param context Name of the context to add
         * \return A reference to the KeyboardManager (to chain calls)
         */
        InputManager& add_context(const std::string& context);
        /**
         * \brief Get the KeyboardAction identified by actionId if it exists
         * \param action_id Id of the KeyboardAction to retrieve
         * \return A reference to the KeyboardAction if found
         */
        InputAction& get_action(const std::string& action_id) const;
        /**
         * \brief Gets all the contexts currently used by the InputManager
         * \return A std::vector of std::string containing all the contexts used
         *         by the InputManager
         */
        std::vector<std::string> get_contexts() const;
        /**
         * \brief Clears all Actions
         */
        void clear();
        /**
         * \brief Clear all contexts the KeyboardManager is using
         */
        void clear_contexts();
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
        InputManager& remove_context(const std::string& context);
        /**
         * \brief Cleans all the contexts and adds a new one
         * \param context Name of the only context to use
         */
        void set_context(const std::string& context);
        /**
         * \brief Updates the KeyboardManager
         */
        void update();
        /**
         * \brief Get an InputButton from the given key
         * \param key Name of the InputButton you want to get
         * \return A reference to the InputButton with the given name
         */
        InputButton& get_input(const std::string& key);
        /**
         * \brief Get a list of all InputButtons
         * \return A list of pointers to all InputButtons
         */
        std::vector<InputButton*> get_inputs();
        /**
         * \brief Get a list of all InputButtons with a given type
         * \param filter Type the InputButtons you want to get
         * \return A list of pointers to all InputButtons with given type
         */
        std::vector<InputButton*> get_inputs(InputType filter);
        /**
         * \brief Get a list of all InputButtons which are pressed
         * \return A list of pointers to all InputButtons which are pressed
         */
        std::vector<InputButton*> get_pressed_inputs() const;

        InputButtonMonitorPtr monitor(const std::string& name);
        InputButtonMonitorPtr monitor(InputButton& input);
        void require_refresh();
        /**
         * TODO: Fix this nobind
         * \nobind
         */
        InputCombination make_combination(const std::string& code);

        void initialize_gamepads();
        void initialize_gamepad(unsigned int gamepad_index);
    };
} // namespace obe::input
