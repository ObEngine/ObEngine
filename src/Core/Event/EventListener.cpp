#include <utility>

#include <Event/EventListener.hpp>

namespace obe::Event
{
    LuaEventListener::LuaEventListener(sol::protected_function callback)
        : m_callback(std::move(callback))
    {
    }
}
