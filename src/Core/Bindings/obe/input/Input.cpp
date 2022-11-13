#include <Bindings/obe/input/Input.hpp>

#include <Input/InputAction.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/InputCondition.hpp>
#include <Input/InputManager.hpp>
#include <Input/InputSource.hpp>
#include <Input/InputSourceGamepad.hpp>
#include <Input/InputSourceKeyboard.hpp>
#include <Input/InputSourceMouse.hpp>
#include <Input/InputSourceState.hpp>
#include <Input/InputType.hpp>
#include <Script/AutoCastManager.hpp>

#include <Bindings/Config.hpp>

namespace obe::input::bindings
{
    void load_enum_axis_threshold_direction(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::AxisThresholdDirection>("AxisThresholdDirection",
            { { "Less", obe::input::AxisThresholdDirection::Less },
                { "More", obe::input::AxisThresholdDirection::More } });
    }
    void load_enum_mouse_wheel_scroll_direction(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::MouseWheelScrollDirection>("MouseWheelScrollDirection",
            { { "Up", obe::input::MouseWheelScrollDirection::Up },
                { "Down", obe::input::MouseWheelScrollDirection::Down },
                { "Left", obe::input::MouseWheelScrollDirection::Left },
                { "Right", obe::input::MouseWheelScrollDirection::Right } });
    }
    void load_enum_input_source_state(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        input_namespace.new_enum<obe::input::InputSourceState>("InputSourceState",
            { { "Idle", obe::input::InputSourceState::Idle },
                { "Hold", obe::input::InputSourceState::Hold },
                { "Pressed", obe::input::InputSourceState::Pressed },
                { "Released", obe::input::InputSourceState::Released } });
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
                sol::base_classes, sol::bases<obe::types::Identifiable>());
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
        bind_input_action["get_involved_input_sources"]
            = &obe::input::InputAction::get_involved_input_sources;
        bind_input_action["enable"] = &obe::input::InputAction::enable;
        bind_input_action["disable"] = &obe::input::InputAction::disable;
        bind_input_action["is_enabled"] = &obe::input::InputAction::is_enabled;
    }
    void load_class_input_button_monitor(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputButtonMonitor> bind_input_button_monitor
            = input_namespace.new_usertype<obe::input::InputButtonMonitor>("InputButtonMonitor");
        bind_input_button_monitor["get_input_source"]
            = &obe::input::InputButtonMonitor::get_input_source;
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
                sol::base_classes, sol::bases<obe::types::Togglable>());
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
        bind_input_manager["get_input_source"] = &obe::input::InputManager::get_input_source;
        bind_input_manager["get_all_input_sources"] = sol::overload(
            static_cast<std::vector<obe::input::InputSource*> (obe::input::InputManager::*)()
                    const>(&obe::input::InputManager::get_all_input_sources),
            static_cast<std::vector<obe::input::InputSource*> (obe::input::InputManager::*)(
                const std::string&) const>(&obe::input::InputManager::get_all_input_sources));
        bind_input_manager["get_pressed_input_sources"]
            = &obe::input::InputManager::get_pressed_input_sources;
        bind_input_manager["monitor"] = sol::overload(
            static_cast<obe::input::InputButtonMonitorPtr (obe::input::InputManager::*)(
                const std::string&)>(&obe::input::InputManager::monitor),
            static_cast<obe::input::InputButtonMonitorPtr (obe::input::InputManager::*)(
                obe::input::InputSource&)>(&obe::input::InputManager::monitor));
        bind_input_manager["require_refresh"] = &obe::input::InputManager::require_refresh;
        bind_input_manager["initialize_gamepads"] = &obe::input::InputManager::initialize_gamepads;
        bind_input_manager["initialize_gamepad"] = &obe::input::InputManager::initialize_gamepad;
        bind_input_manager["process_events"] = &obe::input::InputManager::process_events;
    }
    void load_class_input_source(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputSource> bind_input_source
            = input_namespace.new_usertype<obe::input::InputSource>("InputSource");
        bind_input_source["get_name"] = &obe::input::InputSource::get_name;
        bind_input_source["get_printable_char"] = &obe::input::InputSource::get_printable_char;
        bind_input_source["is_pressed"] = &obe::input::InputSource::is_pressed;
        bind_input_source["is_printable"] = &obe::input::InputSource::is_printable;
        bind_input_source["type"] = &obe::input::InputSource::type;
    }
    void load_class_input_source_gamepad_axis(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputSourceGamepadAxis> bind_input_source_gamepad_axis
            = input_namespace.new_usertype<obe::input::InputSourceGamepadAxis>(
                "InputSourceGamepadAxis", sol::call_constructor,
                sol::constructors<obe::input::InputSourceGamepadAxis(unsigned int,
                    sf::Joystick::Axis, std::pair<obe::input::AxisThresholdDirection, float>,
                    const std::string&)>(),
                sol::base_classes, sol::bases<obe::input::InputSource>());
        bind_input_source_gamepad_axis["get_gamepad_index"]
            = &obe::input::InputSourceGamepadAxis::get_gamepad_index;
        bind_input_source_gamepad_axis["get_axis_position"]
            = &obe::input::InputSourceGamepadAxis::get_axis_position;
        bind_input_source_gamepad_axis["is_pressed"]
            = &obe::input::InputSourceGamepadAxis::is_pressed;
        bind_input_source_gamepad_axis["type"] = &obe::input::InputSourceGamepadAxis::type;
        bind_input_source_gamepad_axis["Type"]
            = sol::var(&obe::input::InputSourceGamepadAxis::Type);

        script::AutoCastManager<input::InputSource>::Register<obe::input::InputSourceGamepadAxis>();
    }
    void load_class_input_source_gamepad_button(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputSourceGamepadButton> bind_input_source_gamepad_button
            = input_namespace.new_usertype<obe::input::InputSourceGamepadButton>(
                "InputSourceGamepadButton", sol::call_constructor,
                sol::constructors<obe::input::InputSourceGamepadButton(
                    unsigned int, unsigned int, const std::string&)>(),
                sol::base_classes, sol::bases<obe::input::InputSource>());
        bind_input_source_gamepad_button["get_gamepad_index"]
            = &obe::input::InputSourceGamepadButton::get_gamepad_index;
        bind_input_source_gamepad_button["get_button_index"]
            = &obe::input::InputSourceGamepadButton::get_button_index;
        bind_input_source_gamepad_button["is_pressed"]
            = &obe::input::InputSourceGamepadButton::is_pressed;
        bind_input_source_gamepad_button["type"] = &obe::input::InputSourceGamepadButton::type;
        bind_input_source_gamepad_button["Type"]
            = sol::var(&obe::input::InputSourceGamepadButton::Type);

        script::AutoCastManager<input::InputSource>::Register<
            obe::input::InputSourceGamepadButton>();
    }
    void load_class_input_source_keyboard_key(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputSourceKeyboardKey> bind_input_source_keyboard_key
            = input_namespace.new_usertype<obe::input::InputSourceKeyboardKey>(
                "InputSourceKeyboardKey", sol::call_constructor,
                sol::constructors<obe::input::InputSourceKeyboardKey(
                                      sf::Keyboard::Key, const std::string&),
                    obe::input::InputSourceKeyboardKey(
                        sf::Keyboard::Key, const std::string&, const std::string&)>(),
                sol::base_classes, sol::bases<obe::input::InputSource>());
        bind_input_source_keyboard_key["get_key"] = &obe::input::InputSourceKeyboardKey::get_key;
        bind_input_source_keyboard_key["is_pressed"]
            = &obe::input::InputSourceKeyboardKey::is_pressed;
        bind_input_source_keyboard_key["type"] = &obe::input::InputSourceKeyboardKey::type;
        bind_input_source_keyboard_key["Type"]
            = sol::var(&obe::input::InputSourceKeyboardKey::Type);

        script::AutoCastManager<input::InputSource>::Register<obe::input::InputSourceKeyboardKey>();
    }
    void load_class_input_source_mouse_button(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputSourceMouseButton> bind_input_source_mouse_button
            = input_namespace.new_usertype<obe::input::InputSourceMouseButton>(
                "InputSourceMouseButton", sol::call_constructor,
                sol::constructors<obe::input::InputSourceMouseButton(sf::Mouse::Button)>(),
                sol::base_classes, sol::bases<obe::input::InputSource>());
        bind_input_source_mouse_button["get_mouse_button"]
            = &obe::input::InputSourceMouseButton::get_mouse_button;
        bind_input_source_mouse_button["is_pressed"]
            = &obe::input::InputSourceMouseButton::is_pressed;
        bind_input_source_mouse_button["type"] = &obe::input::InputSourceMouseButton::type;
        bind_input_source_mouse_button["Type"]
            = sol::var(&obe::input::InputSourceMouseButton::Type);

        script::AutoCastManager<input::InputSource>::Register<obe::input::InputSourceMouseButton>();
    }
    void load_class_input_source_mouse_wheel_scroll(sol::state_view state)
    {
        sol::table input_namespace = state["obe"]["input"].get<sol::table>();
        sol::usertype<obe::input::InputSourceMouseWheelScroll> bind_input_source_mouse_wheel_scroll
            = input_namespace.new_usertype<obe::input::InputSourceMouseWheelScroll>(
                "InputSourceMouseWheelScroll", sol::call_constructor,
                sol::constructors<obe::input::InputSourceMouseWheelScroll(
                                      obe::input::MouseWheelScrollDirection),
                    obe::input::InputSourceMouseWheelScroll(
                        obe::input::MouseWheelScrollDirection, float)>(),
                sol::base_classes, sol::bases<obe::input::InputSource>());
        bind_input_source_mouse_wheel_scroll["get_scroll_wheel_direction"]
            = &obe::input::InputSourceMouseWheelScroll::get_scroll_wheel_direction;
        bind_input_source_mouse_wheel_scroll["is_pressed"]
            = &obe::input::InputSourceMouseWheelScroll::is_pressed;
        bind_input_source_mouse_wheel_scroll["type"]
            = &obe::input::InputSourceMouseWheelScroll::type;
        bind_input_source_mouse_wheel_scroll["Type"]
            = sol::var(&obe::input::InputSourceMouseWheelScroll::Type);

        script::AutoCastManager<input::InputSource>::Register<
            obe::input::InputSourceMouseWheelScroll>();
    }
};