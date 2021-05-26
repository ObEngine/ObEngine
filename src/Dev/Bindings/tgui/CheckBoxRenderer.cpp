#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/CheckBoxRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassCheckBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::CheckBoxRenderer> bindCheckBoxRenderer
            = tguiNamespace.new_usertype<tgui::CheckBoxRenderer>("CheckBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::RadioButtonRenderer, tgui::WidgetRenderer>());
    }
};