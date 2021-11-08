#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ListView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassItem(sol::state_view state)
    {
        sol::table ListViewNamespace = state["tgui"]["ListView"].get<sol::table>();
        sol::usertype<tgui::ListView::Item> bindItem
            = ListViewNamespace.new_usertype<tgui::ListView::Item>(
                "Item", sol::call_constructor, sol::default_constructor);
        bindItem["texts"] = &tgui::ListView::Item::texts;
        bindItem["data"] = &tgui::ListView::Item::data;
        bindItem["icon"] = &tgui::ListView::Item::icon;
    }
};