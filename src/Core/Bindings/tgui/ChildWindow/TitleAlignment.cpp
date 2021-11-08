#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ChildWindow.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumTitleAlignment(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ChildWindow::TitleAlignment>("TitleAlignment",
            { { "Left", tgui::ChildWindow::TitleAlignment::Left },
                { "Center", tgui::ChildWindow::TitleAlignment::Center },
                { "Right", tgui::ChildWindow::TitleAlignment::Right } });
    }
};