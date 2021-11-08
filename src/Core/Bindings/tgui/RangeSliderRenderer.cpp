#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/RangeSliderRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRangeSliderRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RangeSliderRenderer> bindRangeSliderRenderer
            = tguiNamespace.new_usertype<tgui::RangeSliderRenderer>("RangeSliderRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::SliderRenderer, tgui::WidgetRenderer>());
        bindRangeSliderRenderer["setSelectedTrackColor"]
            = &tgui::RangeSliderRenderer::setSelectedTrackColor;
        bindRangeSliderRenderer["getSelectedTrackColor"]
            = &tgui::RangeSliderRenderer::getSelectedTrackColor;
        bindRangeSliderRenderer["setSelectedTrackColorHover"]
            = &tgui::RangeSliderRenderer::setSelectedTrackColorHover;
        bindRangeSliderRenderer["getSelectedTrackColorHover"]
            = &tgui::RangeSliderRenderer::getSelectedTrackColorHover;
        bindRangeSliderRenderer["setTextureSelectedTrack"]
            = &tgui::RangeSliderRenderer::setTextureSelectedTrack;
        bindRangeSliderRenderer["getTextureSelectedTrack"]
            = &tgui::RangeSliderRenderer::getTextureSelectedTrack;
        bindRangeSliderRenderer["setTextureSelectedTrackHover"]
            = &tgui::RangeSliderRenderer::setTextureSelectedTrackHover;
        bindRangeSliderRenderer["getTextureSelectedTrackHover"]
            = &tgui::RangeSliderRenderer::getTextureSelectedTrackHover;
    }
};