#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/ScrollablePanelRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassScrollablePanelRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollablePanelRenderer> bindScrollablePanelRenderer
            = tguiNamespace.new_usertype<tgui::ScrollablePanelRenderer>(
                "ScrollablePanelRenderer", sol::call_constructor,
                sol::default_constructor, sol::base_classes,
                sol::bases<tgui::PanelRenderer, tgui::GroupRenderer,
                    tgui::WidgetRenderer>());
        bindScrollablePanelRenderer["setScrollbar"]
            = &tgui::ScrollablePanelRenderer::setScrollbar;
        bindScrollablePanelRenderer["getScrollbar"]
            = &tgui::ScrollablePanelRenderer::getScrollbar;
        bindScrollablePanelRenderer["setScrollbarWidth"]
            = &tgui::ScrollablePanelRenderer::setScrollbarWidth;
        bindScrollablePanelRenderer["getScrollbarWidth"]
            = &tgui::ScrollablePanelRenderer::getScrollbarWidth;
    }
};