#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Tabs.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTab(sol::state_view state)
    {
        sol::table TabsNamespace = state["tgui"]["Tabs"].get<sol::table>();
        sol::usertype<tgui::Tabs::Tab> bindTab = TabsNamespace.new_usertype<tgui::Tabs::Tab>(
            "Tab", sol::call_constructor, sol::default_constructor);
        bindTab["visible"] = &tgui::Tabs::Tab::visible;
        bindTab["enabled"] = &tgui::Tabs::Tab::enabled;
        bindTab["width"] = &tgui::Tabs::Tab::width;
        bindTab["text"] = &tgui::Tabs::Tab::text;
    }
};