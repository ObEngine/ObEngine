#pragma once

#include <string>

#include <sol/sol.hpp>

namespace obe::Event
{
    class EventGroup;

    /**
     * \proxy{obe::Event::EventGroup::add}
     * \rename{add}
     */
    void addLuaEvent(EventGroup* self, const std::string& name);
    /**
     * \proxy{obe::Event::EventGroup::trigger}
     * \rename{trigger}
     */
    void triggerLuaEvent(EventGroup* self, const std::string& name, sol::table data = sol::lua_nil);
}