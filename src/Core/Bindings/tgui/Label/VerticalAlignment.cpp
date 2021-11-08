#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Label.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumVerticalAlignment(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Label::VerticalAlignment>("VerticalAlignment",
            { { "Top", tgui::Label::VerticalAlignment::Top },
                { "Center", tgui::Label::VerticalAlignment::Center },
                { "Bottom", tgui::Label::VerticalAlignment::Bottom } });
    }
};