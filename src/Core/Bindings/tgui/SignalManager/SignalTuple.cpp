#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/SignalManager.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignalTuple(sol::state_view state)
    {
        sol::table SignalManagerNamespace = state["tgui"]["SignalManager"].get<sol::table>();
        sol::usertype<tgui::SignalManager::SignalTuple> bindSignalTuple
            = SignalManagerNamespace.new_usertype<tgui::SignalManager::SignalTuple>(
                "SignalTuple", sol::call_constructor, sol::default_constructor);
        bindSignalTuple["widgetName"] = &tgui::SignalManager::SignalTuple::widgetName;
        bindSignalTuple["signalName"] = &tgui::SignalManager::SignalTuple::signalName;
        bindSignalTuple["func"] = &tgui::SignalManager::SignalTuple::func;
    }
};