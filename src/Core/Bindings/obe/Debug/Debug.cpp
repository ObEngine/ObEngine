#include <Bindings/obe/Debug/Debug.hpp>

#include <Debug/Logger.hpp>

#include <Bindings/Config.hpp>

namespace obe::Debug::Bindings
{
    void LoadFunctionInitLogger(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("InitLogger", obe::Debug::InitLogger);
    }
    void LoadFunctionTrace(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("trace", obe::Debug::trace);
    }
    void LoadFunctionDebug(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("debug", obe::Debug::debug);
    }
    void LoadFunctionInfo(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("info", obe::Debug::info);
    }
    void LoadFunctionWarn(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("warn", obe::Debug::warn);
    }
    void LoadFunctionError(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("error", obe::Debug::error);
    }
    void LoadFunctionCritical(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("critical", obe::Debug::critical);
    }
    void LoadGlobalLog(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace["Log"] = obe::Debug::Log;
    }
};