#pragma once

#include <sol/sol.hpp>

#include <Script/AutoCastManager.hpp>

#define MAKE_CAST(T)                                                                               \
    inline sol::lua_value cast(T* ptr)                                                             \
    {                                                                                              \
        return AutoCastManager<T>::Cast(ptr);                                                      \
    }

namespace obe::script
{
    class DummyCast
    {
    };

    /**
     * \helper{intlibs://Cast.lua}
     */
    inline sol::lua_value cast(DummyCast* ptr)
    {
        return nullptr;
    }
}