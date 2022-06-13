#pragma once

#include <sol/sol.hpp>

#include <Script/Exceptions.hpp>

namespace obe::script
{
    inline std::string sol_call_status_to_string(sol::call_status status)
    {
        switch (status)
        {
        case sol::call_status::ok:
            return "ok";
        case sol::call_status::yielded:
            return "yielded";
        case sol::call_status::runtime:
            return "runtime_error";
        case sol::call_status::memory:
            return "memory_error";
        case sol::call_status::handler:
            return "handler_error";
        case sol::call_status::gc:
            return "gc_error";
        case sol::call_status::syntax:
            return "syntax_error";
        case sol::call_status::file:
            return "file_error";
        }
    }

    template <class... Args>
    void safeLuaCall(sol::protected_function callback, Args&&... args)
    {
        const sol::protected_function_result result = callback(args...);
        if (!result.valid())
        {
            if (result.return_count() > 0)
            {
                try
                {
                    const auto errObj = result.get<sol::error>();
                    throw exceptions::LuaExecutionError(errObj, EXC_INFO);
                }
                catch (const sol::error& err)
                {
                    throw exceptions::LuaNestedExceptionError(err, EXC_INFO);
                }
            }
            else
            {
                const sol::call_status status = result.status();
                const std::string status_str = sol_call_status_to_string(status);
                const std::string error_str = fmt::format("No error, status : '{}'", status_str);
                throw exceptions::LuaExecutionError(std::runtime_error(error_str), EXC_INFO);
            }
        }
    }
}
