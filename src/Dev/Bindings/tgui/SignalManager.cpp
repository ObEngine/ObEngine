#include <Bindings/tgui/tgui.hpp>

#include <TGUI/SignalManager.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignalManager(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalManager> bindSignalManager
            = tguiNamespace.new_usertype<tgui::SignalManager>("SignalManager",
                sol::call_constructor, sol::constructors<tgui::SignalManager()>());
        bindSignalManager["disconnect"] = &tgui::SignalManager::disconnect;
        bindSignalManager["disconnectAll"] = &tgui::SignalManager::disconnectAll;
        bindSignalManager["add"] = &tgui::SignalManager::add;
        bindSignalManager["remove"] = &tgui::SignalManager::remove;
        bindSignalManager["setDefaultSignalManager"]
            = &tgui::SignalManager::setDefaultSignalManager;
        bindSignalManager["getSignalManager"] = &tgui::SignalManager::getSignalManager;
    }
};