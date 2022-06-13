#include <Bindings/obe/Script/ViliLuaBridge/ViliLuaBridge.hpp>

#include <Script/ViliLuaBridge.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::vili_lua_bridge::Bindings
{
    void LoadFunctionViliToLua(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function("vili_to_lua", &obe::script::vili_lua_bridge::vili_to_lua);
    }
    void LoadFunctionLuaToVili(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function("lua_to_vili", &obe::script::vili_lua_bridge::lua_to_vili);
    }
    void LoadFunctionViliObjectToLuaTable(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "vili_object_to_lua_table", &obe::script::vili_lua_bridge::vili_object_to_lua_table);
    }
    void LoadFunctionViliPrimitiveToLuaValue(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "vili_primitive_to_lua_value", &obe::script::vili_lua_bridge::vili_primitive_to_lua_value);
    }
    void LoadFunctionViliArrayToLuaTable(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "vili_array_to_lua_table", &obe::script::vili_lua_bridge::vili_array_to_lua_table);
    }
    void LoadFunctionLuaTableToViliObject(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "lua_table_to_vili_object", &obe::script::vili_lua_bridge::lua_table_to_vili_object);
    }
    void LoadFunctionLuaValueToViliPrimitive(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "lua_value_to_vili_primitive", &obe::script::vili_lua_bridge::lua_value_to_vili_primitive);
    }
    void LoadFunctionLuaTableToViliArray(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["script"]["vili_lua_bridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "lua_table_to_vili_array", &obe::script::vili_lua_bridge::lua_table_to_vili_array);
    }
};