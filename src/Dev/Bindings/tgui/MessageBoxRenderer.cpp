#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/MessageBoxRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMessageBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MessageBoxRenderer> bindMessageBoxRenderer
            = tguiNamespace.new_usertype<tgui::MessageBoxRenderer>("MessageBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::ChildWindowRenderer, tgui::WidgetRenderer>());
        bindMessageBoxRenderer["setTextColor"] = &tgui::MessageBoxRenderer::setTextColor;
        bindMessageBoxRenderer["getTextColor"] = &tgui::MessageBoxRenderer::getTextColor;
        bindMessageBoxRenderer["setButton"] = &tgui::MessageBoxRenderer::setButton;
        bindMessageBoxRenderer["getButton"] = &tgui::MessageBoxRenderer::getButton;
    }
};