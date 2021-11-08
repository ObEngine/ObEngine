#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/SignalManager.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassConnectedSignalTuple(sol::state_view state)
    {
        sol::table SignalManagerNamespace = state["tgui"]["SignalManager"].get<sol::table>();
        sol::usertype<tgui::SignalManager::ConnectedSignalTuple> bindConnectedSignalTuple
            = SignalManagerNamespace.new_usertype<tgui::SignalManager::ConnectedSignalTuple>(
                "ConnectedSignalTuple", sol::call_constructor, sol::default_constructor);
        bindConnectedSignalTuple["signalId"] = &tgui::SignalManager::ConnectedSignalTuple::signalId;
        bindConnectedSignalTuple["widget"] = &tgui::SignalManager::ConnectedSignalTuple::widget;
        bindConnectedSignalTuple["signalWidgetID"]
            = &tgui::SignalManager::ConnectedSignalTuple::signalWidgetID;
    }
};