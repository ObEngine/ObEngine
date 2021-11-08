#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/TextStyle.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumTextStyle(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::TextStyle>("TextStyle",
            { { "Regular", tgui::TextStyle::Regular }, { "Bold", tgui::TextStyle::Bold },
                { "Italic", tgui::TextStyle::Italic },
                { "Underlined", tgui::TextStyle::Underlined },
                { "StrikeThrough", tgui::TextStyle::StrikeThrough } });
    }
};