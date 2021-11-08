#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Global.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionGetDoubleClickTime(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("getDoubleClickTime", &tgui::getDoubleClickTime);
    }
};