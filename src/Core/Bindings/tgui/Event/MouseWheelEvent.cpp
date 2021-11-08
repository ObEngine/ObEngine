#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMouseWheelEvent(sol::state_view state)
    {
        sol::table EventNamespace = state["tgui"]["Event"].get<sol::table>();
        sol::usertype<tgui::Event::MouseWheelEvent> bindMouseWheelEvent
            = EventNamespace.new_usertype<tgui::Event::MouseWheelEvent>(
                "MouseWheelEvent", sol::call_constructor, sol::default_constructor);
        bindMouseWheelEvent["delta"] = &tgui::Event::MouseWheelEvent::delta;
        bindMouseWheelEvent["x"] = &tgui::Event::MouseWheelEvent::x;
        bindMouseWheelEvent["y"] = &tgui::Event::MouseWheelEvent::y;
    }
};