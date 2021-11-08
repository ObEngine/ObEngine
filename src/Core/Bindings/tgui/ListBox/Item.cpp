#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ListBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassItem(sol::state_view state)
    {
        sol::table ListBoxNamespace = state["tgui"]["ListBox"].get<sol::table>();
        sol::usertype<tgui::ListBox::Item> bindItem
            = ListBoxNamespace.new_usertype<tgui::ListBox::Item>(
                "Item", sol::call_constructor, sol::default_constructor);
        bindItem["text"] = &tgui::ListBox::Item::text;
        bindItem["data"] = &tgui::ListBox::Item::data;
        bindItem["id"] = &tgui::ListBox::Item::id;
    }
};