#include <Event/EventGroup.hpp>
#include <Event/LuaEvent.hpp>
#include <Script/ViliLuaBridge.hpp>

namespace obe::event
{
    void add_lua_event(EventGroup* self, const std::string& name)
    {
        self->add<sol::table>(name);
    }

    void trigger_lua_event(EventGroup* self, const std::string& name, sol::table data)
    {
        self->trigger(name, data);
    }
}
