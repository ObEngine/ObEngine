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

    enum class ListenerChangeState
    {
        Added,
        Removed
    };

    using OnListenerChange = std::function<void(ListenerChangeState, const std::string&)>;
} // namespace obe::event
