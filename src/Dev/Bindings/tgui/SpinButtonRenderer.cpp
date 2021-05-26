#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/SpinButtonRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSpinButtonRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SpinButtonRenderer> bindSpinButtonRenderer
            = tguiNamespace.new_usertype<tgui::SpinButtonRenderer>("SpinButtonRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindSpinButtonRenderer["setBorders"] = &tgui::SpinButtonRenderer::setBorders;
        bindSpinButtonRenderer["getBorders"] = &tgui::SpinButtonRenderer::getBorders;
        bindSpinButtonRenderer["setBorderBetweenArrows"]
            = &tgui::SpinButtonRenderer::setBorderBetweenArrows;
        bindSpinButtonRenderer["getBorderBetweenArrows"]
            = &tgui::SpinButtonRenderer::getBorderBetweenArrows;
        bindSpinButtonRenderer["setBackgroundColor"]
            = &tgui::SpinButtonRenderer::setBackgroundColor;
        bindSpinButtonRenderer["getBackgroundColor"]
            = &tgui::SpinButtonRenderer::getBackgroundColor;
        bindSpinButtonRenderer["setBackgroundColorHover"]
            = &tgui::SpinButtonRenderer::setBackgroundColorHover;
        bindSpinButtonRenderer["getBackgroundColorHover"]
            = &tgui::SpinButtonRenderer::getBackgroundColorHover;
        bindSpinButtonRenderer["setArrowColor"]
            = &tgui::SpinButtonRenderer::setArrowColor;
        bindSpinButtonRenderer["getArrowColor"]
            = &tgui::SpinButtonRenderer::getArrowColor;
        bindSpinButtonRenderer["setArrowColorHover"]
            = &tgui::SpinButtonRenderer::setArrowColorHover;
        bindSpinButtonRenderer["getArrowColorHover"]
            = &tgui::SpinButtonRenderer::getArrowColorHover;
        bindSpinButtonRenderer["setBorderColor"]
            = &tgui::SpinButtonRenderer::setBorderColor;
        bindSpinButtonRenderer["getBorderColor"]
            = &tgui::SpinButtonRenderer::getBorderColor;
        bindSpinButtonRenderer["setTextureArrowUp"]
            = &tgui::SpinButtonRenderer::setTextureArrowUp;
        bindSpinButtonRenderer["getTextureArrowUp"]
            = &tgui::SpinButtonRenderer::getTextureArrowUp;
        bindSpinButtonRenderer["setTextureArrowUpHover"]
            = &tgui::SpinButtonRenderer::setTextureArrowUpHover;
        bindSpinButtonRenderer["getTextureArrowUpHover"]
            = &tgui::SpinButtonRenderer::getTextureArrowUpHover;
        bindSpinButtonRenderer["setTextureArrowDown"]
            = &tgui::SpinButtonRenderer::setTextureArrowDown;
        bindSpinButtonRenderer["getTextureArrowDown"]
            = &tgui::SpinButtonRenderer::getTextureArrowDown;
        bindSpinButtonRenderer["setTextureArrowDownHover"]
            = &tgui::SpinButtonRenderer::setTextureArrowDownHover;
        bindSpinButtonRenderer["getTextureArrowDownHover"]
            = &tgui::SpinButtonRenderer::getTextureArrowDownHover;
    }
};