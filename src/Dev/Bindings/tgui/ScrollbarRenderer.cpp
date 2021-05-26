#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/ScrollbarRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassScrollbarRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollbarRenderer> bindScrollbarRenderer
            = tguiNamespace.new_usertype<tgui::ScrollbarRenderer>("ScrollbarRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindScrollbarRenderer["setTrackColor"] = &tgui::ScrollbarRenderer::setTrackColor;
        bindScrollbarRenderer["getTrackColor"] = &tgui::ScrollbarRenderer::getTrackColor;
        bindScrollbarRenderer["setTrackColorHover"]
            = &tgui::ScrollbarRenderer::setTrackColorHover;
        bindScrollbarRenderer["getTrackColorHover"]
            = &tgui::ScrollbarRenderer::getTrackColorHover;
        bindScrollbarRenderer["setThumbColor"] = &tgui::ScrollbarRenderer::setThumbColor;
        bindScrollbarRenderer["getThumbColor"] = &tgui::ScrollbarRenderer::getThumbColor;
        bindScrollbarRenderer["setThumbColorHover"]
            = &tgui::ScrollbarRenderer::setThumbColorHover;
        bindScrollbarRenderer["getThumbColorHover"]
            = &tgui::ScrollbarRenderer::getThumbColorHover;
        bindScrollbarRenderer["setArrowBackgroundColor"]
            = &tgui::ScrollbarRenderer::setArrowBackgroundColor;
        bindScrollbarRenderer["getArrowBackgroundColor"]
            = &tgui::ScrollbarRenderer::getArrowBackgroundColor;
        bindScrollbarRenderer["setArrowBackgroundColorHover"]
            = &tgui::ScrollbarRenderer::setArrowBackgroundColorHover;
        bindScrollbarRenderer["getArrowBackgroundColorHover"]
            = &tgui::ScrollbarRenderer::getArrowBackgroundColorHover;
        bindScrollbarRenderer["setArrowColor"] = &tgui::ScrollbarRenderer::setArrowColor;
        bindScrollbarRenderer["getArrowColor"] = &tgui::ScrollbarRenderer::getArrowColor;
        bindScrollbarRenderer["setArrowColorHover"]
            = &tgui::ScrollbarRenderer::setArrowColorHover;
        bindScrollbarRenderer["getArrowColorHover"]
            = &tgui::ScrollbarRenderer::getArrowColorHover;
        bindScrollbarRenderer["setTextureTrack"]
            = &tgui::ScrollbarRenderer::setTextureTrack;
        bindScrollbarRenderer["getTextureTrack"]
            = &tgui::ScrollbarRenderer::getTextureTrack;
        bindScrollbarRenderer["setTextureTrackHover"]
            = &tgui::ScrollbarRenderer::setTextureTrackHover;
        bindScrollbarRenderer["getTextureTrackHover"]
            = &tgui::ScrollbarRenderer::getTextureTrackHover;
        bindScrollbarRenderer["setTextureThumb"]
            = &tgui::ScrollbarRenderer::setTextureThumb;
        bindScrollbarRenderer["getTextureThumb"]
            = &tgui::ScrollbarRenderer::getTextureThumb;
        bindScrollbarRenderer["setTextureThumbHover"]
            = &tgui::ScrollbarRenderer::setTextureThumbHover;
        bindScrollbarRenderer["getTextureThumbHover"]
            = &tgui::ScrollbarRenderer::getTextureThumbHover;
        bindScrollbarRenderer["setTextureArrowUp"]
            = &tgui::ScrollbarRenderer::setTextureArrowUp;
        bindScrollbarRenderer["getTextureArrowUp"]
            = &tgui::ScrollbarRenderer::getTextureArrowUp;
        bindScrollbarRenderer["setTextureArrowUpHover"]
            = &tgui::ScrollbarRenderer::setTextureArrowUpHover;
        bindScrollbarRenderer["getTextureArrowUpHover"]
            = &tgui::ScrollbarRenderer::getTextureArrowUpHover;
        bindScrollbarRenderer["setTextureArrowDown"]
            = &tgui::ScrollbarRenderer::setTextureArrowDown;
        bindScrollbarRenderer["getTextureArrowDown"]
            = &tgui::ScrollbarRenderer::getTextureArrowDown;
        bindScrollbarRenderer["setTextureArrowDownHover"]
            = &tgui::ScrollbarRenderer::setTextureArrowDownHover;
        bindScrollbarRenderer["getTextureArrowDownHover"]
            = &tgui::ScrollbarRenderer::getTextureArrowDownHover;
    }
};