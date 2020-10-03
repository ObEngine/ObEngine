#include <Event/EventListener.hpp>
#include <utility>

namespace obe::Event
{
    LuaEventListener::LuaEventListener(sol::protected_function callback)
        : m_callback(std::move(callback))
    {
    }
}
