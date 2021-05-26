#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassEvent(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Event> bindEvent = tguiNamespace.new_usertype<tgui::Event>(
            "Event", sol::call_constructor, sol::default_constructor);
        bindEvent["type"] = &tgui::Event::type;
        bindEvent["key"] = &tgui::Event::key;
        bindEvent["text"] = &tgui::Event::text;
        bindEvent["mouseMove"] = &tgui::Event::mouseMove;
        bindEvent["mouseButton"] = &tgui::Event::mouseButton;
        bindEvent["mouseWheel"] = &tgui::Event::mouseWheel;
        bindEvent["size"] = &tgui::Event::size;
    }
};