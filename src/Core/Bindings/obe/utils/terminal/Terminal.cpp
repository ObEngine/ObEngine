#include <Bindings/obe/utils/terminal/Terminal.hpp>

#include <Utils/Terminal.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::terminal::bindings
{
    void load_class_cursor_position(sol::state_view state)
    {
        sol::table terminal_namespace = state["obe"]["utils"]["terminal"].get<sol::table>();
        sol::usertype<obe::utils::terminal::CursorPosition> bind_cursor_position
            = terminal_namespace.new_usertype<obe::utils::terminal::CursorPosition>(
                "CursorPosition", sol::call_constructor, sol::default_constructor);
        bind_cursor_position["x"] = &obe::utils::terminal::CursorPosition::x;
        bind_cursor_position["y"] = &obe::utils::terminal::CursorPosition::y;
    }
    void load_function_styled_print(sol::state_view state)
    {
        sol::table terminal_namespace = state["obe"]["utils"]["terminal"].get<sol::table>();
        terminal_namespace.set_function("styled_print", &obe::utils::terminal::styled_print);
    }
    void load_function_get_cursor_position(sol::state_view state)
    {
        sol::table terminal_namespace = state["obe"]["utils"]["terminal"].get<sol::table>();
        terminal_namespace.set_function(
            "get_cursor_position", &obe::utils::terminal::get_cursor_position);
    }
    void load_function_set_cursor_position(sol::state_view state)
    {
        sol::table terminal_namespace = state["obe"]["utils"]["terminal"].get<sol::table>();
        terminal_namespace.set_function(
            "set_cursor_position", &obe::utils::terminal::set_cursor_position);
    }
    void load_function_set_terminal_mode_to_utf8(sol::state_view state)
    {
        sol::table terminal_namespace = state["obe"]["utils"]["terminal"].get<sol::table>();
        terminal_namespace.set_function(
            "set_terminal_mode_to_utf8", &obe::utils::terminal::set_terminal_mode_to_utf8);
    }
};