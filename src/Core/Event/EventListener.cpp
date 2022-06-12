#include <utility>

#include <Event/EventListener.hpp>

namespace obe::event
{
    LuaEventListener::LuaEventListener(sol::protected_function callback)
        : m_callback(std::move(callback))
    {
    }
}
