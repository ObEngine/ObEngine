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
                const auto errObj = result.get<sol::error>();
                const std::string errMsg = "\n        \""
                    + Utils::String::replace(errObj.what(), "\n", "\n        ") + "\"";
                throw Exceptions::LuaExecutionError(errMsg, EXC_INFO);
            }
            else
            {
                throw Exceptions::LuaExecutionError("No error", EXC_INFO);
            }
        }
    }
}
