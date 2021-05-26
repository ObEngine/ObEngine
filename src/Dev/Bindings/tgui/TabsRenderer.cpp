#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/TabsRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTabsRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TabsRenderer> bindTabsRenderer
            = tguiNamespace.new_usertype<tgui::TabsRenderer>("TabsRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindTabsRenderer["setBorders"] = &tgui::TabsRenderer::setBorders;
        bindTabsRenderer["getBorders"] = &tgui::TabsRenderer::getBorders;
        bindTabsRenderer["setBackgroundColor"] = &tgui::TabsRenderer::setBackgroundColor;
        bindTabsRenderer["getBackgroundColor"] = &tgui::TabsRenderer::getBackgroundColor;
        bindTabsRenderer["setBackgroundColorHover"]
            = &tgui::TabsRenderer::setBackgroundColorHover;
        bindTabsRenderer["getBackgroundColorHover"]
            = &tgui::TabsRenderer::getBackgroundColorHover;
        bindTabsRenderer["setBackgroundColorDisabled"]
            = &tgui::TabsRenderer::setBackgroundColorDisabled;
        bindTabsRenderer["getBackgroundColorDisabled"]
            = &tgui::TabsRenderer::getBackgroundColorDisabled;
        bindTabsRenderer["setSelectedBackgroundColor"]
            = &tgui::TabsRenderer::setSelectedBackgroundColor;
        bindTabsRenderer["getSelectedBackgroundColor"]
            = &tgui::TabsRenderer::getSelectedBackgroundColor;
        bindTabsRenderer["setSelectedBackgroundColorHover"]
            = &tgui::TabsRenderer::setSelectedBackgroundColorHover;
        bindTabsRenderer["getSelectedBackgroundColorHover"]
            = &tgui::TabsRenderer::getSelectedBackgroundColorHover;
        bindTabsRenderer["setTextColor"] = &tgui::TabsRenderer::setTextColor;
        bindTabsRenderer["getTextColor"] = &tgui::TabsRenderer::getTextColor;
        bindTabsRenderer["setTextColorHover"] = &tgui::TabsRenderer::setTextColorHover;
        bindTabsRenderer["getTextColorHover"] = &tgui::TabsRenderer::getTextColorHover;
        bindTabsRenderer["setTextColorDisabled"]
            = &tgui::TabsRenderer::setTextColorDisabled;
        bindTabsRenderer["getTextColorDisabled"]
            = &tgui::TabsRenderer::getTextColorDisabled;
        bindTabsRenderer["setSelectedTextColor"]
            = &tgui::TabsRenderer::setSelectedTextColor;
        bindTabsRenderer["getSelectedTextColor"]
            = &tgui::TabsRenderer::getSelectedTextColor;
        bindTabsRenderer["setSelectedTextColorHover"]
            = &tgui::TabsRenderer::setSelectedTextColorHover;
        bindTabsRenderer["getSelectedTextColorHover"]
            = &tgui::TabsRenderer::getSelectedTextColorHover;
        bindTabsRenderer["setBorderColor"] = &tgui::TabsRenderer::setBorderColor;
        bindTabsRenderer["getBorderColor"] = &tgui::TabsRenderer::getBorderColor;
        bindTabsRenderer["setBorderColorHover"]
            = &tgui::TabsRenderer::setBorderColorHover;
        bindTabsRenderer["getBorderColorHover"]
            = &tgui::TabsRenderer::getBorderColorHover;
        bindTabsRenderer["setSelectedBorderColor"]
            = &tgui::TabsRenderer::setSelectedBorderColor;
        bindTabsRenderer["getSelectedBorderColor"]
            = &tgui::TabsRenderer::getSelectedBorderColor;
        bindTabsRenderer["setSelectedBorderColorHover"]
            = &tgui::TabsRenderer::setSelectedBorderColorHover;
        bindTabsRenderer["getSelectedBorderColorHover"]
            = &tgui::TabsRenderer::getSelectedBorderColorHover;
        bindTabsRenderer["setTextureTab"] = &tgui::TabsRenderer::setTextureTab;
        bindTabsRenderer["getTextureTab"] = &tgui::TabsRenderer::getTextureTab;
        bindTabsRenderer["setTextureTabHover"] = &tgui::TabsRenderer::setTextureTabHover;
        bindTabsRenderer["getTextureTabHover"] = &tgui::TabsRenderer::getTextureTabHover;
        bindTabsRenderer["setTextureSelectedTab"]
            = &tgui::TabsRenderer::setTextureSelectedTab;
        bindTabsRenderer["getTextureSelectedTab"]
            = &tgui::TabsRenderer::getTextureSelectedTab;
        bindTabsRenderer["setTextureSelectedTabHover"]
            = &tgui::TabsRenderer::setTextureSelectedTabHover;
        bindTabsRenderer["getTextureSelectedTabHover"]
            = &tgui::TabsRenderer::getTextureSelectedTabHover;
        bindTabsRenderer["setTextureDisabledTab"]
            = &tgui::TabsRenderer::setTextureDisabledTab;
        bindTabsRenderer["getTextureDisabledTab"]
            = &tgui::TabsRenderer::getTextureDisabledTab;
        bindTabsRenderer["setDistanceToSide"] = &tgui::TabsRenderer::setDistanceToSide;
        bindTabsRenderer["getDistanceToSide"] = &tgui::TabsRenderer::getDistanceToSide;
    }
};