#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextEvent(sol::state_view state)
    {
        sol::table EventNamespace = state["tgui"]["Event"].get<sol::table>();
        sol::usertype<tgui::Event::TextEvent> bindTextEvent
            = EventNamespace.new_usertype<tgui::Event::TextEvent>(
                "TextEvent", sol::call_constructor, sol::default_constructor);
        bindTextEvent["unicode"] = &tgui::Event::TextEvent::unicode;
    }
};