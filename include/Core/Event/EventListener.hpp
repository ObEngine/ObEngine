#pragma once

#include <Script/Scripting.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <functional>
#include <string>

namespace obe::event
{
    /**
     * \nobind
     */
    template <class EventType>
    using CppEventListener = std::function<void(const EventType&)>;

    class LuaEventListener
    {
    private:
        sol::protected_function m_callback;

    public:
        LuaEventListener(sol::protected_function callback);
        template <class EventType>
        void operator()(const EventType& event) const;
    };

    template <class EventType>
    void LuaEventListener::operator()(const EventType& event) const
    {
        script::safe_lua_call(m_callback, event);
    }

    using ExternalEventListener = std::variant<LuaEventListener>;

    enum class ListenerChangeState
    {
        Added,
        Removed
    };

    using OnListenerChange = std::function<void(ListenerChangeState, const std::string&)>;
} // namespace obe::event
