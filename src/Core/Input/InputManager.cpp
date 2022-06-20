#include <set>

#include <Input/Exceptions.hpp>
#include <Input/InputManager.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::input
{
    bool update_or_clean_monitor(
        event::EventGroupPtr events, const std::weak_ptr<InputButtonMonitor>& element)
    {
        if (const auto monitor = element.lock())
        {
            monitor->update(events);
            return false;
        }
        else
        {
            return true;
        }
    }

    bool InputManager::is_action_currently_in_use(const std::string& action_id)
    {
        return std::ranges::any_of(
            m_current_actions, [&action_id](const auto& action) { return action->get_id() == action_id; });
    }

    InputManager::InputManager(event::EventNamespace& event_namespace)
        : Togglable(true)
        , e_actions(event_namespace.create_group("Actions"))
        , e_inputs(event_namespace.create_group("Keys"))
    {
        this->create_input_map();
        this->create_events();
    }

    InputAction& InputManager::get_action(const std::string& action_id) const
    {
        for (auto& action : m_all_actions)
        {
            if (action->get_id() == action_id)
            {
                return *action;
            }
        }
        std::vector<std::string> action_ids;
        action_ids.reserve(m_all_actions.size());
        for (auto& action : m_all_actions)
        {
            action_ids.push_back(action->get_id());
        }
        throw Exceptions::UnknownInputAction(action_id, action_ids, EXC_INFO);
    }

    void InputManager::update()
    {
        if (m_enabled)
        {
            for (const auto action_buffer = m_current_actions; const auto action : action_buffer)
            {

                action->update();
            }
            if (m_refresh)
            {
                bool should_refresh = false;
                for (auto& [_, input] : m_inputs)
                {

                    if (input->is_pressed())
                    {

                        should_refresh = true;
                        break;
                    }
                }
                std::erase_if(m_monitors,
                    [this](const std::weak_ptr<InputButtonMonitor>& element)
                    { return update_or_clean_monitor(e_inputs, element); });
                for (const auto& monitor_ptr : m_monitors)
                {
                    if (const auto& monitor = monitor_ptr.lock())
                    {
                        if (monitor->check_for_refresh())
                        {
                            should_refresh = true;
                            break;
                        }
                    }
                }
                m_refresh = should_refresh;
            }
        }
    }

    bool InputManager::action_exists(const std::string& action_id) const
    {
        return std::ranges::any_of(m_all_actions, [&action_id](const auto& action) { return action->get_id() == action_id; });
    }

    void InputManager::clear()
    {
        m_current_actions.clear();
        for (const auto& action : m_all_actions)
            e_actions->remove(action->get_id());
        m_all_actions.clear();
    }

    void InputManager::configure(vili::node& config)
    {
        std::vector<std::string> already_in_file;
        for (auto& [context_name, context] : config.items())
        {
            for (auto& [action_name, condition] : context.items())
            {
                if (!this->action_exists(action_name))
                {
                    m_all_actions.push_back(
                        std::make_unique<InputAction>(e_actions.get(), action_name));
                }
                else if (!utils::vector::contains(action_name, already_in_file))
                {
                    this->get_action(action_name).clear_conditions();
                }
                auto input_condition = [this](const InputManager* input_manager, const std::string& action,
                                          vili::node& condition)
                {
                    InputCondition action_condition;
                    InputCombination combination;
                    try
                    {
                        combination = this->make_combination(condition);
                    }
                    catch (const BaseException& e)
                    {
                        throw Exceptions::InvalidInputCombinationCode(action, condition, EXC_INFO)
                            .nest(e);
                    }

                    action_condition.set_combination(combination);
                    debug::Log->debug(
                        "<InputManager> Associated Key '{0}' for Action '{1}'", condition, action);
                    input_manager->get_action(action).add_condition(action_condition);
                };
                if (condition.is_primitive())
                {
                    input_condition(this, action_name, condition);
                }
                else if (condition.is<vili::array>())
                {
                    for (vili::node& single_condition : condition)
                    {
                        input_condition(this, action_name, single_condition);
                    }
                }
                this->get_action(action_name).add_context(context_name);
                already_in_file.push_back(action_name);
            }
        }
        // Add Context keys in real time <REVISION>
    }

    void InputManager::clear_contexts()
    {
        for (InputAction* action : m_current_actions)
        {
            action->disable();
        }
        m_current_actions.clear();
        // m_monitors.clear();
    }

    InputManager& InputManager::add_context(const std::string& context)
    {
        debug::Log->debug("<InputManager> Adding Context '{0}'", context);
        for (auto& action : m_all_actions)
        {
            if (utils::vector::contains(context, action->get_contexts())
                && !is_action_currently_in_use(action->get_id()))
            {
                debug::Log->debug(
                    "<InputManager> Add Action '{0}' in Context '{1}'", action->get_id(), context);
                m_current_actions.push_back(action.get());
                std::vector<InputButtonMonitorPtr> monitors;
                for (InputButton* button : action->get_involved_buttons())
                {
                    monitors.push_back(this->monitor(*button));
                }
                action->enable(monitors);
            }
        }
        return *this;
    }

    InputManager& InputManager::remove_context(const std::string& context)
    {
        //<REVISION> Multiple context, keep which one, remove keys of wrong
        // context
        m_current_actions.erase(std::remove_if(m_current_actions.begin(), m_current_actions.end(),
                                   [&context](auto& action) -> bool
                                   {
                                       const auto& contexts = action->get_contexts();
                                       auto is_action_in_context
                                           = std::find(contexts.begin(), contexts.end(), context)
                                           != contexts.end();
                                       if (is_action_in_context)
                                       {
                                           debug::Log->debug("<InputManager> Remove Action '{0}' "
                                                             "from Context '{1}'",
                                               action->get_id(), context);
                                           action->disable();
                                           return true;
                                       }
                                       else
                                       {
                                           return false;
                                       }
                                   }),
            m_current_actions.end());
        return *this;
    }

    void InputManager::set_context(const std::string& context)
    {
        this->clear_contexts();
        this->add_context(context);
    }

    std::vector<std::string> InputManager::get_contexts() const
    {
        std::set<std::string> all_contexts;

        for (const auto& action : m_current_actions)
        {
            for (const auto& context : action->get_contexts())
            {
                all_contexts.emplace(context);
            }
        }
        return std::vector<std::string>(all_contexts.begin(), all_contexts.end());
    }

    InputButton& InputManager::get_input(const std::string& key_id)
    {
        if (const auto& input = m_inputs.find(key_id); input != m_inputs.end())
            return *input->second;

        throw Exceptions::UnknownInputButton(key_id, this->get_all_input_button_names(), EXC_INFO);
    }

    std::vector<InputButton*> InputManager::get_inputs()
    {
        std::vector<InputButton*> inputs;
        inputs.reserve(m_inputs.size());
        for (auto& [_, input] : m_inputs)
        {
            inputs.push_back(input.get());
        }
        return inputs;
    }

    std::vector<InputButton*> InputManager::get_inputs(InputType filter)
    {
        std::vector<InputButton*> inputs;
        for (auto& key_iterator : m_inputs)
        {
            if (key_iterator.second->is(filter))
            {
                inputs.push_back(key_iterator.second.get());
            }
        }
        return inputs;
    }

    std::vector<InputButton*> InputManager::get_pressed_inputs() const
    {
        std::vector<InputButton*> all_pressed_buttons;
        for (auto& key_iterator : m_inputs)
        {
            if (key_iterator.second->is_pressed())
            {
                all_pressed_buttons.push_back(key_iterator.second.get());
            }
        }
        return all_pressed_buttons;
    }

    InputButtonMonitorPtr InputManager::monitor(const std::string& name)
    {
        return this->monitor(this->get_input(name));
    }

    InputButtonMonitorPtr InputManager::monitor(InputButton& input)
    {
        for (auto& monitor : m_monitors)
        {
            if (const auto shared_monitor = monitor.lock())
            {
                if (&shared_monitor->get_button() == &input)
                    return InputButtonMonitorPtr(shared_monitor);
            }
        }
        InputButtonMonitorPtr monitor = std::make_shared<InputButtonMonitor>(input);
        m_monitors.push_back(monitor);
        return std::move(monitor);
    }

    void InputManager::require_refresh()
    {
        m_refresh = true;
    }

    bool is_key_already_in_combination(InputCombination& combination, InputButton* button)
    {
        for (auto& [monitored_button, _] : combination)
        {
            if (monitored_button == button)
            {
                return true;
            }
        }
        return false;
    }
    InputCombination InputManager::make_combination(const std::string& code)
    {
        InputCombination combination;
        const std::vector<std::string> elements = utils::string::split(code, "+");
        if (code != "NotAssociated")
        {
            for (std::string element : elements)
            {
                utils::string::replace_in_place(element, " ", "");
                std::vector<std::string> state_and_button = utils::string::split(element, ":");
                if (state_and_button.size() == 1 || state_and_button.size() == 2)
                {
                    if (state_and_button.size() == 1)
                    {
                        state_and_button.push_back(state_and_button[0]);
                        state_and_button[0] = "Pressed";
                    }

                    std::vector<std::string> state_list
                        = utils::string::split(state_and_button[0], ",");
                    Types::FlagSet<InputButtonState> button_states;
                    for (std::string& button_state : state_list)
                    {
                        if (utils::vector::contains(
                                button_state, { "Idle", "Hold", "Pressed", "Released" }))
                        {
                            button_states |= InputButtonStateMeta::from_string(button_state);
                        }
                        else
                        {
                            throw Exceptions::InvalidInputButtonState(button_state, EXC_INFO);
                        }
                    }
                    const std::string key_id = state_and_button[1];
                    // Detect gamepad button / axis and initialize whole gamepad
                    if (key_id.substr(0, 3) == "GP_")
                    {
                        auto gamepad_parts = utils::string::split(key_id, "_");
                        unsigned int gamepad_index;
                        try
                        {
                            gamepad_index = std::stoi(gamepad_parts[1]);
                        }
                        catch (const std::invalid_argument& exc)
                        {
                            throw Exceptions::InvalidGamepadButton(key_id, EXC_INFO);
                        }
                        catch (const std::out_of_range& exc)
                        {
                            throw Exceptions::InvalidGamepadButton(key_id, EXC_INFO);
                        }
                        this->initialize_gamepad(gamepad_index);
                    }
                    if (m_inputs.contains(key_id))
                    {
                        InputButton& button = this->get_input(key_id);

                        if (!is_key_already_in_combination(combination, &button))
                        {
                            combination.emplace_back(&button, button_states);
                        }
                        else
                        {
                            throw Exceptions::InputButtonAlreadyInCombination(
                                button.get_name(), EXC_INFO);
                        }
                    }
                    else
                    {
                        throw Exceptions::UnknownInputButton(
                            key_id, this->get_all_input_button_names(), EXC_INFO);
                    }
                }
            }
        }
        return combination;
    }
} // namespace obe::input
