#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/ChildWindowRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassChildWindowRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChildWindowRenderer> bindChildWindowRenderer
            = tguiNamespace.new_usertype<tgui::ChildWindowRenderer>("ChildWindowRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindChildWindowRenderer["setBorders"] = &tgui::ChildWindowRenderer::setBorders;
        bindChildWindowRenderer["getBorders"] = &tgui::ChildWindowRenderer::getBorders;
        bindChildWindowRenderer["setTitleBarHeight"]
            = &tgui::ChildWindowRenderer::setTitleBarHeight;
        bindChildWindowRenderer["getTitleBarHeight"]
            = &tgui::ChildWindowRenderer::getTitleBarHeight;
        bindChildWindowRenderer["setTitleBarColor"] = &tgui::ChildWindowRenderer::setTitleBarColor;
        bindChildWindowRenderer["getTitleBarColor"] = &tgui::ChildWindowRenderer::getTitleBarColor;
        bindChildWindowRenderer["setTitleColor"] = &tgui::ChildWindowRenderer::setTitleColor;
        bindChildWindowRenderer["getTitleColor"] = &tgui::ChildWindowRenderer::getTitleColor;
        bindChildWindowRenderer["setBackgroundColor"]
            = &tgui::ChildWindowRenderer::setBackgroundColor;
        bindChildWindowRenderer["getBackgroundColor"]
            = &tgui::ChildWindowRenderer::getBackgroundColor;
        bindChildWindowRenderer["setBorderColor"] = &tgui::ChildWindowRenderer::setBorderColor;
        bindChildWindowRenderer["getBorderColor"] = &tgui::ChildWindowRenderer::getBorderColor;
        bindChildWindowRenderer["setBorderColorFocused"]
            = &tgui::ChildWindowRenderer::setBorderColorFocused;
        bindChildWindowRenderer["getBorderColorFocused"]
            = &tgui::ChildWindowRenderer::getBorderColorFocused;
        bindChildWindowRenderer["setBorderBelowTitleBar"]
            = &tgui::ChildWindowRenderer::setBorderBelowTitleBar;
        bindChildWindowRenderer["getBorderBelowTitleBar"]
            = &tgui::ChildWindowRenderer::getBorderBelowTitleBar;
        bindChildWindowRenderer["setDistanceToSide"]
            = &tgui::ChildWindowRenderer::setDistanceToSide;
        bindChildWindowRenderer["getDistanceToSide"]
            = &tgui::ChildWindowRenderer::getDistanceToSide;
        bindChildWindowRenderer["setPaddingBetweenButtons"]
            = &tgui::ChildWindowRenderer::setPaddingBetweenButtons;
        bindChildWindowRenderer["getPaddingBetweenButtons"]
            = &tgui::ChildWindowRenderer::getPaddingBetweenButtons;
        bindChildWindowRenderer["setMinimumResizableBorderWidth"]
            = &tgui::ChildWindowRenderer::setMinimumResizableBorderWidth;
        bindChildWindowRenderer["getMinimumResizableBorderWidth"]
            = &tgui::ChildWindowRenderer::getMinimumResizableBorderWidth;
        bindChildWindowRenderer["setShowTextOnTitleButtons"]
            = &tgui::ChildWindowRenderer::setShowTextOnTitleButtons;
        bindChildWindowRenderer["getShowTextOnTitleButtons"]
            = &tgui::ChildWindowRenderer::getShowTextOnTitleButtons;
        bindChildWindowRenderer["setTextureTitleBar"]
            = &tgui::ChildWindowRenderer::setTextureTitleBar;
        bindChildWindowRenderer["getTextureTitleBar"]
            = &tgui::ChildWindowRenderer::getTextureTitleBar;
        bindChildWindowRenderer["setTextureBackground"]
            = &tgui::ChildWindowRenderer::setTextureBackground;
        bindChildWindowRenderer["getTextureBackground"]
            = &tgui::ChildWindowRenderer::getTextureBackground;
        bindChildWindowRenderer["setCloseButton"] = &tgui::ChildWindowRenderer::setCloseButton;
        bindChildWindowRenderer["getCloseButton"] = &tgui::ChildWindowRenderer::getCloseButton;
        bindChildWindowRenderer["setMaximizeButton"]
            = &tgui::ChildWindowRenderer::setMaximizeButton;
        bindChildWindowRenderer["getMaximizeButton"]
            = &tgui::ChildWindowRenderer::getMaximizeButton;
        bindChildWindowRenderer["setMinimizeButton"]
            = &tgui::ChildWindowRenderer::setMinimizeButton;
        bindChildWindowRenderer["getMinimizeButton"]
            = &tgui::ChildWindowRenderer::getMinimizeButton;
    }
};