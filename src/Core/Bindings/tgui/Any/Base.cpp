#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Any.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBase(sol::state_view state)
    {
        sol::table AnyNamespace = state["tgui"]["Any"].get<sol::table>();
        sol::usertype<tgui::Any::Base> bindBase
            = AnyNamespace.new_usertype<tgui::Any::Base>("Base");
        bindBase["clone"] = &tgui::Any::Base::clone;
    }
};