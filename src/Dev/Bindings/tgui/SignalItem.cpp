#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Signal.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignalItem(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalItem> bindSignalItem
            = tguiNamespace.new_usertype<tgui::SignalItem>(
                "SignalItem", sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalItem["emit"] = &tgui::SignalItem::emit;
    }
};