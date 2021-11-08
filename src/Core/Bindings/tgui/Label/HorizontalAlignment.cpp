#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Label.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumHorizontalAlignment(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Label::HorizontalAlignment>("HorizontalAlignment",
            { { "Left", tgui::Label::HorizontalAlignment::Left },
                { "Center", tgui::Label::HorizontalAlignment::Center },
                { "Right", tgui::Label::HorizontalAlignment::Right } });
    }
};