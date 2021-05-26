#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Container.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Container> bindContainer
            = tguiNamespace.new_usertype<tgui::Container>(
                "Container", sol::base_classes, sol::bases<tgui::Widget>());
        bindContainer["setSize"]
            = sol::overload(static_cast<void (tgui::Container::*)(const tgui::Layout2d&)>(
                                &tgui::Container::setSize),
                static_cast<void (tgui::Container::*)(const tgui::Layout2d&)>(
                    &tgui::Container::setSize),
                static_cast<void (tgui::Container::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::Container::setSize));
        bindContainer["getWidgets"] = &tgui::Container::getWidgets;
        bindContainer["add"] = sol::overload(
            [](tgui::Container* self, const tgui::Widget::Ptr& widgetPtr) -> void {
                return self->add(widgetPtr);
            },
            [](tgui::Container* self, const tgui::Widget::Ptr& widgetPtr,
                const tgui::String& widgetName) -> void {
                return self->add(widgetPtr, widgetName);
            });
        bindContainer["get"] = sol::overload(static_cast<tgui::Widget::Ptr (
                tgui::Container::*)(const tgui::String&) const>(&tgui::Container::get));
        bindContainer["remove"] = &tgui::Container::remove;
        bindContainer["removeAllWidgets"] = &tgui::Container::removeAllWidgets;
        bindContainer["getInnerSize"] = &tgui::Container::getInnerSize;
        bindContainer["getChildWidgetsOffset"] = &tgui::Container::getChildWidgetsOffset;
        bindContainer["setTextSize"] = &tgui::Container::setTextSize;
        bindContainer["loadWidgetsFromFile"] = sol::overload(
            [](tgui::Container* self, const tgui::String& filename) -> void {
                return self->loadWidgetsFromFile(filename);
            },
            [](tgui::Container* self, const tgui::String& filename, bool replaceExisting)
                -> void { return self->loadWidgetsFromFile(filename, replaceExisting); });
        bindContainer["saveWidgetsToFile"] = &tgui::Container::saveWidgetsToFile;
        bindContainer["loadWidgetsFromStream"] = static_cast<void (tgui::Container::*)(std::stringstream&, bool)>(
                &tgui::Container::loadWidgetsFromStream);
        bindContainer["saveWidgetsToStream"] = &tgui::Container::saveWidgetsToStream;
        bindContainer["moveWidgetToFront"] = &tgui::Container::moveWidgetToFront;
        bindContainer["moveWidgetToBack"] = &tgui::Container::moveWidgetToBack;
        bindContainer["moveWidgetForward"] = &tgui::Container::moveWidgetForward;
        bindContainer["moveWidgetBackward"] = &tgui::Container::moveWidgetBackward;
        bindContainer["getFocusedChild"] = &tgui::Container::getFocusedChild;
        bindContainer["getFocusedLeaf"] = &tgui::Container::getFocusedLeaf;
        bindContainer["getWidgetAtPosition"] = &tgui::Container::getWidgetAtPosition;
        bindContainer["focusNextWidget"] = sol::overload(
            [](tgui::Container* self) -> bool { return self->focusNextWidget(); },
            [](tgui::Container* self, bool recursive) -> bool {
                return self->focusNextWidget(recursive);
            });
        bindContainer["focusPreviousWidget"] = sol::overload(
            [](tgui::Container* self) -> bool { return self->focusPreviousWidget(); },
            [](tgui::Container* self, bool recursive) -> bool {
                return self->focusPreviousWidget(recursive);
            });
        bindContainer["setFocused"] = &tgui::Container::setFocused;
        bindContainer["processMouseMoveEvent"] = &tgui::Container::processMouseMoveEvent;
        bindContainer["processMousePressEvent"]
            = &tgui::Container::processMousePressEvent;
        bindContainer["processMouseReleaseEvent"]
            = &tgui::Container::processMouseReleaseEvent;
        bindContainer["processMouseWheelScrollEvent"]
            = &tgui::Container::processMouseWheelScrollEvent;
        bindContainer["processKeyPressEvent"] = &tgui::Container::processKeyPressEvent;
        bindContainer["processTextEnteredEvent"]
            = &tgui::Container::processTextEnteredEvent;
        bindContainer["childWidgetFocused"] = &tgui::Container::childWidgetFocused;
        bindContainer["leftMousePressed"] = &tgui::Container::leftMousePressed;
        bindContainer["rightMousePressed"] = &tgui::Container::rightMousePressed;
        bindContainer["leftMouseReleased"] = &tgui::Container::leftMouseReleased;
        bindContainer["rightMouseReleased"] = &tgui::Container::rightMouseReleased;
        bindContainer["mouseMoved"] = &tgui::Container::mouseMoved;
        bindContainer["keyPressed"] = &tgui::Container::keyPressed;
        bindContainer["textEntered"] = &tgui::Container::textEntered;
        bindContainer["mouseWheelScrolled"] = &tgui::Container::mouseWheelScrolled;
        bindContainer["mouseNoLongerOnWidget"] = &tgui::Container::mouseNoLongerOnWidget;
        bindContainer["leftMouseButtonNoLongerDown"]
            = &tgui::Container::leftMouseButtonNoLongerDown;
        bindContainer["rightMouseButtonNoLongerDown"]
            = &tgui::Container::rightMouseButtonNoLongerDown;
        bindContainer["askToolTip"] = &tgui::Container::askToolTip;
        bindContainer["updateTime"] = &tgui::Container::updateTime;
        bindContainer["setParent"] = &tgui::Container::setParent;
        bindContainer["setParentGui"] = &tgui::Container::setParentGui;
    }
};