#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMouseMoveEvent(sol::state_view state)
    {
        sol::table EventNamespace = state["tgui"]["Event"].get<sol::table>();
        sol::usertype<tgui::Event::MouseMoveEvent> bindMouseMoveEvent
            = EventNamespace.new_usertype<tgui::Event::MouseMoveEvent>(
                "MouseMoveEvent", sol::call_constructor, sol::default_constructor);
        bindMouseMoveEvent["x"] = &tgui::Event::MouseMoveEvent::x;
        bindMouseMoveEvent["y"] = &tgui::Event::MouseMoveEvent::y;
    }
};