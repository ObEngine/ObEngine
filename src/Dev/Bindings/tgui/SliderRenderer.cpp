#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/SliderRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSliderRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SliderRenderer> bindSliderRenderer
            = tguiNamespace.new_usertype<tgui::SliderRenderer>("SliderRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindSliderRenderer["setBorders"] = &tgui::SliderRenderer::setBorders;
        bindSliderRenderer["getBorders"] = &tgui::SliderRenderer::getBorders;
        bindSliderRenderer["setTrackColor"] = &tgui::SliderRenderer::setTrackColor;
        bindSliderRenderer["getTrackColor"] = &tgui::SliderRenderer::getTrackColor;
        bindSliderRenderer["setTrackColorHover"]
            = &tgui::SliderRenderer::setTrackColorHover;
        bindSliderRenderer["getTrackColorHover"]
            = &tgui::SliderRenderer::getTrackColorHover;
        bindSliderRenderer["setThumbColor"] = &tgui::SliderRenderer::setThumbColor;
        bindSliderRenderer["getThumbColor"] = &tgui::SliderRenderer::getThumbColor;
        bindSliderRenderer["setThumbColorHover"]
            = &tgui::SliderRenderer::setThumbColorHover;
        bindSliderRenderer["getThumbColorHover"]
            = &tgui::SliderRenderer::getThumbColorHover;
        bindSliderRenderer["setBorderColor"] = &tgui::SliderRenderer::setBorderColor;
        bindSliderRenderer["getBorderColor"] = &tgui::SliderRenderer::getBorderColor;
        bindSliderRenderer["setBorderColorHover"]
            = &tgui::SliderRenderer::setBorderColorHover;
        bindSliderRenderer["getBorderColorHover"]
            = &tgui::SliderRenderer::getBorderColorHover;
        bindSliderRenderer["setTextureTrack"] = &tgui::SliderRenderer::setTextureTrack;
        bindSliderRenderer["getTextureTrack"] = &tgui::SliderRenderer::getTextureTrack;
        bindSliderRenderer["setTextureTrackHover"]
            = &tgui::SliderRenderer::setTextureTrackHover;
        bindSliderRenderer["getTextureTrackHover"]
            = &tgui::SliderRenderer::getTextureTrackHover;
        bindSliderRenderer["setTextureThumb"] = &tgui::SliderRenderer::setTextureThumb;
        bindSliderRenderer["getTextureThumb"] = &tgui::SliderRenderer::getTextureThumb;
        bindSliderRenderer["setTextureThumbHover"]
            = &tgui::SliderRenderer::setTextureThumbHover;
        bindSliderRenderer["getTextureThumbHover"]
            = &tgui::SliderRenderer::getTextureThumbHover;
        bindSliderRenderer["setThumbWithinTrack"]
            = &tgui::SliderRenderer::setThumbWithinTrack;
        bindSliderRenderer["getThumbWithinTrack"]
            = &tgui::SliderRenderer::getThumbWithinTrack;
    }
};