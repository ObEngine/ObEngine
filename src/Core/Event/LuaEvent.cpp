#include <Event/EventGroup.hpp>
#include <Event/LuaEvent.hpp>
#include <Script/ViliLuaBridge.hpp>

namespace obe::Event
{
    void addLuaEvent(EventGroup* self, const std::string& name)
    {
        self->add<sol::table>(name);
    }

    void triggerLuaEvent(EventGroup* self, const std::string& name, sol::table data)
    {
        self->trigger(name, data);
    }
}
