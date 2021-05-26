#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/RadioButtonRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRadioButtonRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RadioButtonRenderer> bindRadioButtonRenderer
            = tguiNamespace.new_usertype<tgui::RadioButtonRenderer>("RadioButtonRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindRadioButtonRenderer["setBorders"] = &tgui::RadioButtonRenderer::setBorders;
        bindRadioButtonRenderer["getBorders"] = &tgui::RadioButtonRenderer::getBorders;
        bindRadioButtonRenderer["setTextDistanceRatio"]
            = &tgui::RadioButtonRenderer::setTextDistanceRatio;
        bindRadioButtonRenderer["getTextDistanceRatio"]
            = &tgui::RadioButtonRenderer::getTextDistanceRatio;
        bindRadioButtonRenderer["setTextColor"]
            = &tgui::RadioButtonRenderer::setTextColor;
        bindRadioButtonRenderer["getTextColor"]
            = &tgui::RadioButtonRenderer::getTextColor;
        bindRadioButtonRenderer["setTextColorHover"]
            = &tgui::RadioButtonRenderer::setTextColorHover;
        bindRadioButtonRenderer["getTextColorHover"]
            = &tgui::RadioButtonRenderer::getTextColorHover;
        bindRadioButtonRenderer["setTextColorDisabled"]
            = &tgui::RadioButtonRenderer::setTextColorDisabled;
        bindRadioButtonRenderer["getTextColorDisabled"]
            = &tgui::RadioButtonRenderer::getTextColorDisabled;
        bindRadioButtonRenderer["setTextColorChecked"]
            = &tgui::RadioButtonRenderer::setTextColorChecked;
        bindRadioButtonRenderer["getTextColorChecked"]
            = &tgui::RadioButtonRenderer::getTextColorChecked;
        bindRadioButtonRenderer["setTextColorCheckedHover"]
            = &tgui::RadioButtonRenderer::setTextColorCheckedHover;
        bindRadioButtonRenderer["getTextColorCheckedHover"]
            = &tgui::RadioButtonRenderer::getTextColorCheckedHover;
        bindRadioButtonRenderer["setTextColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setTextColorCheckedDisabled;
        bindRadioButtonRenderer["getTextColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getTextColorCheckedDisabled;
        bindRadioButtonRenderer["setBackgroundColor"]
            = &tgui::RadioButtonRenderer::setBackgroundColor;
        bindRadioButtonRenderer["getBackgroundColor"]
            = &tgui::RadioButtonRenderer::getBackgroundColor;
        bindRadioButtonRenderer["setBackgroundColorHover"]
            = &tgui::RadioButtonRenderer::setBackgroundColorHover;
        bindRadioButtonRenderer["getBackgroundColorHover"]
            = &tgui::RadioButtonRenderer::getBackgroundColorHover;
        bindRadioButtonRenderer["setBackgroundColorDisabled"]
            = &tgui::RadioButtonRenderer::setBackgroundColorDisabled;
        bindRadioButtonRenderer["getBackgroundColorDisabled"]
            = &tgui::RadioButtonRenderer::getBackgroundColorDisabled;
        bindRadioButtonRenderer["setBackgroundColorChecked"]
            = &tgui::RadioButtonRenderer::setBackgroundColorChecked;
        bindRadioButtonRenderer["getBackgroundColorChecked"]
            = &tgui::RadioButtonRenderer::getBackgroundColorChecked;
        bindRadioButtonRenderer["setBackgroundColorCheckedHover"]
            = &tgui::RadioButtonRenderer::setBackgroundColorCheckedHover;
        bindRadioButtonRenderer["getBackgroundColorCheckedHover"]
            = &tgui::RadioButtonRenderer::getBackgroundColorCheckedHover;
        bindRadioButtonRenderer["setBackgroundColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setBackgroundColorCheckedDisabled;
        bindRadioButtonRenderer["getBackgroundColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getBackgroundColorCheckedDisabled;
        bindRadioButtonRenderer["setBorderColor"]
            = &tgui::RadioButtonRenderer::setBorderColor;
        bindRadioButtonRenderer["getBorderColor"]
            = &tgui::RadioButtonRenderer::getBorderColor;
        bindRadioButtonRenderer["setBorderColorHover"]
            = &tgui::RadioButtonRenderer::setBorderColorHover;
        bindRadioButtonRenderer["getBorderColorHover"]
            = &tgui::RadioButtonRenderer::getBorderColorHover;
        bindRadioButtonRenderer["setBorderColorDisabled"]
            = &tgui::RadioButtonRenderer::setBorderColorDisabled;
        bindRadioButtonRenderer["getBorderColorDisabled"]
            = &tgui::RadioButtonRenderer::getBorderColorDisabled;
        bindRadioButtonRenderer["setBorderColorFocused"]
            = &tgui::RadioButtonRenderer::setBorderColorFocused;
        bindRadioButtonRenderer["getBorderColorFocused"]
            = &tgui::RadioButtonRenderer::getBorderColorFocused;
        bindRadioButtonRenderer["setBorderColorChecked"]
            = &tgui::RadioButtonRenderer::setBorderColorChecked;
        bindRadioButtonRenderer["getBorderColorChecked"]
            = &tgui::RadioButtonRenderer::getBorderColorChecked;
        bindRadioButtonRenderer["setBorderColorCheckedHover"]
            = &tgui::RadioButtonRenderer::setBorderColorCheckedHover;
        bindRadioButtonRenderer["getBorderColorCheckedHover"]
            = &tgui::RadioButtonRenderer::getBorderColorCheckedHover;
        bindRadioButtonRenderer["setBorderColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setBorderColorCheckedDisabled;
        bindRadioButtonRenderer["getBorderColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getBorderColorCheckedDisabled;
        bindRadioButtonRenderer["setBorderColorCheckedFocused"]
            = &tgui::RadioButtonRenderer::setBorderColorCheckedFocused;
        bindRadioButtonRenderer["getBorderColorCheckedFocused"]
            = &tgui::RadioButtonRenderer::getBorderColorCheckedFocused;
        bindRadioButtonRenderer["setCheckColor"]
            = &tgui::RadioButtonRenderer::setCheckColor;
        bindRadioButtonRenderer["getCheckColor"]
            = &tgui::RadioButtonRenderer::getCheckColor;
        bindRadioButtonRenderer["setCheckColorHover"]
            = &tgui::RadioButtonRenderer::setCheckColorHover;
        bindRadioButtonRenderer["getCheckColorHover"]
            = &tgui::RadioButtonRenderer::getCheckColorHover;
        bindRadioButtonRenderer["setCheckColorDisabled"]
            = &tgui::RadioButtonRenderer::setCheckColorDisabled;
        bindRadioButtonRenderer["getCheckColorDisabled"]
            = &tgui::RadioButtonRenderer::getCheckColorDisabled;
        bindRadioButtonRenderer["setTextureUnchecked"]
            = &tgui::RadioButtonRenderer::setTextureUnchecked;
        bindRadioButtonRenderer["getTextureUnchecked"]
            = &tgui::RadioButtonRenderer::getTextureUnchecked;
        bindRadioButtonRenderer["setTextureChecked"]
            = &tgui::RadioButtonRenderer::setTextureChecked;
        bindRadioButtonRenderer["getTextureChecked"]
            = &tgui::RadioButtonRenderer::getTextureChecked;
        bindRadioButtonRenderer["setTextureUncheckedHover"]
            = &tgui::RadioButtonRenderer::setTextureUncheckedHover;
        bindRadioButtonRenderer["getTextureUncheckedHover"]
            = &tgui::RadioButtonRenderer::getTextureUncheckedHover;
        bindRadioButtonRenderer["setTextureCheckedHover"]
            = &tgui::RadioButtonRenderer::setTextureCheckedHover;
        bindRadioButtonRenderer["getTextureCheckedHover"]
            = &tgui::RadioButtonRenderer::getTextureCheckedHover;
        bindRadioButtonRenderer["setTextureUncheckedDisabled"]
            = &tgui::RadioButtonRenderer::setTextureUncheckedDisabled;
        bindRadioButtonRenderer["getTextureUncheckedDisabled"]
            = &tgui::RadioButtonRenderer::getTextureUncheckedDisabled;
        bindRadioButtonRenderer["setTextureCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setTextureCheckedDisabled;
        bindRadioButtonRenderer["getTextureCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getTextureCheckedDisabled;
        bindRadioButtonRenderer["setTextureUncheckedFocused"]
            = &tgui::RadioButtonRenderer::setTextureUncheckedFocused;
        bindRadioButtonRenderer["getTextureUncheckedFocused"]
            = &tgui::RadioButtonRenderer::getTextureUncheckedFocused;
        bindRadioButtonRenderer["setTextureCheckedFocused"]
            = &tgui::RadioButtonRenderer::setTextureCheckedFocused;
        bindRadioButtonRenderer["getTextureCheckedFocused"]
            = &tgui::RadioButtonRenderer::getTextureCheckedFocused;
        bindRadioButtonRenderer["setTextStyle"]
            = &tgui::RadioButtonRenderer::setTextStyle;
        bindRadioButtonRenderer["getTextStyle"]
            = &tgui::RadioButtonRenderer::getTextStyle;
        bindRadioButtonRenderer["setTextStyleChecked"]
            = &tgui::RadioButtonRenderer::setTextStyleChecked;
        bindRadioButtonRenderer["getTextStyleChecked"]
            = &tgui::RadioButtonRenderer::getTextStyleChecked;
    }
};