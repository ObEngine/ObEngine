#pragma once

#include <functional>
#include <string>

#include <sol/sol.hpp>

#include <Event/Exceptions.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Event
{
    template <class EventType>
    using CppEventListener = std::function<void(const EventType&)>;

    class LuaEventListener
    {
    private:
        sol::protected_function m_callback;

    public:
        LuaEventListener(sol::protected_function callback);

        template <class EventType> void operator()(const EventType& event) const;
    };

    template <class EventType>
    void LuaEventListener::operator()(const EventType& event) const
    {
        const sol::protected_function_result result = m_callback(event);
        if (!result.valid())
        {
            const auto errObj = result.get<sol::error>();
            const std::string errMsg = "\n        \""
                + Utils::String::replace(errObj.what(), "\n", "\n        ") + "\"";
            throw Exceptions::LuaExecutionError(errMsg, EXC_INFO);
        }
    }

    using ExternalEventListener = std::variant<LuaEventListener>;

    enum class ListenerChangeState
    {
        Added,
        Removed
    };

    using OnListenerChange = std::function<void(ListenerChangeState, const std::string&)>;
}
