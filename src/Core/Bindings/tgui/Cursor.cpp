#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassCursor(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Cursor> bindCursor = tguiNamespace.new_usertype<tgui::Cursor>(
            "Cursor", sol::call_constructor, sol::default_constructor);
        bindCursor["setStyle"] = &tgui::Cursor::setStyle;
        bindCursor["resetStyle"] = &tgui::Cursor::resetStyle;
    }
};