#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumType(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Event::Type>("Type",
            { { "LostFocus", tgui::Event::Type::LostFocus },
                { "GainedFocus", tgui::Event::Type::GainedFocus },
                { "TextEntered", tgui::Event::Type::TextEntered },
                { "KeyPressed", tgui::Event::Type::KeyPressed },
                { "MouseWheelScrolled", tgui::Event::Type::MouseWheelScrolled },
                { "MouseButtonPressed", tgui::Event::Type::MouseButtonPressed },
                { "MouseButtonReleased", tgui::Event::Type::MouseButtonReleased },
                { "MouseMoved", tgui::Event::Type::MouseMoved },
                { "Resized", tgui::Event::Type::Resized },
                { "Closed", tgui::Event::Type::Closed } });
    }
};