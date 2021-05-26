#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/ButtonRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassButtonRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ButtonRenderer> bindButtonRenderer
            = tguiNamespace.new_usertype<tgui::ButtonRenderer>("ButtonRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindButtonRenderer["setBorders"] = &tgui::ButtonRenderer::setBorders;
        bindButtonRenderer["getBorders"] = &tgui::ButtonRenderer::getBorders;
        bindButtonRenderer["setTextColor"] = &tgui::ButtonRenderer::setTextColor;
        bindButtonRenderer["getTextColor"] = &tgui::ButtonRenderer::getTextColor;
        bindButtonRenderer["setTextColorDown"] = &tgui::ButtonRenderer::setTextColorDown;
        bindButtonRenderer["getTextColorDown"] = &tgui::ButtonRenderer::getTextColorDown;
        bindButtonRenderer["setTextColorHover"]
            = &tgui::ButtonRenderer::setTextColorHover;
        bindButtonRenderer["getTextColorHover"]
            = &tgui::ButtonRenderer::getTextColorHover;
        bindButtonRenderer["setTextColorDownHover"]
            = &tgui::ButtonRenderer::setTextColorDownHover;
        bindButtonRenderer["getTextColorDownHover"]
            = &tgui::ButtonRenderer::getTextColorDownHover;
        bindButtonRenderer["setTextColorDisabled"]
            = &tgui::ButtonRenderer::setTextColorDisabled;
        bindButtonRenderer["getTextColorDisabled"]
            = &tgui::ButtonRenderer::getTextColorDisabled;
        bindButtonRenderer["setTextColorDownDisabled"]
            = &tgui::ButtonRenderer::setTextColorDownDisabled;
        bindButtonRenderer["getTextColorDownDisabled"]
            = &tgui::ButtonRenderer::getTextColorDownDisabled;
        bindButtonRenderer["setTextColorFocused"]
            = &tgui::ButtonRenderer::setTextColorFocused;
        bindButtonRenderer["getTextColorFocused"]
            = &tgui::ButtonRenderer::getTextColorFocused;
        bindButtonRenderer["setTextColorDownFocused"]
            = &tgui::ButtonRenderer::setTextColorDownFocused;
        bindButtonRenderer["getTextColorDownFocused"]
            = &tgui::ButtonRenderer::getTextColorDownFocused;
        bindButtonRenderer["setBackgroundColor"]
            = &tgui::ButtonRenderer::setBackgroundColor;
        bindButtonRenderer["getBackgroundColor"]
            = &tgui::ButtonRenderer::getBackgroundColor;
        bindButtonRenderer["setBackgroundColorDown"]
            = &tgui::ButtonRenderer::setBackgroundColorDown;
        bindButtonRenderer["getBackgroundColorDown"]
            = &tgui::ButtonRenderer::getBackgroundColorDown;
        bindButtonRenderer["setBackgroundColorHover"]
            = &tgui::ButtonRenderer::setBackgroundColorHover;
        bindButtonRenderer["getBackgroundColorHover"]
            = &tgui::ButtonRenderer::getBackgroundColorHover;
        bindButtonRenderer["setBackgroundColorDownHover"]
            = &tgui::ButtonRenderer::setBackgroundColorDownHover;
        bindButtonRenderer["getBackgroundColorDownHover"]
            = &tgui::ButtonRenderer::getBackgroundColorDownHover;
        bindButtonRenderer["setBackgroundColorDisabled"]
            = &tgui::ButtonRenderer::setBackgroundColorDisabled;
        bindButtonRenderer["getBackgroundColorDisabled"]
            = &tgui::ButtonRenderer::getBackgroundColorDisabled;
        bindButtonRenderer["setBackgroundColorDownDisabled"]
            = &tgui::ButtonRenderer::setBackgroundColorDownDisabled;
        bindButtonRenderer["getBackgroundColorDownDisabled"]
            = &tgui::ButtonRenderer::getBackgroundColorDownDisabled;
        bindButtonRenderer["setBackgroundColorFocused"]
            = &tgui::ButtonRenderer::setBackgroundColorFocused;
        bindButtonRenderer["getBackgroundColorFocused"]
            = &tgui::ButtonRenderer::getBackgroundColorFocused;
        bindButtonRenderer["setBackgroundColorDownFocused"]
            = &tgui::ButtonRenderer::setBackgroundColorDownFocused;
        bindButtonRenderer["getBackgroundColorDownFocused"]
            = &tgui::ButtonRenderer::getBackgroundColorDownFocused;
        bindButtonRenderer["setBorderColor"] = &tgui::ButtonRenderer::setBorderColor;
        bindButtonRenderer["getBorderColor"] = &tgui::ButtonRenderer::getBorderColor;
        bindButtonRenderer["setBorderColorDown"]
            = &tgui::ButtonRenderer::setBorderColorDown;
        bindButtonRenderer["getBorderColorDown"]
            = &tgui::ButtonRenderer::getBorderColorDown;
        bindButtonRenderer["setBorderColorHover"]
            = &tgui::ButtonRenderer::setBorderColorHover;
        bindButtonRenderer["getBorderColorHover"]
            = &tgui::ButtonRenderer::getBorderColorHover;
        bindButtonRenderer["setBorderColorDownHover"]
            = &tgui::ButtonRenderer::setBorderColorDownHover;
        bindButtonRenderer["getBorderColorDownHover"]
            = &tgui::ButtonRenderer::getBorderColorDownHover;
        bindButtonRenderer["setBorderColorDisabled"]
            = &tgui::ButtonRenderer::setBorderColorDisabled;
        bindButtonRenderer["getBorderColorDisabled"]
            = &tgui::ButtonRenderer::getBorderColorDisabled;
        bindButtonRenderer["setBorderColorDownDisabled"]
            = &tgui::ButtonRenderer::setBorderColorDownDisabled;
        bindButtonRenderer["getBorderColorDownDisabled"]
            = &tgui::ButtonRenderer::getBorderColorDownDisabled;
        bindButtonRenderer["setBorderColorFocused"]
            = &tgui::ButtonRenderer::setBorderColorFocused;
        bindButtonRenderer["getBorderColorFocused"]
            = &tgui::ButtonRenderer::getBorderColorFocused;
        bindButtonRenderer["setBorderColorDownFocused"]
            = &tgui::ButtonRenderer::setBorderColorDownFocused;
        bindButtonRenderer["getBorderColorDownFocused"]
            = &tgui::ButtonRenderer::getBorderColorDownFocused;
        bindButtonRenderer["setTexture"] = &tgui::ButtonRenderer::setTexture;
        bindButtonRenderer["getTexture"] = &tgui::ButtonRenderer::getTexture;
        bindButtonRenderer["setTextureDown"] = &tgui::ButtonRenderer::setTextureDown;
        bindButtonRenderer["getTextureDown"] = &tgui::ButtonRenderer::getTextureDown;
        bindButtonRenderer["setTextureHover"] = &tgui::ButtonRenderer::setTextureHover;
        bindButtonRenderer["getTextureHover"] = &tgui::ButtonRenderer::getTextureHover;
        bindButtonRenderer["setTextureDownHover"]
            = &tgui::ButtonRenderer::setTextureDownHover;
        bindButtonRenderer["getTextureDownHover"]
            = &tgui::ButtonRenderer::getTextureDownHover;
        bindButtonRenderer["setTextureDisabled"]
            = &tgui::ButtonRenderer::setTextureDisabled;
        bindButtonRenderer["getTextureDisabled"]
            = &tgui::ButtonRenderer::getTextureDisabled;
        bindButtonRenderer["setTextureDownDisabled"]
            = &tgui::ButtonRenderer::setTextureDownDisabled;
        bindButtonRenderer["getTextureDownDisabled"]
            = &tgui::ButtonRenderer::getTextureDownDisabled;
        bindButtonRenderer["setTextureFocused"]
            = &tgui::ButtonRenderer::setTextureFocused;
        bindButtonRenderer["getTextureFocused"]
            = &tgui::ButtonRenderer::getTextureFocused;
        bindButtonRenderer["setTextureDownFocused"]
            = &tgui::ButtonRenderer::setTextureDownFocused;
        bindButtonRenderer["getTextureDownFocused"]
            = &tgui::ButtonRenderer::getTextureDownFocused;
        bindButtonRenderer["setTextStyle"] = &tgui::ButtonRenderer::setTextStyle;
        bindButtonRenderer["getTextStyle"] = &tgui::ButtonRenderer::getTextStyle;
        bindButtonRenderer["setTextStyleDown"] = &tgui::ButtonRenderer::setTextStyleDown;
        bindButtonRenderer["getTextStyleDown"] = &tgui::ButtonRenderer::getTextStyleDown;
        bindButtonRenderer["setTextStyleHover"]
            = &tgui::ButtonRenderer::setTextStyleHover;
        bindButtonRenderer["getTextStyleHover"]
            = &tgui::ButtonRenderer::getTextStyleHover;
        bindButtonRenderer["setTextStyleDownHover"]
            = &tgui::ButtonRenderer::setTextStyleDownHover;
        bindButtonRenderer["getTextStyleDownHover"]
            = &tgui::ButtonRenderer::getTextStyleDownHover;
        bindButtonRenderer["setTextStyleDisabled"]
            = &tgui::ButtonRenderer::setTextStyleDisabled;
        bindButtonRenderer["getTextStyleDisabled"]
            = &tgui::ButtonRenderer::getTextStyleDisabled;
        bindButtonRenderer["setTextStyleDownDisabled"]
            = &tgui::ButtonRenderer::setTextStyleDownDisabled;
        bindButtonRenderer["getTextStyleDownDisabled"]
            = &tgui::ButtonRenderer::getTextStyleDownDisabled;
        bindButtonRenderer["setTextStyleFocused"]
            = &tgui::ButtonRenderer::setTextStyleFocused;
        bindButtonRenderer["getTextStyleFocused"]
            = &tgui::ButtonRenderer::getTextStyleFocused;
        bindButtonRenderer["setTextStyleDownFocused"]
            = &tgui::ButtonRenderer::setTextStyleDownFocused;
        bindButtonRenderer["getTextStyleDownFocused"]
            = &tgui::ButtonRenderer::getTextStyleDownFocused;
        bindButtonRenderer["setTextOutlineColor"]
            = &tgui::ButtonRenderer::setTextOutlineColor;
        bindButtonRenderer["getTextOutlineColor"]
            = &tgui::ButtonRenderer::getTextOutlineColor;
        bindButtonRenderer["setTextOutlineThickness"]
            = &tgui::ButtonRenderer::setTextOutlineThickness;
        bindButtonRenderer["getTextOutlineThickness"]
            = &tgui::ButtonRenderer::getTextOutlineThickness;
        bindButtonRenderer["setRoundedBorderRadius"]
            = &tgui::ButtonRenderer::setRoundedBorderRadius;
        bindButtonRenderer["getRoundedBorderRadius"]
            = &tgui::ButtonRenderer::getRoundedBorderRadius;
    }
};