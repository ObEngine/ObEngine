#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSizeEvent(sol::state_view state)
    {
        sol::table EventNamespace = state["tgui"]["Event"].get<sol::table>();
        sol::usertype<tgui::Event::SizeEvent> bindSizeEvent
            = EventNamespace.new_usertype<tgui::Event::SizeEvent>(
                "SizeEvent", sol::call_constructor, sol::default_constructor);
        bindSizeEvent["width"] = &tgui::Event::SizeEvent::width;
        bindSizeEvent["height"] = &tgui::Event::SizeEvent::height;
    }
};