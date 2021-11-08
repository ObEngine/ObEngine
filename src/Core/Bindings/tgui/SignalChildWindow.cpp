#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Signal.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignalChildWindow(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalChildWindow> bindSignalChildWindow
            = tguiNamespace.new_usertype<tgui::SignalChildWindow>(
                "SignalChildWindow", sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalChildWindow["emit"] = &tgui::SignalChildWindow::emit;
    }
};