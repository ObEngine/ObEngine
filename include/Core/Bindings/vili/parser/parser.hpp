#pragma once

namespace sol
{
    class state_view;
};
namespace vili::parser::Bindings
{
    void LoadClassNodeInStack(sol::state_view state);
    void LoadClassState(sol::state_view state);
    void LoadClassError(sol::state_view state);
    void LoadFunctionFromString(sol::state_view state);
    void LoadFunctionFromFile(sol::state_view state);
    void LoadFunctionStatePushProxy(sol::state_view state);
};