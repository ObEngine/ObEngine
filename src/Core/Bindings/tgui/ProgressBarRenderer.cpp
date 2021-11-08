#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/ProgressBarRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassProgressBarRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ProgressBarRenderer> bindProgressBarRenderer
            = tguiNamespace.new_usertype<tgui::ProgressBarRenderer>("ProgressBarRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindProgressBarRenderer["setBorders"] = &tgui::ProgressBarRenderer::setBorders;
        bindProgressBarRenderer["getBorders"] = &tgui::ProgressBarRenderer::getBorders;
        bindProgressBarRenderer["setTextColor"] = &tgui::ProgressBarRenderer::setTextColor;
        bindProgressBarRenderer["getTextColor"] = &tgui::ProgressBarRenderer::getTextColor;
        bindProgressBarRenderer["setTextColorFilled"]
            = &tgui::ProgressBarRenderer::setTextColorFilled;
        bindProgressBarRenderer["getTextColorFilled"]
            = &tgui::ProgressBarRenderer::getTextColorFilled;
        bindProgressBarRenderer["setBackgroundColor"]
            = &tgui::ProgressBarRenderer::setBackgroundColor;
        bindProgressBarRenderer["getBackgroundColor"]
            = &tgui::ProgressBarRenderer::getBackgroundColor;
        bindProgressBarRenderer["setFillColor"] = &tgui::ProgressBarRenderer::setFillColor;
        bindProgressBarRenderer["getFillColor"] = &tgui::ProgressBarRenderer::getFillColor;
        bindProgressBarRenderer["setBorderColor"] = &tgui::ProgressBarRenderer::setBorderColor;
        bindProgressBarRenderer["getBorderColor"] = &tgui::ProgressBarRenderer::getBorderColor;
        bindProgressBarRenderer["setTextureBackground"]
            = &tgui::ProgressBarRenderer::setTextureBackground;
        bindProgressBarRenderer["getTextureBackground"]
            = &tgui::ProgressBarRenderer::getTextureBackground;
        bindProgressBarRenderer["setTextureFill"] = &tgui::ProgressBarRenderer::setTextureFill;
        bindProgressBarRenderer["getTextureFill"] = &tgui::ProgressBarRenderer::getTextureFill;
        bindProgressBarRenderer["setTextStyle"] = &tgui::ProgressBarRenderer::setTextStyle;
        bindProgressBarRenderer["getTextStyle"] = &tgui::ProgressBarRenderer::getTextStyle;
    }
};