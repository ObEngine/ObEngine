#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Event.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumMouseButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Event::MouseButton>("MouseButton",
            { { "Left", tgui::Event::MouseButton::Left },
                { "Right", tgui::Event::MouseButton::Right },
                { "Middle", tgui::Event::MouseButton::Middle } });
    }
};