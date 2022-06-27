#pragma once

namespace sol
{
    class state_view;
};
namespace obe::input::Exceptions::bindings
{
    void load_class_input_button_already_in_combination(sol::state_view state);
    void load_class_input_button_invalid_operation(sol::state_view state);
    void load_class_invalid_gamepad_button(sol::state_view state);
    void load_class_invalid_input_button_state(sol::state_view state);
    void load_class_invalid_input_combination_code(sol::state_view state);
    void load_class_invalid_input_type_enum_value(sol::state_view state);
    void load_class_unknown_input_action(sol::state_view state);
    void load_class_unknown_input_button(sol::state_view state);
};