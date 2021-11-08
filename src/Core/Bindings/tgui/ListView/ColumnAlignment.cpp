#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ListView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumColumnAlignment(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ListView::ColumnAlignment>("ColumnAlignment",
            { { "Left", tgui::ListView::ColumnAlignment::Left },
                { "Center", tgui::ListView::ColumnAlignment::Center },
                { "Right", tgui::ListView::ColumnAlignment::Right } });
    }
};