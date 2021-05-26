#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Layout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Layout> bindLayout
            = tguiNamespace.new_usertype<tgui::Layout>("Layout", sol::call_constructor,
                sol::constructors<tgui::Layout(), tgui::Layout(const char*),
                    tgui::Layout(tgui::String),
                    tgui::Layout(tgui::Layout::Operation, tgui::Widget*),
                    tgui::Layout(const tgui::Layout&)>());
        bindLayout["operator="] = sol::overload(
            static_cast<tgui::Layout& (tgui::Layout::*)(const tgui::Layout&)>(
                &tgui::Layout::operator=),
            [](tgui::Layout* self, tgui::Layout other) {
                self->operator=(std::move(other));
            });
        bindLayout["getValue"] = &tgui::Layout::getValue;
        bindLayout["isConstant"] = &tgui::Layout::isConstant;
        bindLayout["toString"] = &tgui::Layout::toString;
        bindLayout["connectWidget"] = &tgui::Layout::connectWidget;
        bindLayout["unbindWidget"] = &tgui::Layout::unbindWidget;
        bindLayout["recalculateValue"] = &tgui::Layout::recalculateValue;
    }
};