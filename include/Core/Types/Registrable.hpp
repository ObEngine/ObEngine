#pragma once

#include <kaguya/kaguya.hpp>

#include <Script/GlobalState.hpp>

namespace obe::Types
{
    template <class T> class Registrable
    {
    public:
        Registrable(const std::string& id)
        {
            Script::ScriptEngine[id] = static_cast<T*>(this);
        }
    };
} // namespace obe::Types