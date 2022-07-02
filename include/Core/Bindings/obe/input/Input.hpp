#pragma once

namespace sol
{
    class state_view;
};
namespace obe::input::bindings
{
    void load_class_input_action(sol::state_view state);
    void load_class_input_button(sol::state_view state);
    void load_class_input_button_monitor(sol::state_view state);
    void load_class_input_condition(sol::state_view state);
    void load_class_input_manager(sol::state_view state);
    void load_enum_mouse_wheel_scroll_direction(sol::state_view state);
    void load_enum_axis_threshold_direction(sol::state_view state);
    void load_enum_input_button_state(sol::state_view state);
    void load_enum_input_type(sol::state_view state);
}; // namespace obe::input::bindings