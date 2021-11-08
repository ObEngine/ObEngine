#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Signal.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignalItemHierarchy(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalItemHierarchy> bindSignalItemHierarchy
            = tguiNamespace.new_usertype<tgui::SignalItemHierarchy>(
                "SignalItemHierarchy", sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalItemHierarchy["emit"] = &tgui::SignalItemHierarchy::emit;
    }
};