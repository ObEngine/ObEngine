#include <Bindings/obe/Script/ViliLuaBridge/ViliLuaBridge.hpp>

#include <Script/ViliLuaBridge.hpp>

#include <Bindings/Config.hpp>

namespace obe::Script::ViliLuaBridge::Bindings
{
    void LoadFunctionViliToLua(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "viliToLua", obe::Script::ViliLuaBridge::viliToLua);
    }
    void LoadFunctionLuaToVili(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "luaToVili", obe::Script::ViliLuaBridge::luaToVili);
    }
    void LoadFunctionViliObjectToLuaTable(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "viliObjectToLuaTable", obe::Script::ViliLuaBridge::viliObjectToLuaTable);
    }
    void LoadFunctionViliPrimitiveToLuaValue(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function("viliPrimitiveToLuaValue",
            obe::Script::ViliLuaBridge::viliPrimitiveToLuaValue);
    }
    void LoadFunctionViliArrayToLuaTable(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "viliArrayToLuaTable", obe::Script::ViliLuaBridge::viliArrayToLuaTable);
    }
    void LoadFunctionLuaTableToViliObject(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "luaTableToViliObject", obe::Script::ViliLuaBridge::luaTableToViliObject);
    }
    void LoadFunctionLuaValueToViliPrimitive(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function("luaValueToViliPrimitive",
            obe::Script::ViliLuaBridge::luaValueToViliPrimitive);
    }
    void LoadFunctionLuaTableToViliArray(sol::state_view state)
    {
        sol::table ViliLuaBridgeNamespace
            = state["obe"]["Script"]["ViliLuaBridge"].get<sol::table>();
        ViliLuaBridgeNamespace.set_function(
            "luaTableToViliArray", obe::Script::ViliLuaBridge::luaTableToViliArray);
    }
};