#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/EditBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumAlignment(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::EditBox::Alignment>("Alignment",
            { { "Left", tgui::EditBox::Alignment::Left },
                { "Center", tgui::EditBox::Alignment::Center },
                { "Right", tgui::EditBox::Alignment::Right } });
    }
};