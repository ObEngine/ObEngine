#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Script::ViliLuaBridge::Bindings
{
    void LoadFunctionViliToLua(sol::state_view state);
    void LoadFunctionLuaToVili(sol::state_view state);
    void LoadFunctionViliObjectToLuaTable(sol::state_view state);
    void LoadFunctionViliPrimitiveToLuaValue(sol::state_view state);
    void LoadFunctionViliArrayToLuaTable(sol::state_view state);
    void LoadFunctionLuaTableToViliObject(sol::state_view state);
    void LoadFunctionLuaValueToViliPrimitive(sol::state_view state);
    void LoadFunctionLuaTableToViliArray(sol::state_view state);
};