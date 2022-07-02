#pragma once

#include <sol/sol.hpp>
#include <string>

namespace obe::event
{
    class EventGroup;

    /**
     * \proxy{obe::event::EventGroup::add}
     * \rename{add}
     */
    void add_lua_event(EventGroup* self, const std::string& name);
    /**
     * \proxy{obe::event::EventGroup::trigger}
     * \rename{trigger}
     */
    void trigger_lua_event(
        EventGroup* self, const std::string& name, sol::table data = sol::lua_nil);
} // namespace obe::event