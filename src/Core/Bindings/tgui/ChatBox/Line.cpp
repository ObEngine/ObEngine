#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ChatBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassLine(sol::state_view state)
    {
        sol::table ChatBoxNamespace = state["tgui"]["ChatBox"].get<sol::table>();
        sol::usertype<tgui::ChatBox::Line> bindLine
            = ChatBoxNamespace.new_usertype<tgui::ChatBox::Line>(
                "Line", sol::call_constructor, sol::default_constructor);
        bindLine["text"] = &tgui::ChatBox::Line::text;
        bindLine["string"] = &tgui::ChatBox::Line::string;
    }
};