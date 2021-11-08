#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/TreeView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTreeView(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TreeView> bindTreeView
            = tguiNamespace.new_usertype<tgui::TreeView>("TreeView", sol::call_constructor,
                sol::constructors<tgui::TreeView(), tgui::TreeView(const char*),
                    tgui::TreeView(const char*, bool), tgui::TreeView(const tgui::TreeView&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindTreeView["operator="]
            = sol::overload(static_cast<tgui::TreeView& (tgui::TreeView::*)(const tgui::TreeView&)>(
                                &tgui::TreeView::operator=),
                static_cast<tgui::TreeView& (tgui::TreeView::*)(tgui::TreeView &&)>(
                    &tgui::TreeView::operator=));
        bindTreeView["getSharedRenderer"]
            = sol::overload(static_cast<tgui::TreeViewRenderer* (tgui::TreeView::*)()>(
                                &tgui::TreeView::getSharedRenderer),
                static_cast<const tgui::TreeViewRenderer* (tgui::TreeView::*)() const>(
                    &tgui::TreeView::getSharedRenderer));
        bindTreeView["getRenderer"]
            = sol::overload(static_cast<tgui::TreeViewRenderer* (tgui::TreeView::*)()>(
                                &tgui::TreeView::getRenderer),
                static_cast<const tgui::TreeViewRenderer* (tgui::TreeView::*)() const>(
                    &tgui::TreeView::getRenderer));
        bindTreeView["setSize"] = sol::overload(
            static_cast<void (tgui::TreeView::*)(const tgui::Layout2d&)>(&tgui::TreeView::setSize),
            static_cast<void (tgui::TreeView::*)(const tgui::Layout2d&)>(&tgui::TreeView::setSize),
            static_cast<void (tgui::TreeView::*)(tgui::Layout, tgui::Layout)>(
                &tgui::TreeView::setSize));
        bindTreeView["addItem"] = sol::overload(
            [](tgui::TreeView* self, const std::vector<tgui::String>& hierarchy) -> bool {
                return self->addItem(hierarchy);
            },
            [](tgui::TreeView* self, const std::vector<tgui::String>& hierarchy,
                bool createParents) -> bool { return self->addItem(hierarchy, createParents); });
        bindTreeView["expand"] = &tgui::TreeView::expand;
        bindTreeView["expandAll"] = &tgui::TreeView::expandAll;
        bindTreeView["collapse"] = &tgui::TreeView::collapse;
        bindTreeView["collapseAll"] = &tgui::TreeView::collapseAll;
        bindTreeView["selectItem"] = &tgui::TreeView::selectItem;
        bindTreeView["deselectItem"] = &tgui::TreeView::deselectItem;
        bindTreeView["removeItem"] = sol::overload(
            [](tgui::TreeView* self, const std::vector<tgui::String>& hierarchy) -> bool {
                return self->removeItem(hierarchy);
            },
            [](tgui::TreeView* self, const std::vector<tgui::String>& hierarchy,
                bool removeParentsWhenEmpty) -> bool {
                return self->removeItem(hierarchy, removeParentsWhenEmpty);
            });
        bindTreeView["removeAllItems"] = &tgui::TreeView::removeAllItems;
        bindTreeView["getSelectedItem"] = &tgui::TreeView::getSelectedItem;
        bindTreeView["getNodes"] = &tgui::TreeView::getNodes;
        bindTreeView["setItemHeight"] = &tgui::TreeView::setItemHeight;
        bindTreeView["getItemHeight"] = &tgui::TreeView::getItemHeight;
        bindTreeView["setTextSize"] = &tgui::TreeView::setTextSize;
        bindTreeView["setVerticalScrollbarValue"] = &tgui::TreeView::setVerticalScrollbarValue;
        bindTreeView["getVerticalScrollbarValue"] = &tgui::TreeView::getVerticalScrollbarValue;
        bindTreeView["setHorizontalScrollbarValue"] = &tgui::TreeView::setHorizontalScrollbarValue;
        bindTreeView["getHorizontalScrollbarValue"] = &tgui::TreeView::getHorizontalScrollbarValue;
        bindTreeView["isMouseOnWidget"] = &tgui::TreeView::isMouseOnWidget;
        bindTreeView["leftMousePressed"] = &tgui::TreeView::leftMousePressed;
        bindTreeView["leftMouseReleased"] = &tgui::TreeView::leftMouseReleased;
        bindTreeView["rightMousePressed"] = &tgui::TreeView::rightMousePressed;
        bindTreeView["mouseMoved"] = &tgui::TreeView::mouseMoved;
        bindTreeView["mouseWheelScrolled"] = &tgui::TreeView::mouseWheelScrolled;
        bindTreeView["mouseNoLongerOnWidget"] = &tgui::TreeView::mouseNoLongerOnWidget;
        bindTreeView["leftMouseButtonNoLongerDown"] = &tgui::TreeView::leftMouseButtonNoLongerDown;
        bindTreeView["markNodesDirty"] = &tgui::TreeView::markNodesDirty;
        bindTreeView["draw"] = &tgui::TreeView::draw;
        bindTreeView["create"] = &tgui::TreeView::create;
        bindTreeView["copy"] = &tgui::TreeView::copy;
        bindTreeView["onItemSelect"] = &tgui::TreeView::onItemSelect;
        bindTreeView["onDoubleClick"] = &tgui::TreeView::onDoubleClick;
        bindTreeView["onExpand"] = &tgui::TreeView::onExpand;
        bindTreeView["onCollapse"] = &tgui::TreeView::onCollapse;
        bindTreeView["onRightClick"] = &tgui::TreeView::onRightClick;
    }
};