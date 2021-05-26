#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Any.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassAny(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Any> bindAny
            = tguiNamespace.new_usertype<tgui::Any>("Any", sol::call_constructor,
                sol::constructors<tgui::Any(), tgui::Any(const tgui::Any&)>());
        bindAny["is_null"] = &tgui::Any::is_null;
        bindAny["not_null"] = &tgui::Any::not_null;
        bindAny["operator="]
            = sol::overload(static_cast<tgui::Any& (tgui::Any::*)(const tgui::Any&)>(
                                &tgui::Any::operator=),
                [](tgui::Any* self, tgui::Any a) { self->operator=(std::move(a)); });
    }
};