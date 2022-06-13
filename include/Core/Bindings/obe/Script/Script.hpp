#pragma once

namespace sol
{
    class state_view;
};
namespace obe::script::Bindings
{
    void LoadClassGameObject(sol::state_view state);
    void LoadClassGameObjectDatabase(sol::state_view state);
    void LoadClassLuaState(sol::state_view state);
    void LoadFunctionSafeLuaCall(sol::state_view state);
};