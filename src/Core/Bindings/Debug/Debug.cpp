#include <Bindings/Debug/Debug.hpp>

#include <Debug/Logger.hpp>

#include <sol/sol.hpp>

namespace obe::Debug::Bindings
{
    void LoadFunctionInitLogger(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace.set_function("InitLogger", obe::Debug::InitLogger);
    }
    void LoadGlobalLog(sol::state_view state)
    {
        sol::table DebugNamespace = state["obe"]["Debug"].get<sol::table>();
        DebugNamespace["Log"] = obe::Debug::Log;
    }
};