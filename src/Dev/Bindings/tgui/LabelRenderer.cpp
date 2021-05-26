#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/LabelRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassLabelRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::LabelRenderer> bindLabelRenderer
            = tguiNamespace.new_usertype<tgui::LabelRenderer>("LabelRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindLabelRenderer["setBorders"] = &tgui::LabelRenderer::setBorders;
        bindLabelRenderer["getBorders"] = &tgui::LabelRenderer::getBorders;
        bindLabelRenderer["setPadding"] = &tgui::LabelRenderer::setPadding;
        bindLabelRenderer["getPadding"] = &tgui::LabelRenderer::getPadding;
        bindLabelRenderer["setTextColor"] = &tgui::LabelRenderer::setTextColor;
        bindLabelRenderer["getTextColor"] = &tgui::LabelRenderer::getTextColor;
        bindLabelRenderer["setBackgroundColor"]
            = &tgui::LabelRenderer::setBackgroundColor;
        bindLabelRenderer["getBackgroundColor"]
            = &tgui::LabelRenderer::getBackgroundColor;
        bindLabelRenderer["setBorderColor"] = &tgui::LabelRenderer::setBorderColor;
        bindLabelRenderer["getBorderColor"] = &tgui::LabelRenderer::getBorderColor;
        bindLabelRenderer["setTextStyle"] = &tgui::LabelRenderer::setTextStyle;
        bindLabelRenderer["getTextStyle"] = &tgui::LabelRenderer::getTextStyle;
        bindLabelRenderer["setTextOutlineColor"]
            = &tgui::LabelRenderer::setTextOutlineColor;
        bindLabelRenderer["getTextOutlineColor"]
            = &tgui::LabelRenderer::getTextOutlineColor;
        bindLabelRenderer["setTextOutlineThickness"]
            = &tgui::LabelRenderer::setTextOutlineThickness;
        bindLabelRenderer["getTextOutlineThickness"]
            = &tgui::LabelRenderer::getTextOutlineThickness;
        bindLabelRenderer["setTextureBackground"]
            = &tgui::LabelRenderer::setTextureBackground;
        bindLabelRenderer["getTextureBackground"]
            = &tgui::LabelRenderer::getTextureBackground;
        bindLabelRenderer["setScrollbar"] = &tgui::LabelRenderer::setScrollbar;
        bindLabelRenderer["getScrollbar"] = &tgui::LabelRenderer::getScrollbar;
        bindLabelRenderer["setScrollbarWidth"] = &tgui::LabelRenderer::setScrollbarWidth;
        bindLabelRenderer["getScrollbarWidth"] = &tgui::LabelRenderer::getScrollbarWidth;
    }
};