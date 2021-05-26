#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Global.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionIsWhitespace(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("isWhitespace",
            sol::overload(static_cast<bool (*)(char)>(tgui::isWhitespace),
                static_cast<bool (*)(char32_t)>(tgui::isWhitespace)));
    }
};