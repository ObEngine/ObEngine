#include <Bindings/obe/debug/Debug.hpp>

#include <Debug/Logger.hpp>

#include <Bindings/Config.hpp>

namespace obe::debug::bindings
{
    void load_enum_log_level(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.new_enum<obe::debug::LogLevel>("LogLevel",
            { { "Trace", obe::debug::LogLevel::Trace }, { "Debug", obe::debug::LogLevel::Debug },
                { "Info", obe::debug::LogLevel::Info }, { "Warn", obe::debug::LogLevel::Warn },
                { "Error", obe::debug::LogLevel::Error },
                { "Critical", obe::debug::LogLevel::Critical },
                { "Off", obe::debug::LogLevel::Off } });
    }
    void load_function_init_logger(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("init_logger", &obe::debug::init_logger);
    }
    void load_function_trace(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("trace", &obe::debug::trace);
    }
    void load_function_debug(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("debug", &obe::debug::debug);
    }
    void load_function_info(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("info", &obe::debug::info);
    }
    void load_function_warn(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("warn", &obe::debug::warn);
    }
    void load_function_error(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("error", &obe::debug::error);
    }
    void load_function_critical(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace.set_function("critical", &obe::debug::critical);
    }
    void load_global_log(sol::state_view state)
    {
        sol::table debug_namespace = state["obe"]["debug"].get<sol::table>();
        debug_namespace["Log"] = obe::debug::Log;
    }
};