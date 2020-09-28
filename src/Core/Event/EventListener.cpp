#include <Event/EventListener.hpp>
#include <Event/Exceptions.hpp>
#include <Utils/StringUtils.hpp>
#include <utility>

namespace obe::Event
{
    LuaEventListener::LuaEventListener(sol::protected_function callback)
        : m_callback(std::move(callback))
    {
    }
}
