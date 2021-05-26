#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/ComboBoxRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassComboBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ComboBoxRenderer> bindComboBoxRenderer
            = tguiNamespace.new_usertype<tgui::ComboBoxRenderer>("ComboBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindComboBoxRenderer["setBorders"] = &tgui::ComboBoxRenderer::setBorders;
        bindComboBoxRenderer["getBorders"] = &tgui::ComboBoxRenderer::getBorders;
        bindComboBoxRenderer["setPadding"] = &tgui::ComboBoxRenderer::setPadding;
        bindComboBoxRenderer["getPadding"] = &tgui::ComboBoxRenderer::getPadding;
        bindComboBoxRenderer["setTextStyle"] = &tgui::ComboBoxRenderer::setTextStyle;
        bindComboBoxRenderer["getTextStyle"] = &tgui::ComboBoxRenderer::getTextStyle;
        bindComboBoxRenderer["setDefaultTextStyle"]
            = &tgui::ComboBoxRenderer::setDefaultTextStyle;
        bindComboBoxRenderer["getDefaultTextStyle"]
            = &tgui::ComboBoxRenderer::getDefaultTextStyle;
        bindComboBoxRenderer["setBackgroundColor"]
            = &tgui::ComboBoxRenderer::setBackgroundColor;
        bindComboBoxRenderer["getBackgroundColor"]
            = &tgui::ComboBoxRenderer::getBackgroundColor;
        bindComboBoxRenderer["setBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::setBackgroundColorDisabled;
        bindComboBoxRenderer["getBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::getBackgroundColorDisabled;
        bindComboBoxRenderer["setTextColor"] = &tgui::ComboBoxRenderer::setTextColor;
        bindComboBoxRenderer["getTextColor"] = &tgui::ComboBoxRenderer::getTextColor;
        bindComboBoxRenderer["setTextColorDisabled"]
            = &tgui::ComboBoxRenderer::setTextColorDisabled;
        bindComboBoxRenderer["getTextColorDisabled"]
            = &tgui::ComboBoxRenderer::getTextColorDisabled;
        bindComboBoxRenderer["setDefaultTextColor"]
            = &tgui::ComboBoxRenderer::setDefaultTextColor;
        bindComboBoxRenderer["getDefaultTextColor"]
            = &tgui::ComboBoxRenderer::getDefaultTextColor;
        bindComboBoxRenderer["setArrowBackgroundColor"]
            = &tgui::ComboBoxRenderer::setArrowBackgroundColor;
        bindComboBoxRenderer["getArrowBackgroundColor"]
            = &tgui::ComboBoxRenderer::getArrowBackgroundColor;
        bindComboBoxRenderer["setArrowBackgroundColorHover"]
            = &tgui::ComboBoxRenderer::setArrowBackgroundColorHover;
        bindComboBoxRenderer["getArrowBackgroundColorHover"]
            = &tgui::ComboBoxRenderer::getArrowBackgroundColorHover;
        bindComboBoxRenderer["setArrowBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::setArrowBackgroundColorDisabled;
        bindComboBoxRenderer["getArrowBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::getArrowBackgroundColorDisabled;
        bindComboBoxRenderer["setArrowColor"] = &tgui::ComboBoxRenderer::setArrowColor;
        bindComboBoxRenderer["getArrowColor"] = &tgui::ComboBoxRenderer::getArrowColor;
        bindComboBoxRenderer["setArrowColorHover"]
            = &tgui::ComboBoxRenderer::setArrowColorHover;
        bindComboBoxRenderer["getArrowColorHover"]
            = &tgui::ComboBoxRenderer::getArrowColorHover;
        bindComboBoxRenderer["setArrowColorDisabled"]
            = &tgui::ComboBoxRenderer::setArrowColorDisabled;
        bindComboBoxRenderer["getArrowColorDisabled"]
            = &tgui::ComboBoxRenderer::getArrowColorDisabled;
        bindComboBoxRenderer["setBorderColor"] = &tgui::ComboBoxRenderer::setBorderColor;
        bindComboBoxRenderer["getBorderColor"] = &tgui::ComboBoxRenderer::getBorderColor;
        bindComboBoxRenderer["setTextureBackground"]
            = &tgui::ComboBoxRenderer::setTextureBackground;
        bindComboBoxRenderer["getTextureBackground"]
            = &tgui::ComboBoxRenderer::getTextureBackground;
        bindComboBoxRenderer["setTextureBackgroundDisabled"]
            = &tgui::ComboBoxRenderer::setTextureBackgroundDisabled;
        bindComboBoxRenderer["getTextureBackgroundDisabled"]
            = &tgui::ComboBoxRenderer::getTextureBackgroundDisabled;
        bindComboBoxRenderer["setTextureArrow"]
            = &tgui::ComboBoxRenderer::setTextureArrow;
        bindComboBoxRenderer["getTextureArrow"]
            = &tgui::ComboBoxRenderer::getTextureArrow;
        bindComboBoxRenderer["setTextureArrowHover"]
            = &tgui::ComboBoxRenderer::setTextureArrowHover;
        bindComboBoxRenderer["getTextureArrowHover"]
            = &tgui::ComboBoxRenderer::getTextureArrowHover;
        bindComboBoxRenderer["setTextureArrowDisabled"]
            = &tgui::ComboBoxRenderer::setTextureArrowDisabled;
        bindComboBoxRenderer["getTextureArrowDisabled"]
            = &tgui::ComboBoxRenderer::getTextureArrowDisabled;
        bindComboBoxRenderer["setListBox"] = &tgui::ComboBoxRenderer::setListBox;
        bindComboBoxRenderer["getListBox"] = &tgui::ComboBoxRenderer::getListBox;
    }
};