#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Global.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionGetResourcePath(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("getResourcePath", tgui::getResourcePath);
    }
};