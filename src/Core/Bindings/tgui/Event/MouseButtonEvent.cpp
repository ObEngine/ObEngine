#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMouseButtonEvent(sol::state_view state)
    {
        sol::table EventNamespace = state["tgui"]["Event"].get<sol::table>();
        sol::usertype<tgui::Event::MouseButtonEvent> bindMouseButtonEvent
            = EventNamespace.new_usertype<tgui::Event::MouseButtonEvent>(
                "MouseButtonEvent", sol::call_constructor, sol::default_constructor);
        bindMouseButtonEvent["button"] = &tgui::Event::MouseButtonEvent::button;
        bindMouseButtonEvent["x"] = &tgui::Event::MouseButtonEvent::x;
        bindMouseButtonEvent["y"] = &tgui::Event::MouseButtonEvent::y;
    }
};