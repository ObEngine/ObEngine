#pragma once

#include <Script/Casters/Base.hpp>

#include <Input/InputSource.hpp>

namespace obe::script
{
    // InputSource
    inline sol::lua_value cast(input::InputSource* ptr)
    {
        return AutoCastManager<input::InputSource>::Cast(ptr);
    }
}