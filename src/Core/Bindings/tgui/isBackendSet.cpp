#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Backend.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionIsBackendSet(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("isBackendSet", &tgui::isBackendSet);
    }
};