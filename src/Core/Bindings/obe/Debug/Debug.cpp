#include <Bindings/obe/Debug/Debug.hpp>

#include <Debug/Logger.hpp>

#include <Bindings/Config.hpp>

namespace obe::debug::Bindings
{
    void LoadFunctionInitLogger(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("init_logger", &obe::debug::init_logger);
    }
    void LoadFunctionTrace(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("trace", &obe::debug::trace);
    }
    void LoadFunctionDebug(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("debug", &obe::debug::debug);
    }
    void LoadFunctionInfo(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("info", &obe::debug::info);
    }
    void LoadFunctionWarn(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("warn", &obe::debug::warn);
    }
    void LoadFunctionError(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("error", &obe::debug::error);
    }
    void LoadFunctionCritical(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace.set_function("critical", &obe::debug::critical);
    }
    void LoadGlobalLog(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["debug"].get<sol::table>();
        DebugNamespace["Log"] = obe::debug::Log;
    }
};