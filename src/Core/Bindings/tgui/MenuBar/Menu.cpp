#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/MenuBar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMenu(sol::state_view state)
    {
        sol::table MenuBarNamespace = state["tgui"]["MenuBar"].get<sol::table>();
        sol::usertype<tgui::MenuBar::Menu> bindMenu
            = MenuBarNamespace.new_usertype<tgui::MenuBar::Menu>(
                "Menu", sol::call_constructor, sol::default_constructor);
        bindMenu["text"] = &tgui::MenuBar::Menu::text;
        bindMenu["enabled"] = &tgui::MenuBar::Menu::enabled;
        bindMenu["selectedMenuItem"] = &tgui::MenuBar::Menu::selectedMenuItem;
        bindMenu["menuItems"] = &tgui::MenuBar::Menu::menuItems;
    }
};