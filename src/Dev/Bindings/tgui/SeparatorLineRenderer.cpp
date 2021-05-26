#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/SeparatorLineRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSeparatorLineRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SeparatorLineRenderer> bindSeparatorLineRenderer
            = tguiNamespace.new_usertype<tgui::SeparatorLineRenderer>(
                "SeparatorLineRenderer", sol::call_constructor, sol::default_constructor,
                sol::base_classes, sol::bases<tgui::WidgetRenderer>());
        bindSeparatorLineRenderer["setColor"] = &tgui::SeparatorLineRenderer::setColor;
        bindSeparatorLineRenderer["getColor"] = &tgui::SeparatorLineRenderer::getColor;
    }
};