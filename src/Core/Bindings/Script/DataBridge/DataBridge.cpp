#include <Bindings/Script/DataBridge/DataBridge.hpp>

#include <Script/ViliLuaBridge.hpp>

#include <sol/sol.hpp>

namespace obe::Script::DataBridge::Bindings
{
void LoadFunctionDataToLua(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("dataToLua", obe::Script::DataBridge::dataToLua);}
void LoadFunctionLuaToData(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("luaToData", obe::Script::DataBridge::luaToData);}
void LoadFunctionComplexNodeToLuaTable(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("complexNodeToLuaTable", obe::Script::DataBridge::complexNodeToLuaTable);}
void LoadFunctionDataNodeToLuaElement(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("dataNodeToLuaElement", obe::Script::DataBridge::dataNodeToLuaElement);}
void LoadFunctionArrayNodeToLuaTable(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("arrayNodeToLuaTable", obe::Script::DataBridge::arrayNodeToLuaTable);}
void LoadFunctionLuaTableToComplexNode(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("luaTableToComplexNode", obe::Script::DataBridge::luaTableToComplexNode);}
void LoadFunctionLuaElementToDataNode(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("luaElementToDataNode", obe::Script::DataBridge::luaElementToDataNode);}
void LoadFunctionLuaTableToArrayNode(sol::state_view state)
{
sol::table DataBridgeNamespace = state["obe"]["Script"]["DataBridge"].get<sol::table>();
DataBridgeNamespace.set_function("luaTableToArrayNode", obe::Script::DataBridge::luaTableToArrayNode);}
};