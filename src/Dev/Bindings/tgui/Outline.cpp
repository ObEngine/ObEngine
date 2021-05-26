#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Outline.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassOutline(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Outline> bindOutline
            = tguiNamespace.new_usertype<tgui::Outline>("Outline", sol::call_constructor,
                sol::constructors<tgui::Outline(),
                    tgui::Outline(tgui::AbsoluteOrRelativeValue),
                    tgui::Outline(
                        tgui::AbsoluteOrRelativeValue, tgui::AbsoluteOrRelativeValue),
                    tgui::Outline(tgui::AbsoluteOrRelativeValue,
                        tgui::AbsoluteOrRelativeValue, tgui::AbsoluteOrRelativeValue,
                        tgui::AbsoluteOrRelativeValue)>());
        bindOutline["getLeft"] = &tgui::Outline::getLeft;
        bindOutline["getTop"] = &tgui::Outline::getTop;
        bindOutline["getRight"] = &tgui::Outline::getRight;
        bindOutline["getBottom"] = &tgui::Outline::getBottom;
        bindOutline["getOffset"] = &tgui::Outline::getOffset;
        bindOutline[sol::meta_function::equal_to] = &tgui::Outline::operator==;
        bindOutline[sol::meta_function::addition] = &tgui::Outline::operator+;
        bindOutline[sol::meta_function::subtraction] = &tgui::Outline::operator-;
        bindOutline["updateParentSize"] = &tgui::Outline::updateParentSize;
        bindOutline["toString"] = &tgui::Outline::toString;
    }
};