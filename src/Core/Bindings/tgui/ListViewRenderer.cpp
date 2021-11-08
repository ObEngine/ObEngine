#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/ListViewRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassListViewRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListViewRenderer> bindListViewRenderer
            = tguiNamespace.new_usertype<tgui::ListViewRenderer>("ListViewRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindListViewRenderer["setBorders"] = &tgui::ListViewRenderer::setBorders;
        bindListViewRenderer["getBorders"] = &tgui::ListViewRenderer::getBorders;
        bindListViewRenderer["setPadding"] = &tgui::ListViewRenderer::setPadding;
        bindListViewRenderer["getPadding"] = &tgui::ListViewRenderer::getPadding;
        bindListViewRenderer["setBackgroundColor"] = &tgui::ListViewRenderer::setBackgroundColor;
        bindListViewRenderer["getBackgroundColor"] = &tgui::ListViewRenderer::getBackgroundColor;
        bindListViewRenderer["setBackgroundColorHover"]
            = &tgui::ListViewRenderer::setBackgroundColorHover;
        bindListViewRenderer["getBackgroundColorHover"]
            = &tgui::ListViewRenderer::getBackgroundColorHover;
        bindListViewRenderer["setSelectedBackgroundColor"]
            = &tgui::ListViewRenderer::setSelectedBackgroundColor;
        bindListViewRenderer["getSelectedBackgroundColor"]
            = &tgui::ListViewRenderer::getSelectedBackgroundColor;
        bindListViewRenderer["setSelectedBackgroundColorHover"]
            = &tgui::ListViewRenderer::setSelectedBackgroundColorHover;
        bindListViewRenderer["getSelectedBackgroundColorHover"]
            = &tgui::ListViewRenderer::getSelectedBackgroundColorHover;
        bindListViewRenderer["setTextColor"] = &tgui::ListViewRenderer::setTextColor;
        bindListViewRenderer["getTextColor"] = &tgui::ListViewRenderer::getTextColor;
        bindListViewRenderer["setTextColorHover"] = &tgui::ListViewRenderer::setTextColorHover;
        bindListViewRenderer["getTextColorHover"] = &tgui::ListViewRenderer::getTextColorHover;
        bindListViewRenderer["setSelectedTextColor"]
            = &tgui::ListViewRenderer::setSelectedTextColor;
        bindListViewRenderer["getSelectedTextColor"]
            = &tgui::ListViewRenderer::getSelectedTextColor;
        bindListViewRenderer["setSelectedTextColorHover"]
            = &tgui::ListViewRenderer::setSelectedTextColorHover;
        bindListViewRenderer["getSelectedTextColorHover"]
            = &tgui::ListViewRenderer::getSelectedTextColorHover;
        bindListViewRenderer["setHeaderBackgroundColor"]
            = &tgui::ListViewRenderer::setHeaderBackgroundColor;
        bindListViewRenderer["getHeaderBackgroundColor"]
            = &tgui::ListViewRenderer::getHeaderBackgroundColor;
        bindListViewRenderer["setHeaderTextColor"] = &tgui::ListViewRenderer::setHeaderTextColor;
        bindListViewRenderer["getHeaderTextColor"] = &tgui::ListViewRenderer::getHeaderTextColor;
        bindListViewRenderer["setBorderColor"] = &tgui::ListViewRenderer::setBorderColor;
        bindListViewRenderer["getBorderColor"] = &tgui::ListViewRenderer::getBorderColor;
        bindListViewRenderer["setSeparatorColor"] = &tgui::ListViewRenderer::setSeparatorColor;
        bindListViewRenderer["getSeparatorColor"] = &tgui::ListViewRenderer::getSeparatorColor;
        bindListViewRenderer["setGridLinesColor"] = &tgui::ListViewRenderer::setGridLinesColor;
        bindListViewRenderer["getGridLinesColor"] = &tgui::ListViewRenderer::getGridLinesColor;
        bindListViewRenderer["setScrollbar"] = &tgui::ListViewRenderer::setScrollbar;
        bindListViewRenderer["getScrollbar"] = &tgui::ListViewRenderer::getScrollbar;
        bindListViewRenderer["setScrollbarWidth"] = &tgui::ListViewRenderer::setScrollbarWidth;
        bindListViewRenderer["getScrollbarWidth"] = &tgui::ListViewRenderer::getScrollbarWidth;
    }
};