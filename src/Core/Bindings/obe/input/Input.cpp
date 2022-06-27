#include <Bindings/obe/input/Input.hpp>

#include <Input/InputAction.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/InputButtonState.hpp>
#include <Input/InputCondition.hpp>
#include <Input/InputManager.hpp>
#include <Input/InputType.hpp>

#include <Bindings/Config.hpp>

namespace obe::input::bindings
{
    void load_enum_mouse_wheel_scroll_direction(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::MouseWheelScrollDirection>("MouseWheelScrollDirection",
            { { "Up", obe::input::MouseWheelScrollDirection::Up },
                { "Down", obe::input::MouseWheelScrollDirection::Down },
                { "Left", obe::input::MouseWheelScrollDirection::Left },
                { "Right", obe::input::MouseWheelScrollDirection::Right } });
    }
    void load_enum_axis_threshold_direction(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::AxisThresholdDirection>("AxisThresholdDirection",
            { { "Less", obe::input::AxisThresholdDirection::Less },
                { "More", obe::input::AxisThresholdDirection::More } });
    }
    void load_enum_input_button_state(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::InputButtonState>("InputButtonState",
            { { "Idle", obe::input::InputButtonState::Idle },
                { "Hold", obe::input::InputButtonState::Hold },
                { "Pressed", obe::input::InputButtonState::Pressed },
                { "Released", obe::input::InputButtonState::Released },
                { "LAST__", obe::input::InputButtonState::LAST__ } });
    }
    void load_enum_input_type(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::InputType>("InputType",
            { { "Alpha", obe::input::InputType::Alpha },
                { "Numeric", obe::input::InputType::Numeric },
                { "NumericNP", obe::input::InputType::NumericNP },
                { "Arrows", obe::input::InputType::Arrows },
                { "Functions", obe::input::InputType::Functions },
                { "Mouse", obe::input::InputType::Mouse },
                { "Others", obe::input::InputType::Others },
                { "GamepadButton", obe::input::InputType::GamepadButton },
                { "GamepadAxis", obe::input::InputType::GamepadAxis },
                { "ScrollWheel", obe::input::InputType::ScrollWheel } });
    }
    void load_class_input_action(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputAction> bind_input_action
            = input_namespace.new_usertype<obe::input::InputAction>("InputAction",
                sol::call_constructor,
                sol::constructors<obe::input::InputAction(
                    obe::event::EventGroup*, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bind_input_action["add_condition"] = &obe::input::InputAction::add_condition;
        bind_input_action["add_context"] = &obe::input::InputAction::add_context;
        bind_input_action["check"] = &obe::input::InputAction::check;
        bind_input_action["clear_conditions"] = &obe::input::InputAction::clear_conditions;
        bind_input_action["get_contexts"] = &obe::input::InputAction::get_contexts;
        bind_input_action["get_interval"] = &obe::input::InputAction::get_interval;
        bind_input_action["get_repeat"] = &obe::input::InputAction::get_repeat;
        bind_input_action["set_interval"] = &obe::input::InputAction::set_interval;
        bind_input_action["set_repeat"] = &obe::input::InputAction::set_repeat;
        bind_input_action["update"] = &obe::input::InputAction::update;
        bind_input_action["get_involved_buttons"] = &obe::input::InputAction::get_involved_buttons;
        bind_input_action["enable"] = &obe::input::InputAction::enable;
        bind_input_action["disable"] = &obe::input::InputAction::disable;
        bind_input_action["is_enabled"] = &obe::input::InputAction::is_enabled;
    }
    void load_class_input_button(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputButton> bind_input_button = input_namespace.new_usertype<
            obe::input::InputButton>("InputButton", sol::call_constructor,
            sol::constructors<obe::input::InputButton(sf::Keyboard::Key, const std::string&,
                                  const std::string&, obe::input::InputType),
                obe::input::InputButton(sf::Mouse::Button, const std::string&),
                obe::input::InputButton(unsigned int, unsigned int, const std::string&),
                obe::input::InputButton(unsigned int, sf::Joystick::Axis,
                    std::pair<obe::input::AxisThresholdDirection, float>, const std::string&),
                obe::input::InputButton(obe::input::MouseWheelScrollDirection, const std::string&),
                obe::input::InputButton(const obe::input::InputButton&)>());
        bind_input_button["reload"] = &obe::input::InputButton::reload;
        bind_input_button["get_axis_position"] = &obe::input::InputButton::get_axis_position;
        bind_input_button["get_wheel_delta"] = &obe::input::InputButton::get_wheel_delta;
        bind_input_button["get_key"] = &obe::input::InputButton::get_key;
        bind_input_button["get_name"] = &obe::input::InputButton::get_name;
        bind_input_button["get_type"] = &obe::input::InputButton::get_type;
        bind_input_button["is"] = &obe::input::InputButton::is;
        bind_input_button["is_pressed"] = &obe::input::InputButton::is_pressed;
        bind_input_button["is_writable"] = &obe::input::InputButton::is_writable;
    }
    void load_class_input_button_monitor(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputButtonMonitor> bind_input_button_monitor
            = input_namespace.new_usertype<obe::input::InputButtonMonitor>("InputButtonMonitor",
                sol::call_constructor,
                sol::constructors<obe::input::InputButtonMonitor(obe::input::InputButton&)>());
        bind_input_button_monitor["get_button"] = &obe::input::InputButtonMonitor::get_button;
        bind_input_button_monitor["get_state"] = &obe::input::InputButtonMonitor::get_state;
        bind_input_button_monitor["update"] = &obe::input::InputButtonMonitor::update;
        bind_input_button_monitor["check_for_refresh"]
            = &obe::input::InputButtonMonitor::check_for_refresh;
    }
    void load_class_input_condition(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputCondition> bind_input_condition
            = input_namespace.new_usertype<obe::input::InputCondition>("InputCondition",
                sol::call_constructor, sol::constructors<obe::input::InputCondition()>());
        bind_input_condition["add_combination_element"]
            = &obe::input::InputCondition::add_combination_element;
        bind_input_condition["check"] = &obe::input::InputCondition::check;
        bind_input_condition["clear"] = &obe::input::InputCondition::clear;
        bind_input_condition["enable"] = &obe::input::InputCondition::enable;
        bind_input_condition["disable"] = &obe::input::InputCondition::disable;
        bind_input_condition["is_enabled"] = &obe::input::InputCondition::is_enabled;
    }
    void load_class_input_manager(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputManager> bind_input_manager
            = input_namespace.new_usertype<obe::input::InputManager>("InputManager",
                sol::call_constructor,
                sol::constructors<obe::input::InputManager(obe::event::EventNamespace&)>(),
                sol::base_classes, sol::bases<obe::Types::Togglable>());
        bind_input_manager["action_exists"] = &obe::input::InputManager::action_exists;
        bind_input_manager["add_context"] = &obe::input::InputManager::add_context;
        bind_input_manager["get_action"] = &obe::input::InputManager::get_action;
        bind_input_manager["get_contexts"] = &obe::input::InputManager::get_contexts;
        bind_input_manager["clear"] = &obe::input::InputManager::clear;
        bind_input_manager["clear_contexts"] = &obe::input::InputManager::clear_contexts;
        bind_input_manager["configure"] = &obe::input::InputManager::configure;
        bind_input_manager["remove_context"] = &obe::input::InputManager::remove_context;
        bind_input_manager["set_context"] = &obe::input::InputManager::set_context;
        bind_input_manager["update"] = &obe::input::InputManager::update;
        bind_input_manager["get_input"] = &obe::input::InputManager::get_input;
        bind_input_manager["get_inputs"] = sol::overload(
            static_cast<std::vector<obe::input::InputButton*> (obe::input::InputManager::*)()>(
                &obe::input::InputManager::get_inputs),
            static_cast<std::vector<obe::input::InputButton*> (obe::input::InputManager::*)(
                obe::input::InputType)>(&obe::input::InputManager::get_inputs));
        bind_input_manager["get_pressed_inputs"] = &obe::input::InputManager::get_pressed_inputs;
        bind_input_manager["monitor"] = sol::overload(
            static_cast<obe::input::InputButtonMonitorPtr (obe::input::InputManager::*)(
                const std::string&)>(&obe::input::InputManager::monitor),
            static_cast<obe::input::InputButtonMonitorPtr (obe::input::InputManager::*)(
                obe::input::InputButton&)>(&obe::input::InputManager::monitor));
        bind_input_manager["require_refresh"] = &obe::input::InputManager::require_refresh;
        bind_input_manager["initialize_gamepads"] = &obe::input::InputManager::initialize_gamepads;
        bind_input_manager["initialize_gamepad"] = &obe::input::InputManager::initialize_gamepad;
    }
};