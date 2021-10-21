#include <Event/EventGroup.hpp>
#include <Event/LuaEvent.hpp>
#include <Script/ViliLuaBridge.hpp>

namespace obe::Event
{
    void addLuaEvent(obe::Event::EventGroup* self, const std::string& name)
    {
        self->add<sol::table>(name);
    }

    void triggerLuaEvent(obe::Event::EventGroup* self, const std::string& name, sol::table data)
    {
        self->trigger(name, data);
    }

    void addUniversalEvent(obe::Event::EventGroup* self, const std::string& name)
    {
        self->add<vili::node>(name);
    }

    void triggerUniversalEvent(obe::Event::EventGroup* self, const std::string& name,
        sol::table data)
    {
        self->trigger(name, Script::ViliLuaBridge::luaToVili(data));
    }
}
