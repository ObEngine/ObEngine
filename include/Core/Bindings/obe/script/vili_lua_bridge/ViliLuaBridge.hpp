#pragma once

namespace sol
{
    class state_view;
};
namespace obe::script::vili_lua_bridge::bindings
{
    void load_function_vili_to_lua(sol::state_view state);
    void load_function_lua_to_vili(sol::state_view state);
    void load_function_vili_object_to_lua_table(sol::state_view state);
    void load_function_vili_primitive_to_lua_value(sol::state_view state);
    void load_function_vili_array_to_lua_table(sol::state_view state);
    void load_function_lua_table_to_vili_object(sol::state_view state);
    void load_function_lua_value_to_vili_primitive(sol::state_view state);
    void load_function_lua_table_to_vili_array(sol::state_view state);
}; // namespace obe::script::vili_lua_bridge::bindings