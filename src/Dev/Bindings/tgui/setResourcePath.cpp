#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Global.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionSetResourcePath(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("setResourcePath",
            sol::overload(static_cast<void (*)(const tgui::Filesystem::Path&)>(
                              tgui::setResourcePath),
                static_cast<void (*)(const tgui::String&)>(tgui::setResourcePath)));
    }
};