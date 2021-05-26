#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ListBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassListBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListBox> bindListBox
            = tguiNamespace.new_usertype<tgui::ListBox>("ListBox", sol::call_constructor,
                sol::constructors<tgui::ListBox(), tgui::ListBox(const char*),
                    tgui::ListBox(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindListBox["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ListBoxRenderer* (tgui::ListBox::*)()>(
                                &tgui::ListBox::getSharedRenderer),
                static_cast<const tgui::ListBoxRenderer* (tgui::ListBox::*)() const>(
                    &tgui::ListBox::getSharedRenderer));
        bindListBox["getRenderer"]
            = sol::overload(static_cast<tgui::ListBoxRenderer* (tgui::ListBox::*)()>(
                                &tgui::ListBox::getRenderer),
                static_cast<const tgui::ListBoxRenderer* (tgui::ListBox::*)() const>(
                    &tgui::ListBox::getRenderer));
        bindListBox["setPosition"]
            = sol::overload(static_cast<void (tgui::ListBox::*)(const tgui::Layout2d&)>(
                                &tgui::ListBox::setPosition),
                static_cast<void (tgui::ListBox::*)(const tgui::Layout2d&)>(
                    &tgui::ListBox::setPosition),
                static_cast<void (tgui::ListBox::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ListBox::setPosition));
        bindListBox["setSize"]
            = sol::overload(static_cast<void (tgui::ListBox::*)(const tgui::Layout2d&)>(
                                &tgui::ListBox::setSize),
                static_cast<void (tgui::ListBox::*)(const tgui::Layout2d&)>(
                    &tgui::ListBox::setSize),
                static_cast<void (tgui::ListBox::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ListBox::setSize));
        bindListBox["addItem"] = sol::overload(
            [](tgui::ListBox* self, const tgui::String& itemName) -> std::size_t {
                return self->addItem(itemName);
            },
            [](tgui::ListBox* self, const tgui::String& itemName, const tgui::String& id)
                -> std::size_t { return self->addItem(itemName, id); });
        bindListBox["setSelectedItem"] = &tgui::ListBox::setSelectedItem;
        bindListBox["setSelectedItemById"] = &tgui::ListBox::setSelectedItemById;
        bindListBox["setSelectedItemByIndex"] = &tgui::ListBox::setSelectedItemByIndex;
        bindListBox["deselectItem"] = &tgui::ListBox::deselectItem;
        bindListBox["removeItem"] = &tgui::ListBox::removeItem;
        bindListBox["removeItemById"] = &tgui::ListBox::removeItemById;
        bindListBox["removeItemByIndex"] = &tgui::ListBox::removeItemByIndex;
        bindListBox["removeAllItems"] = &tgui::ListBox::removeAllItems;
        bindListBox["getItemById"] = &tgui::ListBox::getItemById;
        bindListBox["getItemByIndex"] = &tgui::ListBox::getItemByIndex;
        bindListBox["getIndexById"] = &tgui::ListBox::getIndexById;
        bindListBox["getIdByIndex"] = &tgui::ListBox::getIdByIndex;
        bindListBox["getSelectedItem"] = &tgui::ListBox::getSelectedItem;
        bindListBox["getSelectedItemId"] = &tgui::ListBox::getSelectedItemId;
        bindListBox["getSelectedItemIndex"] = &tgui::ListBox::getSelectedItemIndex;
        bindListBox["changeItem"] = &tgui::ListBox::changeItem;
        bindListBox["changeItemById"] = &tgui::ListBox::changeItemById;
        bindListBox["changeItemByIndex"] = &tgui::ListBox::changeItemByIndex;
        bindListBox["getItemCount"] = &tgui::ListBox::getItemCount;
        bindListBox["getItems"] = &tgui::ListBox::getItems;
        bindListBox["getItemIds"] = &tgui::ListBox::getItemIds;
        bindListBox["setItemData"] = &tgui::ListBox::setItemData;
        bindListBox["setItemHeight"] = &tgui::ListBox::setItemHeight;
        bindListBox["getItemHeight"] = &tgui::ListBox::getItemHeight;
        bindListBox["setTextSize"] = &tgui::ListBox::setTextSize;
        bindListBox["setMaximumItems"] = sol::overload(
            [](tgui::ListBox* self) -> void { return self->setMaximumItems(); },
            [](tgui::ListBox* self, std::size_t maximumItems) -> void {
                return self->setMaximumItems(maximumItems);
            });
        bindListBox["getMaximumItems"] = &tgui::ListBox::getMaximumItems;
        bindListBox["setAutoScroll"] = &tgui::ListBox::setAutoScroll;
        bindListBox["getAutoScroll"] = &tgui::ListBox::getAutoScroll;
        bindListBox["contains"] = &tgui::ListBox::contains;
        bindListBox["containsId"] = &tgui::ListBox::containsId;
        bindListBox["setScrollbarValue"] = &tgui::ListBox::setScrollbarValue;
        bindListBox["getScrollbarValue"] = &tgui::ListBox::getScrollbarValue;
        bindListBox["isMouseOnWidget"] = &tgui::ListBox::isMouseOnWidget;
        bindListBox["leftMousePressed"] = &tgui::ListBox::leftMousePressed;
        bindListBox["leftMouseReleased"] = &tgui::ListBox::leftMouseReleased;
        bindListBox["mouseMoved"] = &tgui::ListBox::mouseMoved;
        bindListBox["mouseWheelScrolled"] = &tgui::ListBox::mouseWheelScrolled;
        bindListBox["mouseNoLongerOnWidget"] = &tgui::ListBox::mouseNoLongerOnWidget;
        bindListBox["leftMouseButtonNoLongerDown"]
            = &tgui::ListBox::leftMouseButtonNoLongerDown;
        bindListBox["keyPressed"] = &tgui::ListBox::keyPressed;
        bindListBox["draw"] =

            [](tgui::ListBox* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindListBox["create"] = &tgui::ListBox::create;
        bindListBox["copy"] = &tgui::ListBox::copy;
        bindListBox["onItemSelect"] = &tgui::ListBox::onItemSelect;
        bindListBox["onMousePress"] = &tgui::ListBox::onMousePress;
        bindListBox["onMouseRelease"] = &tgui::ListBox::onMouseRelease;
        bindListBox["onDoubleClick"] = &tgui::ListBox::onDoubleClick;
    }
};