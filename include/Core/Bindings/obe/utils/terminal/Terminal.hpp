#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::terminal::bindings
{
    void load_class_cursor_position(sol::state_view state);
    void load_function_styled_print(sol::state_view state);
    void load_function_get_cursor_position(sol::state_view state);
    void load_function_set_cursor_position(sol::state_view state);
    void load_function_set_terminal_mode_to_utf8(sol::state_view state);
};