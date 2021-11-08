#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ListView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassColumn(sol::state_view state)
    {
        sol::table ListViewNamespace = state["tgui"]["ListView"].get<sol::table>();
        sol::usertype<tgui::ListView::Column> bindColumn
            = ListViewNamespace.new_usertype<tgui::ListView::Column>(
                "Column", sol::call_constructor, sol::default_constructor);
        bindColumn["width"] = &tgui::ListView::Column::width;
        bindColumn["designWidth"] = &tgui::ListView::Column::designWidth;
        bindColumn["maxItemWidth"] = &tgui::ListView::Column::maxItemWidth;
        bindColumn["text"] = &tgui::ListView::Column::text;
        bindColumn["alignment"] = &tgui::ListView::Column::alignment;
    }
};