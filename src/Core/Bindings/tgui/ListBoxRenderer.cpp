#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/ListBoxRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassListBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListBoxRenderer> bindListBoxRenderer
            = tguiNamespace.new_usertype<tgui::ListBoxRenderer>("ListBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindListBoxRenderer["setBorders"] = &tgui::ListBoxRenderer::setBorders;
        bindListBoxRenderer["getBorders"] = &tgui::ListBoxRenderer::getBorders;
        bindListBoxRenderer["setPadding"] = &tgui::ListBoxRenderer::setPadding;
        bindListBoxRenderer["getPadding"] = &tgui::ListBoxRenderer::getPadding;
        bindListBoxRenderer["setTextStyle"] = &tgui::ListBoxRenderer::setTextStyle;
        bindListBoxRenderer["getTextStyle"] = &tgui::ListBoxRenderer::getTextStyle;
        bindListBoxRenderer["setSelectedTextStyle"] = &tgui::ListBoxRenderer::setSelectedTextStyle;
        bindListBoxRenderer["getSelectedTextStyle"] = &tgui::ListBoxRenderer::getSelectedTextStyle;
        bindListBoxRenderer["setBackgroundColor"] = &tgui::ListBoxRenderer::setBackgroundColor;
        bindListBoxRenderer["getBackgroundColor"] = &tgui::ListBoxRenderer::getBackgroundColor;
        bindListBoxRenderer["setBackgroundColorHover"]
            = &tgui::ListBoxRenderer::setBackgroundColorHover;
        bindListBoxRenderer["getBackgroundColorHover"]
            = &tgui::ListBoxRenderer::getBackgroundColorHover;
        bindListBoxRenderer["setSelectedBackgroundColor"]
            = &tgui::ListBoxRenderer::setSelectedBackgroundColor;
        bindListBoxRenderer["getSelectedBackgroundColor"]
            = &tgui::ListBoxRenderer::getSelectedBackgroundColor;
        bindListBoxRenderer["setSelectedBackgroundColorHover"]
            = &tgui::ListBoxRenderer::setSelectedBackgroundColorHover;
        bindListBoxRenderer["getSelectedBackgroundColorHover"]
            = &tgui::ListBoxRenderer::getSelectedBackgroundColorHover;
        bindListBoxRenderer["setTextColor"] = &tgui::ListBoxRenderer::setTextColor;
        bindListBoxRenderer["getTextColor"] = &tgui::ListBoxRenderer::getTextColor;
        bindListBoxRenderer["setTextColorHover"] = &tgui::ListBoxRenderer::setTextColorHover;
        bindListBoxRenderer["getTextColorHover"] = &tgui::ListBoxRenderer::getTextColorHover;
        bindListBoxRenderer["setSelectedTextColor"] = &tgui::ListBoxRenderer::setSelectedTextColor;
        bindListBoxRenderer["getSelectedTextColor"] = &tgui::ListBoxRenderer::getSelectedTextColor;
        bindListBoxRenderer["setSelectedTextColorHover"]
            = &tgui::ListBoxRenderer::setSelectedTextColorHover;
        bindListBoxRenderer["getSelectedTextColorHover"]
            = &tgui::ListBoxRenderer::getSelectedTextColorHover;
        bindListBoxRenderer["setBorderColor"] = &tgui::ListBoxRenderer::setBorderColor;
        bindListBoxRenderer["getBorderColor"] = &tgui::ListBoxRenderer::getBorderColor;
        bindListBoxRenderer["setTextureBackground"] = &tgui::ListBoxRenderer::setTextureBackground;
        bindListBoxRenderer["getTextureBackground"] = &tgui::ListBoxRenderer::getTextureBackground;
        bindListBoxRenderer["setScrollbar"] = &tgui::ListBoxRenderer::setScrollbar;
        bindListBoxRenderer["getScrollbar"] = &tgui::ListBoxRenderer::getScrollbar;
        bindListBoxRenderer["setScrollbarWidth"] = &tgui::ListBoxRenderer::setScrollbarWidth;
        bindListBoxRenderer["getScrollbarWidth"] = &tgui::ListBoxRenderer::getScrollbarWidth;
    }
};