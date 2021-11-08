#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassKeyEvent(sol::state_view state)
    {
        sol::table EventNamespace = state["tgui"]["Event"].get<sol::table>();
        sol::usertype<tgui::Event::KeyEvent> bindKeyEvent
            = EventNamespace.new_usertype<tgui::Event::KeyEvent>(
                "KeyEvent", sol::call_constructor, sol::default_constructor);
        bindKeyEvent["code"] = &tgui::Event::KeyEvent::code;
        bindKeyEvent["alt"] = &tgui::Event::KeyEvent::alt;
        bindKeyEvent["control"] = &tgui::Event::KeyEvent::control;
        bindKeyEvent["shift"] = &tgui::Event::KeyEvent::shift;
        bindKeyEvent["system"] = &tgui::Event::KeyEvent::system;
    }
};