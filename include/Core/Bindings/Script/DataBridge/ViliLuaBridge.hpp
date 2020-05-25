#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Script::ViliLuaBridge::Bindings
{
    void LoadFunctionDataToLua(sol::state_view state);
    void LoadFunctionLuaToData(sol::state_view state);
    void LoadFunctionComplexNodeToLuaTable(sol::state_view state);
    void LoadFunctionDataNodeToLuaElement(sol::state_view state);
    void LoadFunctionArrayNodeToLuaTable(sol::state_view state);
    void LoadFunctionLuaTableToComplexNode(sol::state_view state);
    void LoadFunctionLuaElementToDataNode(sol::state_view state);
    void LoadFunctionLuaTableToArrayNode(sol::state_view state);
};