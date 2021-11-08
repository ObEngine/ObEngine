#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/ToolTip.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassToolTip(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ToolTip> bindToolTip = tguiNamespace.new_usertype<tgui::ToolTip>(
            "ToolTip", sol::call_constructor, sol::default_constructor);
        bindToolTip["setInitialDelay"] = &tgui::ToolTip::setInitialDelay;
        bindToolTip["getInitialDelay"] = &tgui::ToolTip::getInitialDelay;
        bindToolTip["setDistanceToMouse"] = &tgui::ToolTip::setDistanceToMouse;
        bindToolTip["getDistanceToMouse"] = &tgui::ToolTip::getDistanceToMouse;
    }
};