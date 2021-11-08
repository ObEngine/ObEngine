#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/GuiBase.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassGuiBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::GuiBase> bindGuiBase
            = tguiNamespace.new_usertype<tgui::GuiBase>("GuiBase");
        bindGuiBase["operator="] = &tgui::GuiBase::operator=;
        bindGuiBase["setAbsoluteViewport"] = &tgui::GuiBase::setAbsoluteViewport;
        bindGuiBase["setRelativeViewport"] = &tgui::GuiBase::setRelativeViewport;
        bindGuiBase["getViewport"] = &tgui::GuiBase::getViewport;
        bindGuiBase["setAbsoluteView"] = &tgui::GuiBase::setAbsoluteView;
        bindGuiBase["setRelativeView"] = &tgui::GuiBase::setRelativeView;
        bindGuiBase["getView"] = &tgui::GuiBase::getView;
        bindGuiBase["handleEvent"] = &tgui::GuiBase::handleEvent;
        bindGuiBase["setTabKeyUsageEnabled"] = &tgui::GuiBase::setTabKeyUsageEnabled;
        bindGuiBase["isTabKeyUsageEnabled"] = &tgui::GuiBase::isTabKeyUsageEnabled;
        bindGuiBase["draw"] = &tgui::GuiBase::draw;
        bindGuiBase["getContainer"] = &tgui::GuiBase::getContainer;
        bindGuiBase["setFont"] = &tgui::GuiBase::setFont;
        bindGuiBase["getFont"] = &tgui::GuiBase::getFont;
        bindGuiBase["getWidgets"] = &tgui::GuiBase::getWidgets;
        bindGuiBase["add"] = sol::overload(
            [](tgui::GuiBase* self, const tgui::Widget::Ptr& widgetPtr) -> void {
                return self->add(widgetPtr);
            },
            [](tgui::GuiBase* self, const tgui::Widget::Ptr& widgetPtr,
                const tgui::String& widgetName) -> void {
                return self->add(widgetPtr, widgetName);
            });
        bindGuiBase["get"]
            = static_cast<tgui::Widget::Ptr (tgui::GuiBase::*)(const tgui::String&) const>(
                &tgui::GuiBase::get);
        bindGuiBase["remove"] = &tgui::GuiBase::remove;
        bindGuiBase["removeAllWidgets"] = &tgui::GuiBase::removeAllWidgets;
        bindGuiBase["getFocusedChild"] = &tgui::GuiBase::getFocusedChild;
        bindGuiBase["getFocusedLeaf"] = &tgui::GuiBase::getFocusedLeaf;
        bindGuiBase["getWidgetAtPosition"] = &tgui::GuiBase::getWidgetAtPosition;
        bindGuiBase["getWidgetBelowMouseCursor"] = &tgui::GuiBase::getWidgetBelowMouseCursor;
        bindGuiBase["focusNextWidget"]
            = sol::overload([](tgui::GuiBase* self) -> bool { return self->focusNextWidget(); },
                [](tgui::GuiBase* self, bool recursive) -> bool {
                    return self->focusNextWidget(recursive);
                });
        bindGuiBase["focusPreviousWidget"]
            = sol::overload([](tgui::GuiBase* self) -> bool { return self->focusPreviousWidget(); },
                [](tgui::GuiBase* self, bool recursive) -> bool {
                    return self->focusPreviousWidget(recursive);
                });
        bindGuiBase["unfocusAllWidgets"] = &tgui::GuiBase::unfocusAllWidgets;
        bindGuiBase["moveWidgetToFront"] = &tgui::GuiBase::moveWidgetToFront;
        bindGuiBase["moveWidgetToBack"] = &tgui::GuiBase::moveWidgetToBack;
        bindGuiBase["moveWidgetForward"] = &tgui::GuiBase::moveWidgetForward;
        bindGuiBase["moveWidgetBackward"] = &tgui::GuiBase::moveWidgetBackward;
        bindGuiBase["setOpacity"] = &tgui::GuiBase::setOpacity;
        bindGuiBase["getOpacity"] = &tgui::GuiBase::getOpacity;
        bindGuiBase["setTextSize"] = &tgui::GuiBase::setTextSize;
        bindGuiBase["getTextSize"] = &tgui::GuiBase::getTextSize;
        bindGuiBase["loadWidgetsFromFile"] = sol::overload(
            [](tgui::GuiBase* self, const tgui::String& filename) -> void {
                return self->loadWidgetsFromFile(filename);
            },
            [](tgui::GuiBase* self, const tgui::String& filename, bool replaceExisting) -> void {
                return self->loadWidgetsFromFile(filename, replaceExisting);
            });
        bindGuiBase["saveWidgetsToFile"] = &tgui::GuiBase::saveWidgetsToFile;
        bindGuiBase["loadWidgetsFromStream"] = sol::overload(
            [](tgui::GuiBase* self, std::stringstream& stream) -> void {
                return self->loadWidgetsFromStream(stream);
            },
            [](tgui::GuiBase* self, std::stringstream& stream, bool replaceExisting) -> void {
                return self->loadWidgetsFromStream(stream, replaceExisting);
            },
            [](tgui::GuiBase* self, std::stringstream&& stream) -> void {
                return self->loadWidgetsFromStream(stream);
            },
            [](tgui::GuiBase* self, std::stringstream&& stream, bool replaceExisting) -> void {
                return self->loadWidgetsFromStream(stream, replaceExisting);
            });
        bindGuiBase["saveWidgetsToStream"] = &tgui::GuiBase::saveWidgetsToStream;
        bindGuiBase["setOverrideMouseCursor"] = &tgui::GuiBase::setOverrideMouseCursor;
        bindGuiBase["restoreOverrideMouseCursor"] = &tgui::GuiBase::restoreOverrideMouseCursor;
        bindGuiBase["requestMouseCursor"] = &tgui::GuiBase::requestMouseCursor;
        bindGuiBase["setDrawingUpdatesTime"] = &tgui::GuiBase::setDrawingUpdatesTime;
        bindGuiBase["updateTime"]
            = sol::overload(static_cast<bool (tgui::GuiBase::*)()>(&tgui::GuiBase::updateTime),
                static_cast<bool (tgui::GuiBase::*)(tgui::Duration)>(&tgui::GuiBase::updateTime));
        bindGuiBase["mapPixelToView"] = &tgui::GuiBase::mapPixelToView;
        bindGuiBase["mainLoop"] = &tgui::GuiBase::mainLoop;
        bindGuiBase["onViewChange"] = &tgui::GuiBase::onViewChange;
    }
};