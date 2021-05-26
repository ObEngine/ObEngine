#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/TextAreaRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextAreaRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextAreaRenderer> bindTextAreaRenderer
            = tguiNamespace.new_usertype<tgui::TextAreaRenderer>("TextAreaRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindTextAreaRenderer["setBorders"] = &tgui::TextAreaRenderer::setBorders;
        bindTextAreaRenderer["getBorders"] = &tgui::TextAreaRenderer::getBorders;
        bindTextAreaRenderer["setPadding"] = &tgui::TextAreaRenderer::setPadding;
        bindTextAreaRenderer["getPadding"] = &tgui::TextAreaRenderer::getPadding;
        bindTextAreaRenderer["setBackgroundColor"]
            = &tgui::TextAreaRenderer::setBackgroundColor;
        bindTextAreaRenderer["getBackgroundColor"]
            = &tgui::TextAreaRenderer::getBackgroundColor;
        bindTextAreaRenderer["setTextColor"] = &tgui::TextAreaRenderer::setTextColor;
        bindTextAreaRenderer["getTextColor"] = &tgui::TextAreaRenderer::getTextColor;
        bindTextAreaRenderer["setDefaultTextColor"]
            = &tgui::TextAreaRenderer::setDefaultTextColor;
        bindTextAreaRenderer["getDefaultTextColor"]
            = &tgui::TextAreaRenderer::getDefaultTextColor;
        bindTextAreaRenderer["setSelectedTextColor"]
            = &tgui::TextAreaRenderer::setSelectedTextColor;
        bindTextAreaRenderer["getSelectedTextColor"]
            = &tgui::TextAreaRenderer::getSelectedTextColor;
        bindTextAreaRenderer["setSelectedTextBackgroundColor"]
            = &tgui::TextAreaRenderer::setSelectedTextBackgroundColor;
        bindTextAreaRenderer["getSelectedTextBackgroundColor"]
            = &tgui::TextAreaRenderer::getSelectedTextBackgroundColor;
        bindTextAreaRenderer["setBorderColor"] = &tgui::TextAreaRenderer::setBorderColor;
        bindTextAreaRenderer["getBorderColor"] = &tgui::TextAreaRenderer::getBorderColor;
        bindTextAreaRenderer["setCaretColor"] = &tgui::TextAreaRenderer::setCaretColor;
        bindTextAreaRenderer["getCaretColor"] = &tgui::TextAreaRenderer::getCaretColor;
        bindTextAreaRenderer["setTextureBackground"]
            = &tgui::TextAreaRenderer::setTextureBackground;
        bindTextAreaRenderer["getTextureBackground"]
            = &tgui::TextAreaRenderer::getTextureBackground;
        bindTextAreaRenderer["setCaretWidth"] = &tgui::TextAreaRenderer::setCaretWidth;
        bindTextAreaRenderer["getCaretWidth"] = &tgui::TextAreaRenderer::getCaretWidth;
        bindTextAreaRenderer["setScrollbar"] = &tgui::TextAreaRenderer::setScrollbar;
        bindTextAreaRenderer["getScrollbar"] = &tgui::TextAreaRenderer::getScrollbar;
        bindTextAreaRenderer["setScrollbarWidth"]
            = &tgui::TextAreaRenderer::setScrollbarWidth;
        bindTextAreaRenderer["getScrollbarWidth"]
            = &tgui::TextAreaRenderer::getScrollbarWidth;
    }
};