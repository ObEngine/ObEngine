#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ListView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassListView(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListView> bindListView
            = tguiNamespace.new_usertype<tgui::ListView>("ListView",
                sol::call_constructor,
                sol::constructors<tgui::ListView(), tgui::ListView(const char*),
                    tgui::ListView(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindListView["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ListViewRenderer* (tgui::ListView::*)()>(
                                &tgui::ListView::getSharedRenderer),
                static_cast<const tgui::ListViewRenderer* (tgui::ListView::*)() const>(
                    &tgui::ListView::getSharedRenderer));
        bindListView["getRenderer"]
            = sol::overload(static_cast<tgui::ListViewRenderer* (tgui::ListView::*)()>(
                                &tgui::ListView::getRenderer),
                static_cast<const tgui::ListViewRenderer* (tgui::ListView::*)() const>(
                    &tgui::ListView::getRenderer));
        bindListView["setSize"]
            = sol::overload(static_cast<void (tgui::ListView::*)(const tgui::Layout2d&)>(
                                &tgui::ListView::setSize),
                static_cast<void (tgui::ListView::*)(const tgui::Layout2d&)>(
                    &tgui::ListView::setSize),
                static_cast<void (tgui::ListView::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ListView::setSize));
        bindListView["addColumn"] = sol::overload(
            [](tgui::ListView* self, const tgui::String& text) -> std::size_t {
                return self->addColumn(text);
            },
            [](tgui::ListView* self, const tgui::String& text,
                float width) -> std::size_t { return self->addColumn(text, width); },
            [](tgui::ListView* self, const tgui::String& text, float width,
                tgui::ListView::ColumnAlignment alignment) -> std::size_t {
                return self->addColumn(text, width, alignment);
            });
        bindListView["setColumnText"] = &tgui::ListView::setColumnText;
        bindListView["getColumnText"] = &tgui::ListView::getColumnText;
        bindListView["setColumnWidth"] = &tgui::ListView::setColumnWidth;
        bindListView["getColumnWidth"] = &tgui::ListView::getColumnWidth;
        bindListView["setColumnAlignment"] = &tgui::ListView::setColumnAlignment;
        bindListView["getColumnAlignment"] = &tgui::ListView::getColumnAlignment;
        bindListView["removeAllColumns"] = &tgui::ListView::removeAllColumns;
        bindListView["getColumnCount"] = &tgui::ListView::getColumnCount;
        bindListView["setHeaderHeight"] = &tgui::ListView::setHeaderHeight;
        bindListView["getHeaderHeight"] = &tgui::ListView::getHeaderHeight;
        bindListView["getCurrentHeaderHeight"] = &tgui::ListView::getCurrentHeaderHeight;
        bindListView["setHeaderVisible"] = &tgui::ListView::setHeaderVisible;
        bindListView["getHeaderVisible"] = &tgui::ListView::getHeaderVisible;
        bindListView["addItem"] = sol::overload(
            static_cast<std::size_t (tgui::ListView::*)(const tgui::String&)>(
                &tgui::ListView::addItem),
            static_cast<std::size_t (tgui::ListView::*)(
                const std::vector<tgui::String>&)>(&tgui::ListView::addItem));
        bindListView["addMultipleItems"] = &tgui::ListView::addMultipleItems;
        bindListView["insertItem"] = sol::overload(
            static_cast<void (tgui::ListView::*)(std::size_t, const tgui::String&)>(
                &tgui::ListView::insertItem),
            static_cast<void (tgui::ListView::*)(std::size_t,
                const std::vector<tgui::String>&)>(&tgui::ListView::insertItem));
        bindListView["insertMultipleItems"] = &tgui::ListView::insertMultipleItems;
        bindListView["changeItem"] = &tgui::ListView::changeItem;
        bindListView["changeSubItem"] = &tgui::ListView::changeSubItem;
        bindListView["removeItem"] = &tgui::ListView::removeItem;
        bindListView["removeAllItems"] = &tgui::ListView::removeAllItems;
        bindListView["setSelectedItem"] = &tgui::ListView::setSelectedItem;
        bindListView["setSelectedItems"] = &tgui::ListView::setSelectedItems;
        bindListView["deselectItems"] = &tgui::ListView::deselectItems;
        bindListView["getSelectedItemIndex"] = &tgui::ListView::getSelectedItemIndex;
        bindListView["getSelectedItemIndices"] = &tgui::ListView::getSelectedItemIndices;
        bindListView["setMultiSelect"] = &tgui::ListView::setMultiSelect;
        bindListView["getMultiSelect"] = &tgui::ListView::getMultiSelect;
        bindListView["setItemData"] = &tgui::ListView::setItemData;
        bindListView["setItemIcon"] = &tgui::ListView::setItemIcon;
        bindListView["getItemIcon"] = &tgui::ListView::getItemIcon;
        bindListView["getItemCount"] = &tgui::ListView::getItemCount;
        bindListView["getItem"] = &tgui::ListView::getItem;
        bindListView["getItemRow"] = &tgui::ListView::getItemRow;
        bindListView["getItemCell"] = &tgui::ListView::getItemCell;
        bindListView["getItems"] = &tgui::ListView::getItems;
        bindListView["getItemRows"] = &tgui::ListView::getItemRows;
        bindListView["sort"] = &tgui::ListView::sort;
        bindListView["setItemHeight"] = &tgui::ListView::setItemHeight;
        bindListView["getItemHeight"] = &tgui::ListView::getItemHeight;
        bindListView["setTextSize"] = &tgui::ListView::setTextSize;
        bindListView["setHeaderTextSize"] = &tgui::ListView::setHeaderTextSize;
        bindListView["getHeaderTextSize"] = &tgui::ListView::getHeaderTextSize;
        bindListView["setSeparatorWidth"] = &tgui::ListView::setSeparatorWidth;
        bindListView["getSeparatorWidth"] = &tgui::ListView::getSeparatorWidth;
        bindListView["setHeaderSeparatorHeight"]
            = &tgui::ListView::setHeaderSeparatorHeight;
        bindListView["getHeaderSeparatorHeight"]
            = &tgui::ListView::getHeaderSeparatorHeight;
        bindListView["setGridLinesWidth"] = &tgui::ListView::setGridLinesWidth;
        bindListView["getGridLinesWidth"] = &tgui::ListView::getGridLinesWidth;
        bindListView["setAutoScroll"] = &tgui::ListView::setAutoScroll;
        bindListView["getAutoScroll"] = &tgui::ListView::getAutoScroll;
        bindListView["setShowVerticalGridLines"]
            = &tgui::ListView::setShowVerticalGridLines;
        bindListView["getShowVerticalGridLines"]
            = &tgui::ListView::getShowVerticalGridLines;
        bindListView["setShowHorizontalGridLines"]
            = &tgui::ListView::setShowHorizontalGridLines;
        bindListView["getShowHorizontalGridLines"]
            = &tgui::ListView::getShowHorizontalGridLines;
        bindListView["setExpandLastColumn"] = &tgui::ListView::setExpandLastColumn;
        bindListView["getExpandLastColumn"] = &tgui::ListView::getExpandLastColumn;
        bindListView["setVerticalScrollbarPolicy"]
            = &tgui::ListView::setVerticalScrollbarPolicy;
        bindListView["getVerticalScrollbarPolicy"]
            = &tgui::ListView::getVerticalScrollbarPolicy;
        bindListView["setHorizontalScrollbarPolicy"]
            = &tgui::ListView::setHorizontalScrollbarPolicy;
        bindListView["getHorizontalScrollbarPolicy"]
            = &tgui::ListView::getHorizontalScrollbarPolicy;
        bindListView["setVerticalScrollbarValue"]
            = &tgui::ListView::setVerticalScrollbarValue;
        bindListView["getVerticalScrollbarValue"]
            = &tgui::ListView::getVerticalScrollbarValue;
        bindListView["setHorizontalScrollbarValue"]
            = &tgui::ListView::setHorizontalScrollbarValue;
        bindListView["getHorizontalScrollbarValue"]
            = &tgui::ListView::getHorizontalScrollbarValue;
        bindListView["setFixedIconSize"] = &tgui::ListView::setFixedIconSize;
        bindListView["getFixedIconSize"] = &tgui::ListView::getFixedIconSize;
        bindListView["isMouseOnWidget"] = &tgui::ListView::isMouseOnWidget;
        bindListView["leftMousePressed"] = &tgui::ListView::leftMousePressed;
        bindListView["leftMouseReleased"] = &tgui::ListView::leftMouseReleased;
        bindListView["rightMousePressed"] = &tgui::ListView::rightMousePressed;
        bindListView["mouseMoved"] = &tgui::ListView::mouseMoved;
        bindListView["mouseWheelScrolled"] = &tgui::ListView::mouseWheelScrolled;
        bindListView["mouseNoLongerOnWidget"] = &tgui::ListView::mouseNoLongerOnWidget;
        bindListView["leftMouseButtonNoLongerDown"]
            = &tgui::ListView::leftMouseButtonNoLongerDown;
        bindListView["keyPressed"] = &tgui::ListView::keyPressed;
        bindListView["draw"] =

            [](tgui::ListView* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindListView["create"] = &tgui::ListView::create;
        bindListView["copy"] = &tgui::ListView::copy;
        bindListView["onItemSelect"] = &tgui::ListView::onItemSelect;
        bindListView["onDoubleClick"] = &tgui::ListView::onDoubleClick;
        bindListView["onRightClick"] = &tgui::ListView::onRightClick;
        bindListView["onHeaderClick"] = &tgui::ListView::onHeaderClick;
    }
};