#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/TextStyle.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextStyles(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextStyles> bindTextStyles
            = tguiNamespace.new_usertype<tgui::TextStyles>("TextStyles", sol::call_constructor,
                sol::constructors<tgui::TextStyles(), tgui::TextStyles(unsigned int),
                    tgui::TextStyles(const tgui::String&), tgui::TextStyles(const char*)>());
        bindTextStyles["isSet"] = &tgui::TextStyles::isSet;
    }
};