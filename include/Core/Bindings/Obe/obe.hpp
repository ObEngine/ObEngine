#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Bindings
{
    void LoadClassDebugInfo(sol::state_view state);
    void LoadClassException(sol::state_view state);
    void LoadFunctionInitEngine(sol::state_view state);
};