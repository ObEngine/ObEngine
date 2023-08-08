#pragma once

#include <Script/Exceptions.hpp>
#include <sol/sol.hpp>

namespace obe::script
{
    std::unique_ptr<sol::state> make_lua_state();
    std::string sol_call_status_to_string(sol::call_status status);

    template <class ReturnType = void, class... Args>
    ReturnType safe_lua_call(sol::protected_function callback, Args&&... args)
    {
        const sol::protected_function_result result = callback(args...);
        if (!result.valid())
        {
            if (result.return_count() > 0)
            {
                try
                {
                    const auto err_obj = result.get<sol::error>();
                    throw exceptions::LuaExecutionError(err_obj);
                }
                catch (const sol::error& err)
                {
                    throw exceptions::LuaNestedExceptionError(err);
                }
            }
            else
            {
                const sol::call_status status = result.status();
                const std::string status_str = sol_call_status_to_string(status);
                const std::string error_str = fmt::format("No error, status : '{}'", status_str);
                throw exceptions::LuaExecutionError(std::runtime_error(error_str));
            }
        }
        if constexpr (!std::is_same_v<ReturnType, void>)
        {
            return result.get<ReturnType>();
        }
    }
} // namespace obe::script
