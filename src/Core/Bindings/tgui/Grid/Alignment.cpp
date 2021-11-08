#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Grid.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumAlignment(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Grid::Alignment>("Alignment",
            { { "Center", tgui::Grid::Alignment::Center },
                { "UpperLeft", tgui::Grid::Alignment::UpperLeft },
                { "Up", tgui::Grid::Alignment::Up },
                { "UpperRight", tgui::Grid::Alignment::UpperRight },
                { "Right", tgui::Grid::Alignment::Right },
                { "BottomRight", tgui::Grid::Alignment::BottomRight },
                { "Bottom", tgui::Grid::Alignment::Bottom },
                { "BottomLeft", tgui::Grid::Alignment::BottomLeft },
                { "Left", tgui::Grid::Alignment::Left } });
    }
};