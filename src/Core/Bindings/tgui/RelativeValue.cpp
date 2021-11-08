#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/AbsoluteOrRelativeValue.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRelativeValue(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RelativeValue> bindRelativeValue
            = tguiNamespace.new_usertype<tgui::RelativeValue>("RelativeValue",
                sol::call_constructor, sol::constructors<tgui::RelativeValue(float)>(),
                sol::base_classes, sol::bases<tgui::AbsoluteOrRelativeValue>());
    }
};