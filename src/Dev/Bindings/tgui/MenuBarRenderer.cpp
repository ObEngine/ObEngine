#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/MenuBarRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMenuBarRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MenuBarRenderer> bindMenuBarRenderer
            = tguiNamespace.new_usertype<tgui::MenuBarRenderer>("MenuBarRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindMenuBarRenderer["setBackgroundColor"]
            = &tgui::MenuBarRenderer::setBackgroundColor;
        bindMenuBarRenderer["getBackgroundColor"]
            = &tgui::MenuBarRenderer::getBackgroundColor;
        bindMenuBarRenderer["setSelectedBackgroundColor"]
            = &tgui::MenuBarRenderer::setSelectedBackgroundColor;
        bindMenuBarRenderer["getSelectedBackgroundColor"]
            = &tgui::MenuBarRenderer::getSelectedBackgroundColor;
        bindMenuBarRenderer["setTextColor"] = &tgui::MenuBarRenderer::setTextColor;
        bindMenuBarRenderer["getTextColor"] = &tgui::MenuBarRenderer::getTextColor;
        bindMenuBarRenderer["setSelectedTextColor"]
            = &tgui::MenuBarRenderer::setSelectedTextColor;
        bindMenuBarRenderer["getSelectedTextColor"]
            = &tgui::MenuBarRenderer::getSelectedTextColor;
        bindMenuBarRenderer["setTextColorDisabled"]
            = &tgui::MenuBarRenderer::setTextColorDisabled;
        bindMenuBarRenderer["getTextColorDisabled"]
            = &tgui::MenuBarRenderer::getTextColorDisabled;
        bindMenuBarRenderer["setSeparatorColor"]
            = &tgui::MenuBarRenderer::setSeparatorColor;
        bindMenuBarRenderer["getSeparatorColor"]
            = &tgui::MenuBarRenderer::getSeparatorColor;
        bindMenuBarRenderer["setTextureBackground"]
            = &tgui::MenuBarRenderer::setTextureBackground;
        bindMenuBarRenderer["getTextureBackground"]
            = &tgui::MenuBarRenderer::getTextureBackground;
        bindMenuBarRenderer["setTextureItemBackground"]
            = &tgui::MenuBarRenderer::setTextureItemBackground;
        bindMenuBarRenderer["getTextureItemBackground"]
            = &tgui::MenuBarRenderer::getTextureItemBackground;
        bindMenuBarRenderer["setTextureSelectedItemBackground"]
            = &tgui::MenuBarRenderer::setTextureSelectedItemBackground;
        bindMenuBarRenderer["getTextureSelectedItemBackground"]
            = &tgui::MenuBarRenderer::getTextureSelectedItemBackground;
        bindMenuBarRenderer["setDistanceToSide"]
            = &tgui::MenuBarRenderer::setDistanceToSide;
        bindMenuBarRenderer["getDistanceToSide"]
            = &tgui::MenuBarRenderer::getDistanceToSide;
        bindMenuBarRenderer["setSeparatorThickness"]
            = &tgui::MenuBarRenderer::setSeparatorThickness;
        bindMenuBarRenderer["getSeparatorThickness"]
            = &tgui::MenuBarRenderer::getSeparatorThickness;
        bindMenuBarRenderer["setSeparatorVerticalPadding"]
            = &tgui::MenuBarRenderer::setSeparatorVerticalPadding;
        bindMenuBarRenderer["getSeparatorVerticalPadding"]
            = &tgui::MenuBarRenderer::getSeparatorVerticalPadding;
        bindMenuBarRenderer["setSeparatorSidePadding"]
            = &tgui::MenuBarRenderer::setSeparatorSidePadding;
        bindMenuBarRenderer["getSeparatorSidePadding"]
            = &tgui::MenuBarRenderer::getSeparatorSidePadding;
    }
};