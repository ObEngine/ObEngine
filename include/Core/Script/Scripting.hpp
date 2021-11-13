#pragma once

#include <sol/sol.hpp>

#include <Script/Exceptions.hpp>

namespace obe::Script
{
    template <class... Args>
    void safeLuaCall(sol::protected_function callback, Args&&... args)
    {
        if (const sol::protected_function_result result = callback(args...); !result.valid())
        {
            if (result.return_count() > 0)
            {
                try
                {
                    const auto errObj = result.get<sol::error>();
                    throw Exceptions::LuaExecutionError(errObj, EXC_INFO);
                }
                catch (const sol::error& err)
                {
                    throw Exceptions::LuaNestedExceptionError(err, EXC_INFO);
                }
            }
            else
            {
                throw Exceptions::LuaExecutionError(std::runtime_error("No error"), EXC_INFO);
            }
        }
    }
}
