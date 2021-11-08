#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/TreeViewRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTreeViewRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TreeViewRenderer> bindTreeViewRenderer
            = tguiNamespace.new_usertype<tgui::TreeViewRenderer>("TreeViewRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindTreeViewRenderer["setBorders"] = &tgui::TreeViewRenderer::setBorders;
        bindTreeViewRenderer["getBorders"] = &tgui::TreeViewRenderer::getBorders;
        bindTreeViewRenderer["setPadding"] = &tgui::TreeViewRenderer::setPadding;
        bindTreeViewRenderer["getPadding"] = &tgui::TreeViewRenderer::getPadding;
        bindTreeViewRenderer["setBackgroundColor"] = &tgui::TreeViewRenderer::setBackgroundColor;
        bindTreeViewRenderer["getBackgroundColor"] = &tgui::TreeViewRenderer::getBackgroundColor;
        bindTreeViewRenderer["setBorderColor"] = &tgui::TreeViewRenderer::setBorderColor;
        bindTreeViewRenderer["getBorderColor"] = &tgui::TreeViewRenderer::getBorderColor;
        bindTreeViewRenderer["setTextColor"] = &tgui::TreeViewRenderer::setTextColor;
        bindTreeViewRenderer["getTextColor"] = &tgui::TreeViewRenderer::getTextColor;
        bindTreeViewRenderer["setTextColorHover"] = &tgui::TreeViewRenderer::setTextColorHover;
        bindTreeViewRenderer["getTextColorHover"] = &tgui::TreeViewRenderer::getTextColorHover;
        bindTreeViewRenderer["setSelectedTextColor"]
            = &tgui::TreeViewRenderer::setSelectedTextColor;
        bindTreeViewRenderer["getSelectedTextColor"]
            = &tgui::TreeViewRenderer::getSelectedTextColor;
        bindTreeViewRenderer["setSelectedTextColorHover"]
            = &tgui::TreeViewRenderer::setSelectedTextColorHover;
        bindTreeViewRenderer["getSelectedTextColorHover"]
            = &tgui::TreeViewRenderer::getSelectedTextColorHover;
        bindTreeViewRenderer["setSelectedBackgroundColor"]
            = &tgui::TreeViewRenderer::setSelectedBackgroundColor;
        bindTreeViewRenderer["getSelectedBackgroundColor"]
            = &tgui::TreeViewRenderer::getSelectedBackgroundColor;
        bindTreeViewRenderer["setBackgroundColorHover"]
            = &tgui::TreeViewRenderer::setBackgroundColorHover;
        bindTreeViewRenderer["getBackgroundColorHover"]
            = &tgui::TreeViewRenderer::getBackgroundColorHover;
        bindTreeViewRenderer["setSelectedBackgroundColorHover"]
            = &tgui::TreeViewRenderer::setSelectedBackgroundColorHover;
        bindTreeViewRenderer["getSelectedBackgroundColorHover"]
            = &tgui::TreeViewRenderer::getSelectedBackgroundColorHover;
        bindTreeViewRenderer["setScrollbar"] = &tgui::TreeViewRenderer::setScrollbar;
        bindTreeViewRenderer["getScrollbar"] = &tgui::TreeViewRenderer::getScrollbar;
        bindTreeViewRenderer["setScrollbarWidth"] = &tgui::TreeViewRenderer::setScrollbarWidth;
        bindTreeViewRenderer["getScrollbarWidth"] = &tgui::TreeViewRenderer::getScrollbarWidth;
        bindTreeViewRenderer["setTextureBranchExpanded"]
            = &tgui::TreeViewRenderer::setTextureBranchExpanded;
        bindTreeViewRenderer["getTextureBranchExpanded"]
            = &tgui::TreeViewRenderer::getTextureBranchExpanded;
        bindTreeViewRenderer["setTextureBranchCollapsed"]
            = &tgui::TreeViewRenderer::setTextureBranchCollapsed;
        bindTreeViewRenderer["getTextureBranchCollapsed"]
            = &tgui::TreeViewRenderer::getTextureBranchCollapsed;
        bindTreeViewRenderer["setTextureLeaf"] = &tgui::TreeViewRenderer::setTextureLeaf;
        bindTreeViewRenderer["getTextureLeaf"] = &tgui::TreeViewRenderer::getTextureLeaf;
    }
};