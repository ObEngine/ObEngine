#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Backend.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionSetBackend(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("setBackend", tgui::setBackend);
    }
};