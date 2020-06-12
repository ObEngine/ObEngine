#pragma once

namespace sol
{
    class state_view;
};
namespace vili::parser::Bindings
{
    void LoadClassNodeInStack(sol::state_view state);
    void LoadClassState(sol::state_view state);
    void LoadFunctionFromString(sol::state_view state);
    void LoadFunctionFromFile(sol::state_view state);
    void LoadGlobalErrorMessage(sol::state_view state);
};