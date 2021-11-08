#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ChildWindow.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumTitleButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ChildWindow::TitleButton>("TitleButton",
            { { "None", tgui::ChildWindow::TitleButton::None },
                { "Close", tgui::ChildWindow::TitleButton::Close },
                { "Maximize", tgui::ChildWindow::TitleButton::Maximize },
                { "Minimize", tgui::ChildWindow::TitleButton::Minimize } });
    }
};