#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/AbsoluteOrRelativeValue.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassAbsoluteOrRelativeValue(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::AbsoluteOrRelativeValue> bindAbsoluteOrRelativeValue
            = tguiNamespace.new_usertype<tgui::AbsoluteOrRelativeValue>("AbsoluteOrRelativeValue",
                sol::call_constructor,
                sol::constructors<tgui::AbsoluteOrRelativeValue(),
                    tgui::AbsoluteOrRelativeValue(const char*),
                    tgui::AbsoluteOrRelativeValue(const tgui::String&)>());
        bindAbsoluteOrRelativeValue["getValue"] = &tgui::AbsoluteOrRelativeValue::getValue;
        bindAbsoluteOrRelativeValue["getRatio"] = &tgui::AbsoluteOrRelativeValue::getRatio;
        bindAbsoluteOrRelativeValue["isConstant"] = &tgui::AbsoluteOrRelativeValue::isConstant;
        bindAbsoluteOrRelativeValue["updateParentSize"]
            = &tgui::AbsoluteOrRelativeValue::updateParentSize;
        bindAbsoluteOrRelativeValue["toString"] = &tgui::AbsoluteOrRelativeValue::toString;
    }
};