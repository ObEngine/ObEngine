#include <Bindings/Script/DataBridge/ViliLuaBridge.hpp>

#include <Script/ViliLuaBridge.hpp>

#include <sol/sol.hpp>

namespace obe::Script::ViliLuaBridge::Bindings
{
    void LoadFunctionDataToLua(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function("dataToLua", obe::Script::ViliLuaBridge::viliToLua);
    }
    void LoadFunctionLuaToData(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function("luaToData", obe::Script::ViliLuaBridge::luaToVili);
    }
    void LoadFunctionComplexNodeToLuaTable(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function(
            "complexNodeToLuaTable", obe::Script::ViliLuaBridge::viliObjectToLuaTable);
    }
    void LoadFunctionDataNodeToLuaElement(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function(
            "dataNodeToLuaElement", obe::Script::ViliLuaBridge::viliPrimitiveToLuaValue);
    }
    void LoadFunctionArrayNodeToLuaTable(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function(
            "arrayNodeToLuaTable", obe::Script::ViliLuaBridge::viliArrayToLuaTable);
    }
    void LoadFunctionLuaTableToComplexNode(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function(
            "luaTableToComplexNode", obe::Script::ViliLuaBridge::luaTableToViliObject);
    }
    void LoadFunctionLuaElementToDataNode(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function(
            "luaElementToDataNode", obe::Script::ViliLuaBridge::luaValueToViliPrimitive);
    }
    void LoadFunctionLuaTableToArrayNode(sol::state_view state)
    {
        sol::table DataBridgeNamespace
            = state["obe"]["Script"]["DataBridge"].get<sol::table>();
        DataBridgeNamespace.set_function(
            "luaTableToArrayNode", obe::Script::ViliLuaBridge::luaTableToViliArray);
    }
};