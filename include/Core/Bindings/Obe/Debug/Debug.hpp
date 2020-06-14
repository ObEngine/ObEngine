#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Debug::Bindings
{
    void LoadFunctionInitLogger(sol::state_view state);
    void LoadFunctionTrace(sol::state_view state);
    void LoadFunctionDebug(sol::state_view state);
    void LoadFunctionInfo(sol::state_view state);
    void LoadFunctionWarn(sol::state_view state);
    void LoadFunctionError(sol::state_view state);
    void LoadFunctionCritical(sol::state_view state);
    void LoadGlobalLog(sol::state_view state);
};