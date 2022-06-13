#include <Bindings/obe/Input/Input.hpp>

#include <Input/InputAction.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/InputButtonState.hpp>
#include <Input/InputCondition.hpp>
#include <Input/InputManager.hpp>
#include <Input/InputType.hpp>

#include <Bindings/Config.hpp>

namespace obe::input::Bindings
{
    void LoadEnumMouseWheelScrollDirection(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        InputNamespace.new_enum<obe::input::MouseWheelScrollDirection>("MouseWheelScrollDirection",
            { { "Up", obe::input::MouseWheelScrollDirection::Up },
                { "Down", obe::input::MouseWheelScrollDirection::Down },
                { "Left", obe::input::MouseWheelScrollDirection::Left },
                { "Right", obe::input::MouseWheelScrollDirection::Right } });
    }
    void LoadEnumAxisThresholdDirection(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        InputNamespace.new_enum<obe::input::AxisThresholdDirection>("AxisThresholdDirection",
            { { "Less", obe::input::AxisThresholdDirection::Less },
                { "More", obe::input::AxisThresholdDirection::More } });
    }
    void LoadEnumInputButtonState(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        InputNamespace.new_enum<obe::input::InputButtonState>("InputButtonState",
            { { "Idle", obe::input::InputButtonState::Idle },
                { "Hold", obe::input::InputButtonState::Hold },
                { "Pressed", obe::input::InputButtonState::Pressed },
                { "Released", obe::input::InputButtonState::Released },
                { "LAST__", obe::input::InputButtonState::LAST__ } });
    }
    void LoadEnumInputType(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        InputNamespace.new_enum<obe::input::InputType>("InputType",
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
    void LoadClassInputAction(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputAction> bindInputAction
            = InputNamespace.new_usertype<obe::input::InputAction>("InputAction",
                sol::call_constructor,
                sol::constructors<obe::input::InputAction(
                    obe::event::EventGroup*, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindInputAction["add_condition"] = &obe::input::InputAction::add_condition;
        bindInputAction["add_context"] = &obe::input::InputAction::add_context;
        bindInputAction["check"] = &obe::input::InputAction::check;
        bindInputAction["clear_conditions"] = &obe::input::InputAction::clear_conditions;
        bindInputAction["get_contexts"] = &obe::input::InputAction::get_contexts;
        bindInputAction["get_interval"] = &obe::input::InputAction::get_interval;
        bindInputAction["get_repeat"] = &obe::input::InputAction::get_repeat;
        bindInputAction["set_interval"] = &obe::input::InputAction::set_interval;
        bindInputAction["set_repeat"] = &obe::input::InputAction::set_repeat;
        bindInputAction["update"] = &obe::input::InputAction::update;
        bindInputAction["get_involved_buttons"] = &obe::input::InputAction::get_involved_buttons;
        bindInputAction["enable"] = &obe::input::InputAction::enable;
        bindInputAction["disable"] = &obe::input::InputAction::disable;
        bindInputAction["is_enabled"] = &obe::input::InputAction::is_enabled;
    }
    void LoadClassInputButton(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputButton> bindInputButton = InputNamespace.new_usertype<
            obe::input::InputButton>("InputButton", sol::call_constructor,
            sol::constructors<obe::input::InputButton(sf::Keyboard::Key, const std::string&,
                                  const std::string&, obe::input::InputType),
                obe::input::InputButton(sf::Mouse::Button, const std::string&),
                obe::input::InputButton(unsigned int, unsigned int, const std::string&),
                obe::input::InputButton(unsigned int, sf::Joystick::Axis,
                    std::pair<obe::input::AxisThresholdDirection, float>, const std::string&),
                obe::input::InputButton(obe::input::MouseWheelScrollDirection, const std::string&),
                obe::input::InputButton(const obe::input::InputButton&)>());
        bindInputButton["reload"] = &obe::input::InputButton::reload;
        bindInputButton["get_axis_position"] = &obe::input::InputButton::get_axis_position;
        bindInputButton["get_wheel_delta"] = &obe::input::InputButton::get_wheel_delta;
        bindInputButton["get_key"] = &obe::input::InputButton::get_key;
        bindInputButton["get_name"] = &obe::input::InputButton::get_name;
        bindInputButton["get_type"] = &obe::input::InputButton::get_type;
        bindInputButton["is"] = &obe::input::InputButton::is;
        bindInputButton["is_pressed"] = &obe::input::InputButton::is_pressed;
        bindInputButton["is_writable"] = &obe::input::InputButton::is_writable;
    }
    void LoadClassInputButtonMonitor(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputButtonMonitor> bindInputButtonMonitor
            = InputNamespace.new_usertype<obe::input::InputButtonMonitor>("InputButtonMonitor",
                sol::call_constructor,
                sol::constructors<obe::input::InputButtonMonitor(obe::input::InputButton&)>());
        bindInputButtonMonitor["get_button"] = &obe::input::InputButtonMonitor::get_button;
        bindInputButtonMonitor["get_state"] = &obe::input::InputButtonMonitor::get_state;
        bindInputButtonMonitor["update"] = &obe::input::InputButtonMonitor::update;
        bindInputButtonMonitor["check_for_refresh"]
            = &obe::input::InputButtonMonitor::check_for_refresh;
    }
    void LoadClassInputCondition(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputCondition> bindInputCondition
            = InputNamespace.new_usertype<obe::input::InputCondition>("InputCondition",
                sol::call_constructor, sol::constructors<obe::input::InputCondition()>());
        bindInputCondition["add_combination_element"]
            = &obe::input::InputCondition::add_combination_element;
        bindInputCondition["check"] = &obe::input::InputCondition::check;
        bindInputCondition["clear"] = &obe::input::InputCondition::clear;
        bindInputCondition["enable"] = &obe::input::InputCondition::enable;
        bindInputCondition["disable"] = &obe::input::InputCondition::disable;
        bindInputCondition["is_enabled"] = &obe::input::InputCondition::is_enabled;
    }
    void LoadClassInputManager(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputManager> bindInputManager
            = InputNamespace.new_usertype<obe::input::InputManager>("InputManager",
                sol::call_constructor,
                sol::constructors<obe::input::InputManager(obe::event::EventNamespace&)>(),
                sol::base_classes, sol::bases<obe::Types::Togglable>());
        bindInputManager["action_exists"] = &obe::input::InputManager::action_exists;
        bindInputManager["add_context"] = &obe::input::InputManager::add_context;
        bindInputManager["get_action"] = &obe::input::InputManager::get_action;
        bindInputManager["get_contexts"] = &obe::input::InputManager::get_contexts;
        bindInputManager["clear"] = &obe::input::InputManager::clear;
        bindInputManager["clear_contexts"] = &obe::input::InputManager::clear_contexts;
        bindInputManager["configure"] = &obe::input::InputManager::configure;
        bindInputManager["remove_context"] = &obe::input::InputManager::remove_context;
        bindInputManager["set_context"] = &obe::input::InputManager::set_context;
        bindInputManager["update"] = &obe::input::InputManager::update;
        bindInputManager["get_input"] = &obe::input::InputManager::get_input;
        bindInputManager["get_inputs"] = sol::overload(
            static_cast<std::vector<obe::input::InputButton*> (obe::input::InputManager::*)()>(
                &obe::input::InputManager::get_inputs),
            static_cast<std::vector<obe::input::InputButton*> (obe::input::InputManager::*)(
                obe::input::InputType)>(&obe::input::InputManager::get_inputs));
        bindInputManager["get_pressed_inputs"] = &obe::input::InputManager::get_pressed_inputs;
        bindInputManager["monitor"] = sol::overload(
            static_cast<obe::input::InputButtonMonitorPtr (obe::input::InputManager::*)(
                const std::string&)>(&obe::input::InputManager::monitor),
            static_cast<obe::input::InputButtonMonitorPtr (obe::input::InputManager::*)(
                obe::input::InputButton&)>(&obe::input::InputManager::monitor));
        bindInputManager["require_refresh"] = &obe::input::InputManager::require_refresh;
        bindInputManager["initialize_gamepads"] = &obe::input::InputManager::initialize_gamepads;
        bindInputManager["initialize_gamepad"] = &obe::input::InputManager::initialize_gamepad;
    }
};