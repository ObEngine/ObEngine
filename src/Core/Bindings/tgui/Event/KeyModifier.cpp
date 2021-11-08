#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumKeyModifier(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Event::KeyModifier>("KeyModifier",
            { { "System", tgui::Event::KeyModifier::System },
                { "Control", tgui::Event::KeyModifier::Control },
                { "Shift", tgui::Event::KeyModifier::Shift },
                { "Alt", tgui::Event::KeyModifier::Alt } });
    }
};