#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/EditBoxRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassEditBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::EditBoxRenderer> bindEditBoxRenderer
            = tguiNamespace.new_usertype<tgui::EditBoxRenderer>("EditBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindEditBoxRenderer["setTextStyle"] = &tgui::EditBoxRenderer::setTextStyle;
        bindEditBoxRenderer["getTextStyle"] = &tgui::EditBoxRenderer::getTextStyle;
        bindEditBoxRenderer["setDefaultTextStyle"]
            = &tgui::EditBoxRenderer::setDefaultTextStyle;
        bindEditBoxRenderer["getDefaultTextStyle"]
            = &tgui::EditBoxRenderer::getDefaultTextStyle;
        bindEditBoxRenderer["setBorders"] = &tgui::EditBoxRenderer::setBorders;
        bindEditBoxRenderer["getBorders"] = &tgui::EditBoxRenderer::getBorders;
        bindEditBoxRenderer["setPadding"] = &tgui::EditBoxRenderer::setPadding;
        bindEditBoxRenderer["getPadding"] = &tgui::EditBoxRenderer::getPadding;
        bindEditBoxRenderer["setCaretWidth"] = &tgui::EditBoxRenderer::setCaretWidth;
        bindEditBoxRenderer["getCaretWidth"] = &tgui::EditBoxRenderer::getCaretWidth;
        bindEditBoxRenderer["setTextColor"] = &tgui::EditBoxRenderer::setTextColor;
        bindEditBoxRenderer["getTextColor"] = &tgui::EditBoxRenderer::getTextColor;
        bindEditBoxRenderer["setTextColorDisabled"]
            = &tgui::EditBoxRenderer::setTextColorDisabled;
        bindEditBoxRenderer["getTextColorDisabled"]
            = &tgui::EditBoxRenderer::getTextColorDisabled;
        bindEditBoxRenderer["setTextColorFocused"]
            = &tgui::EditBoxRenderer::setTextColorFocused;
        bindEditBoxRenderer["getTextColorFocused"]
            = &tgui::EditBoxRenderer::getTextColorFocused;
        bindEditBoxRenderer["setSelectedTextColor"]
            = &tgui::EditBoxRenderer::setSelectedTextColor;
        bindEditBoxRenderer["getSelectedTextColor"]
            = &tgui::EditBoxRenderer::getSelectedTextColor;
        bindEditBoxRenderer["setSelectedTextBackgroundColor"]
            = &tgui::EditBoxRenderer::setSelectedTextBackgroundColor;
        bindEditBoxRenderer["getSelectedTextBackgroundColor"]
            = &tgui::EditBoxRenderer::getSelectedTextBackgroundColor;
        bindEditBoxRenderer["setDefaultTextColor"]
            = &tgui::EditBoxRenderer::setDefaultTextColor;
        bindEditBoxRenderer["getDefaultTextColor"]
            = &tgui::EditBoxRenderer::getDefaultTextColor;
        bindEditBoxRenderer["setBackgroundColor"]
            = &tgui::EditBoxRenderer::setBackgroundColor;
        bindEditBoxRenderer["getBackgroundColor"]
            = &tgui::EditBoxRenderer::getBackgroundColor;
        bindEditBoxRenderer["setBackgroundColorHover"]
            = &tgui::EditBoxRenderer::setBackgroundColorHover;
        bindEditBoxRenderer["getBackgroundColorHover"]
            = &tgui::EditBoxRenderer::getBackgroundColorHover;
        bindEditBoxRenderer["setBackgroundColorDisabled"]
            = &tgui::EditBoxRenderer::setBackgroundColorDisabled;
        bindEditBoxRenderer["getBackgroundColorDisabled"]
            = &tgui::EditBoxRenderer::getBackgroundColorDisabled;
        bindEditBoxRenderer["setBackgroundColorFocused"]
            = &tgui::EditBoxRenderer::setBackgroundColorFocused;
        bindEditBoxRenderer["getBackgroundColorFocused"]
            = &tgui::EditBoxRenderer::getBackgroundColorFocused;
        bindEditBoxRenderer["setCaretColor"] = &tgui::EditBoxRenderer::setCaretColor;
        bindEditBoxRenderer["getCaretColor"] = &tgui::EditBoxRenderer::getCaretColor;
        bindEditBoxRenderer["setCaretColorHover"]
            = &tgui::EditBoxRenderer::setCaretColorHover;
        bindEditBoxRenderer["getCaretColorHover"]
            = &tgui::EditBoxRenderer::getCaretColorHover;
        bindEditBoxRenderer["setCaretColorFocused"]
            = &tgui::EditBoxRenderer::setCaretColorFocused;
        bindEditBoxRenderer["getCaretColorFocused"]
            = &tgui::EditBoxRenderer::getCaretColorFocused;
        bindEditBoxRenderer["setBorderColor"] = &tgui::EditBoxRenderer::setBorderColor;
        bindEditBoxRenderer["getBorderColor"] = &tgui::EditBoxRenderer::getBorderColor;
        bindEditBoxRenderer["setBorderColorHover"]
            = &tgui::EditBoxRenderer::setBorderColorHover;
        bindEditBoxRenderer["getBorderColorHover"]
            = &tgui::EditBoxRenderer::getBorderColorHover;
        bindEditBoxRenderer["setBorderColorDisabled"]
            = &tgui::EditBoxRenderer::setBorderColorDisabled;
        bindEditBoxRenderer["getBorderColorDisabled"]
            = &tgui::EditBoxRenderer::getBorderColorDisabled;
        bindEditBoxRenderer["setBorderColorFocused"]
            = &tgui::EditBoxRenderer::setBorderColorFocused;
        bindEditBoxRenderer["getBorderColorFocused"]
            = &tgui::EditBoxRenderer::getBorderColorFocused;
        bindEditBoxRenderer["setTexture"] = &tgui::EditBoxRenderer::setTexture;
        bindEditBoxRenderer["getTexture"] = &tgui::EditBoxRenderer::getTexture;
        bindEditBoxRenderer["setTextureHover"] = &tgui::EditBoxRenderer::setTextureHover;
        bindEditBoxRenderer["getTextureHover"] = &tgui::EditBoxRenderer::getTextureHover;
        bindEditBoxRenderer["setTextureDisabled"]
            = &tgui::EditBoxRenderer::setTextureDisabled;
        bindEditBoxRenderer["getTextureDisabled"]
            = &tgui::EditBoxRenderer::getTextureDisabled;
        bindEditBoxRenderer["setTextureFocused"]
            = &tgui::EditBoxRenderer::setTextureFocused;
        bindEditBoxRenderer["getTextureFocused"]
            = &tgui::EditBoxRenderer::getTextureFocused;
    }
};