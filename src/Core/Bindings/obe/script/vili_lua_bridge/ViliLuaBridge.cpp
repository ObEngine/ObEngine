#include <Bindings/obe/script/vili_lua_bridge/ViliLuaBridge.hpp>

#include <Script/ViliLuaBridge.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::vili_lua_bridge::bindings
{
    void load_function_vili_to_lua(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "vili_to_lua", &obe::script::vili_lua_bridge::vili_to_lua);
    }
    void load_function_vili_to_lua_keep_order(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "vili_to_lua_keep_order", &obe::script::vili_lua_bridge::vili_to_lua_keep_order_proxy);
    }
    void load_function_lua_to_vili(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "lua_to_vili", &obe::script::vili_lua_bridge::lua_to_vili);
    }
    void load_function_vili_object_to_lua_table(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "vili_object_to_lua_table", &obe::script::vili_lua_bridge::vili_object_to_lua_table);
    }
    void load_function_vili_object_to_lua_table_keep_order(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function("vili_object_to_lua_table_keep_order",
            &obe::script::vili_lua_bridge::vili_object_to_lua_table_keep_order);
    }
    void load_function_vili_primitive_to_lua_value(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function("vili_primitive_to_lua_value",
            &obe::script::vili_lua_bridge::vili_primitive_to_lua_value);
    }
    void load_function_vili_array_to_lua_table(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "vili_array_to_lua_table", &obe::script::vili_lua_bridge::vili_array_to_lua_table);
    }
    void load_function_lua_table_to_vili_object(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "lua_table_to_vili_object", &obe::script::vili_lua_bridge::lua_table_to_vili_object);
    }
    void load_function_lua_value_to_vili_primitive(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function("lua_value_to_vili_primitive",
            &obe::script::vili_lua_bridge::lua_value_to_vili_primitive);
    }
    void load_function_lua_table_to_vili_array(sol::state_view state)
    {
        sol::table vili_lua_bridge_namespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        vili_lua_bridge_namespace.set_function(
            "lua_table_to_vili_array", &obe::script::vili_lua_bridge::lua_table_to_vili_array);
    }
};