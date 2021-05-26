#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ChildWindow.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassChildWindow(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChildWindow> bindChildWindow
            = tguiNamespace.new_usertype<tgui::ChildWindow>("ChildWindow",
                sol::call_constructor,
                sol::constructors<tgui::ChildWindow(), tgui::ChildWindow(const char*),
                    tgui::ChildWindow(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindChildWindow["getSharedRenderer"] = sol::overload(
            static_cast<tgui::ChildWindowRenderer* (tgui::ChildWindow::*)()>(
                &tgui::ChildWindow::getSharedRenderer),
            static_cast<const tgui::ChildWindowRenderer* (tgui::ChildWindow::*)() const>(
                &tgui::ChildWindow::getSharedRenderer));
        bindChildWindow["getRenderer"] = sol::overload(
            static_cast<tgui::ChildWindowRenderer* (tgui::ChildWindow::*)()>(
                &tgui::ChildWindow::getRenderer),
            static_cast<const tgui::ChildWindowRenderer* (tgui::ChildWindow::*)() const>(
                &tgui::ChildWindow::getRenderer));
        bindChildWindow["setPosition"] = sol::overload(
            static_cast<void (tgui::ChildWindow::*)(const tgui::Layout2d&)>(
                &tgui::ChildWindow::setPosition),
            static_cast<void (tgui::ChildWindow::*)(const tgui::Layout2d&)>(
                &tgui::ChildWindow::setPosition),
            static_cast<void (tgui::ChildWindow::*)(tgui::Layout, tgui::Layout)>(
                &tgui::ChildWindow::setPosition));
        bindChildWindow["setSize"] = sol::overload(
            static_cast<void (tgui::ChildWindow::*)(const tgui::Layout2d&)>(
                &tgui::ChildWindow::setSize),
            static_cast<void (tgui::ChildWindow::*)(const tgui::Layout2d&)>(
                &tgui::ChildWindow::setSize),
            static_cast<void (tgui::ChildWindow::*)(tgui::Layout, tgui::Layout)>(
                &tgui::ChildWindow::setSize));
        bindChildWindow["getInnerSize"] = &tgui::ChildWindow::getInnerSize;
        bindChildWindow["setClientSize"] = &tgui::ChildWindow::setClientSize;
        bindChildWindow["getClientSize"] = &tgui::ChildWindow::getClientSize;
        bindChildWindow["setMaximumSize"] = &tgui::ChildWindow::setMaximumSize;
        bindChildWindow["getMaximumSize"] = &tgui::ChildWindow::getMaximumSize;
        bindChildWindow["setMinimumSize"] = &tgui::ChildWindow::setMinimumSize;
        bindChildWindow["getMinimumSize"] = &tgui::ChildWindow::getMinimumSize;
        bindChildWindow["setTitle"] = &tgui::ChildWindow::setTitle;
        bindChildWindow["getTitle"] = &tgui::ChildWindow::getTitle;
        bindChildWindow["setTitleTextSize"] = &tgui::ChildWindow::setTitleTextSize;
        bindChildWindow["getTitleTextSize"] = &tgui::ChildWindow::getTitleTextSize;
        bindChildWindow["setTitleAlignment"] = &tgui::ChildWindow::setTitleAlignment;
        bindChildWindow["getTitleAlignment"] = &tgui::ChildWindow::getTitleAlignment;
        bindChildWindow["setTitleButtons"] = &tgui::ChildWindow::setTitleButtons;
        bindChildWindow["getTitleButtons"] = &tgui::ChildWindow::getTitleButtons;
        bindChildWindow["close"] = &tgui::ChildWindow::close;
        bindChildWindow["destroy"] = &tgui::ChildWindow::destroy;
        bindChildWindow["setResizable"] = sol::overload(
            [](tgui::ChildWindow* self) -> void { return self->setResizable(); },
            [](tgui::ChildWindow* self, bool resizable) -> void {
                return self->setResizable(resizable);
            });
        bindChildWindow["isResizable"] = &tgui::ChildWindow::isResizable;
        bindChildWindow["setPositionLocked"] = sol::overload(
            [](tgui::ChildWindow* self) -> void { return self->setPositionLocked(); },
            [](tgui::ChildWindow* self, bool positionLocked) -> void {
                return self->setPositionLocked(positionLocked);
            });
        bindChildWindow["isPositionLocked"] = &tgui::ChildWindow::isPositionLocked;
        bindChildWindow["setKeepInParent"] = sol::overload(
            [](tgui::ChildWindow* self) -> void { return self->setKeepInParent(); },
            [](tgui::ChildWindow* self, bool enabled) -> void {
                return self->setKeepInParent(enabled);
            });
        bindChildWindow["isKeptInParent"] = &tgui::ChildWindow::isKeptInParent;
        bindChildWindow["getChildWidgetsOffset"]
            = &tgui::ChildWindow::getChildWidgetsOffset;
        bindChildWindow["setParent"] = &tgui::ChildWindow::setParent;
        bindChildWindow["isMouseOnWidget"] = &tgui::ChildWindow::isMouseOnWidget;
        bindChildWindow["leftMousePressed"] = &tgui::ChildWindow::leftMousePressed;
        bindChildWindow["leftMouseReleased"] = &tgui::ChildWindow::leftMouseReleased;
        bindChildWindow["rightMousePressed"] = &tgui::ChildWindow::rightMousePressed;
        bindChildWindow["rightMouseReleased"] = &tgui::ChildWindow::rightMouseReleased;
        bindChildWindow["mouseMoved"] = &tgui::ChildWindow::mouseMoved;
        bindChildWindow["keyPressed"] = &tgui::ChildWindow::keyPressed;
        bindChildWindow["mouseNoLongerOnWidget"]
            = &tgui::ChildWindow::mouseNoLongerOnWidget;
        bindChildWindow["leftMouseButtonNoLongerDown"]
            = &tgui::ChildWindow::leftMouseButtonNoLongerDown;
        bindChildWindow["draw"] =

            [](tgui::ChildWindow* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindChildWindow["create"] = sol::overload(
            [](tgui::ChildWindow* self) -> tgui::ChildWindow::Ptr {
                return self->create();
            },
            [](tgui::ChildWindow* self, const tgui::String& title)
                -> tgui::ChildWindow::Ptr { return self->create(title); },
            [](tgui::ChildWindow* self, const tgui::String& title,
                unsigned int titleButtons) -> tgui::ChildWindow::Ptr {
                return self->create(title, titleButtons);
            });
        bindChildWindow["copy"] = &tgui::ChildWindow::copy;
        bindChildWindow["onMousePress"] = &tgui::ChildWindow::onMousePress;
        bindChildWindow["onClose"] = &tgui::ChildWindow::onClose;
        bindChildWindow["onMinimize"] = &tgui::ChildWindow::onMinimize;
        bindChildWindow["onMaximize"] = &tgui::ChildWindow::onMaximize;
        bindChildWindow["onEscapeKeyPress"] = &tgui::ChildWindow::onEscapeKeyPress;
        bindChildWindow["onClosing"] = &tgui::ChildWindow::onClosing;
    }
};