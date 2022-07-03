#pragma once

namespace sol
{
    class state_view;
};
namespace obe::script::bindings
{
    void load_class_game_object(sol::state_view state);
    void load_class_game_object_database(sol::state_view state);
    void load_class_lua_state(sol::state_view state);
    void load_enum_environment_target(sol::state_view state);
    void load_function_sol_call_status_to_string(sol::state_view state);
    void load_function_safe_lua_call(sol::state_view state);
};