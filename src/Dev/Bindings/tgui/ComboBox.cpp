#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ComboBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassComboBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ComboBox> bindComboBox
            = tguiNamespace.new_usertype<tgui::ComboBox>("ComboBox",
                sol::call_constructor,
                sol::constructors<tgui::ComboBox(), tgui::ComboBox(const char*),
                    tgui::ComboBox(const char*, bool),
                    tgui::ComboBox(const tgui::ComboBox&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindComboBox["operator="] = sol::overload(
            static_cast<tgui::ComboBox& (tgui::ComboBox::*)(const tgui::ComboBox&)>(
                &tgui::ComboBox::operator=),
            [](tgui::ComboBox* self, tgui::ComboBox other) {
                self->operator=(std::move(other));
            });
        bindComboBox["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ComboBoxRenderer* (tgui::ComboBox::*)()>(
                                &tgui::ComboBox::getSharedRenderer),
                static_cast<const tgui::ComboBoxRenderer* (tgui::ComboBox::*)() const>(
                    &tgui::ComboBox::getSharedRenderer));
        bindComboBox["getRenderer"]
            = sol::overload(static_cast<tgui::ComboBoxRenderer* (tgui::ComboBox::*)()>(
                                &tgui::ComboBox::getRenderer),
                static_cast<const tgui::ComboBoxRenderer* (tgui::ComboBox::*)() const>(
                    &tgui::ComboBox::getRenderer));
        bindComboBox["setSize"]
            = sol::overload(static_cast<void (tgui::ComboBox::*)(const tgui::Layout2d&)>(
                                &tgui::ComboBox::setSize),
                static_cast<void (tgui::ComboBox::*)(const tgui::Layout2d&)>(
                    &tgui::ComboBox::setSize),
                static_cast<void (tgui::ComboBox::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ComboBox::setSize));
        bindComboBox["setEnabled"] = &tgui::ComboBox::setEnabled;
        bindComboBox["setItemsToDisplay"] = &tgui::ComboBox::setItemsToDisplay;
        bindComboBox["getItemsToDisplay"] = &tgui::ComboBox::getItemsToDisplay;
        bindComboBox["addItem"] = sol::overload(
            [](tgui::ComboBox* self, const tgui::String& itemName) -> std::size_t {
                return self->addItem(itemName);
            },
            [](tgui::ComboBox* self, const tgui::String& itemName, const tgui::String& id)
                -> std::size_t { return self->addItem(itemName, id); });
        bindComboBox["setSelectedItem"] = &tgui::ComboBox::setSelectedItem;
        bindComboBox["setSelectedItemById"] = &tgui::ComboBox::setSelectedItemById;
        bindComboBox["setSelectedItemByIndex"] = &tgui::ComboBox::setSelectedItemByIndex;
        bindComboBox["deselectItem"] = &tgui::ComboBox::deselectItem;
        bindComboBox["removeItem"] = &tgui::ComboBox::removeItem;
        bindComboBox["removeItemById"] = &tgui::ComboBox::removeItemById;
        bindComboBox["removeItemByIndex"] = &tgui::ComboBox::removeItemByIndex;
        bindComboBox["removeAllItems"] = &tgui::ComboBox::removeAllItems;
        bindComboBox["getItemById"] = &tgui::ComboBox::getItemById;
        bindComboBox["getSelectedItem"] = &tgui::ComboBox::getSelectedItem;
        bindComboBox["getSelectedItemId"] = &tgui::ComboBox::getSelectedItemId;
        bindComboBox["getSelectedItemIndex"] = &tgui::ComboBox::getSelectedItemIndex;
        bindComboBox["changeItem"] = &tgui::ComboBox::changeItem;
        bindComboBox["changeItemById"] = &tgui::ComboBox::changeItemById;
        bindComboBox["changeItemByIndex"] = &tgui::ComboBox::changeItemByIndex;
        bindComboBox["getItemCount"] = &tgui::ComboBox::getItemCount;
        bindComboBox["getItems"] = &tgui::ComboBox::getItems;
        bindComboBox["getItemIds"] = &tgui::ComboBox::getItemIds;
        bindComboBox["setMaximumItems"] = sol::overload(
            [](tgui::ComboBox* self) -> void { return self->setMaximumItems(); },
            [](tgui::ComboBox* self, std::size_t maximumItems) -> void {
                return self->setMaximumItems(maximumItems);
            });
        bindComboBox["getMaximumItems"] = &tgui::ComboBox::getMaximumItems;
        bindComboBox["setTextSize"] = &tgui::ComboBox::setTextSize;
        bindComboBox["getTextSize"] = &tgui::ComboBox::getTextSize;
        bindComboBox["setDefaultText"] = &tgui::ComboBox::setDefaultText;
        bindComboBox["getDefaultText"] = &tgui::ComboBox::getDefaultText;
        bindComboBox["setExpandDirection"] = &tgui::ComboBox::setExpandDirection;
        bindComboBox["getExpandDirection"] = &tgui::ComboBox::getExpandDirection;
        bindComboBox["contains"] = &tgui::ComboBox::contains;
        bindComboBox["containsId"] = &tgui::ComboBox::containsId;
        bindComboBox["setChangeItemOnScroll"] = &tgui::ComboBox::setChangeItemOnScroll;
        bindComboBox["getChangeItemOnScroll"] = &tgui::ComboBox::getChangeItemOnScroll;
        bindComboBox["setParent"] = &tgui::ComboBox::setParent;
        bindComboBox["isMouseOnWidget"] = &tgui::ComboBox::isMouseOnWidget;
        bindComboBox["leftMousePressed"] = &tgui::ComboBox::leftMousePressed;
        bindComboBox["mouseWheelScrolled"] = &tgui::ComboBox::mouseWheelScrolled;
        bindComboBox["draw"] =

            [](tgui::ComboBox* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindComboBox["create"] = &tgui::ComboBox::create;
        bindComboBox["copy"] = &tgui::ComboBox::copy;
        bindComboBox["onItemSelect"] = &tgui::ComboBox::onItemSelect;
    }
};