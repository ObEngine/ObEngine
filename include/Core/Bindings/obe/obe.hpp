#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Bindings
{
    void LoadClassBaseException(sol::state_view state);
    void LoadClassDebugInfo(sol::state_view state);
    void LoadFunctionGetTypeName(sol::state_view state);
    void LoadFunctionInitEngine(sol::state_view state);
    void LoadGlobalObengineProduction(sol::state_view state);
};