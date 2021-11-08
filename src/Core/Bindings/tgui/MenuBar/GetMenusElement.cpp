#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/MenuBar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassGetMenusElement(sol::state_view state)
    {
        sol::table MenuBarNamespace = state["tgui"]["MenuBar"].get<sol::table>();
        sol::usertype<tgui::MenuBar::GetMenusElement> bindGetMenusElement
            = MenuBarNamespace.new_usertype<tgui::MenuBar::GetMenusElement>(
                "GetMenusElement", sol::call_constructor, sol::default_constructor);
        bindGetMenusElement["text"] = &tgui::MenuBar::GetMenusElement::text;
        bindGetMenusElement["enabled"] = &tgui::MenuBar::GetMenusElement::enabled;
        bindGetMenusElement["menuItems"] = &tgui::MenuBar::GetMenusElement::menuItems;
    }
};