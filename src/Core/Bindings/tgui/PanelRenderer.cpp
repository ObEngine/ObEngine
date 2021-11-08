#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/PanelRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassPanelRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::PanelRenderer> bindPanelRenderer
            = tguiNamespace.new_usertype<tgui::PanelRenderer>("PanelRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::GroupRenderer, tgui::WidgetRenderer>());
        bindPanelRenderer["setBorders"] = &tgui::PanelRenderer::setBorders;
        bindPanelRenderer["getBorders"] = &tgui::PanelRenderer::getBorders;
        bindPanelRenderer["setBorderColor"] = &tgui::PanelRenderer::setBorderColor;
        bindPanelRenderer["getBorderColor"] = &tgui::PanelRenderer::getBorderColor;
        bindPanelRenderer["setBackgroundColor"] = &tgui::PanelRenderer::setBackgroundColor;
        bindPanelRenderer["getBackgroundColor"] = &tgui::PanelRenderer::getBackgroundColor;
        bindPanelRenderer["setTextureBackground"] = &tgui::PanelRenderer::setTextureBackground;
        bindPanelRenderer["getTextureBackground"] = &tgui::PanelRenderer::getTextureBackground;
    }
};