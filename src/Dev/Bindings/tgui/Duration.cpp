#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Duration.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassDuration(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Duration> bindDuration
            = tguiNamespace.new_usertype<tgui::Duration>("Duration",
                sol::call_constructor,
                sol::constructors<tgui::Duration(), tgui::Duration(int)>());
        bindDuration["asSeconds"] = &tgui::Duration::asSeconds;
    }
};