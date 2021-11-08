#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Any.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionAnyCast(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
    }
};