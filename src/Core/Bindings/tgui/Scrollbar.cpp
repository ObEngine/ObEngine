#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Scrollbar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassScrollbar(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Scrollbar> bindScrollbar
            = tguiNamespace.new_usertype<tgui::Scrollbar>("Scrollbar", sol::call_constructor,
                sol::constructors<tgui::Scrollbar(), tgui::Scrollbar(const char*),
                    tgui::Scrollbar(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindScrollbar["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ScrollbarRenderer* (tgui::Scrollbar::*)()>(
                                &tgui::Scrollbar::getSharedRenderer),
                static_cast<const tgui::ScrollbarRenderer* (tgui::Scrollbar::*)() const>(
                    &tgui::Scrollbar::getSharedRenderer));
        bindScrollbar["getRenderer"]
            = sol::overload(static_cast<tgui::ScrollbarRenderer* (tgui::Scrollbar::*)()>(
                                &tgui::Scrollbar::getRenderer),
                static_cast<const tgui::ScrollbarRenderer* (tgui::Scrollbar::*)() const>(
                    &tgui::Scrollbar::getRenderer));
        bindScrollbar["setSize"]
            = sol::overload(static_cast<void (tgui::Scrollbar::*)(const tgui::Layout2d&)>(
                                &tgui::Scrollbar::setSize),
                static_cast<void (tgui::Scrollbar::*)(const tgui::Layout2d&)>(
                    &tgui::Scrollbar::setSize),
                static_cast<void (tgui::Scrollbar::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::Scrollbar::setSize));
        bindScrollbar["setMaximum"] = &tgui::Scrollbar::setMaximum;
        bindScrollbar["getMaximum"] = &tgui::Scrollbar::getMaximum;
        bindScrollbar["setValue"] = &tgui::Scrollbar::setValue;
        bindScrollbar["getValue"] = &tgui::Scrollbar::getValue;
        bindScrollbar["setViewportSize"] = &tgui::Scrollbar::setViewportSize;
        bindScrollbar["getViewportSize"] = &tgui::Scrollbar::getViewportSize;
        bindScrollbar["setScrollAmount"] = &tgui::Scrollbar::setScrollAmount;
        bindScrollbar["getScrollAmount"] = &tgui::Scrollbar::getScrollAmount;
        bindScrollbar["setAutoHide"] = &tgui::Scrollbar::setAutoHide;
        bindScrollbar["getAutoHide"] = &tgui::Scrollbar::getAutoHide;
        bindScrollbar["setVerticalScroll"] = &tgui::Scrollbar::setVerticalScroll;
        bindScrollbar["getVerticalScroll"] = &tgui::Scrollbar::getVerticalScroll;
        bindScrollbar["getDefaultWidth"] = &tgui::Scrollbar::getDefaultWidth;
        bindScrollbar["isMouseOnWidget"] = &tgui::Scrollbar::isMouseOnWidget;
        bindScrollbar["leftMousePressed"] = &tgui::Scrollbar::leftMousePressed;
        bindScrollbar["leftMouseReleased"] = &tgui::Scrollbar::leftMouseReleased;
        bindScrollbar["mouseMoved"] = &tgui::Scrollbar::mouseMoved;
        bindScrollbar["mouseWheelScrolled"] = &tgui::Scrollbar::mouseWheelScrolled;
        bindScrollbar["leftMouseButtonNoLongerDown"]
            = &tgui::Scrollbar::leftMouseButtonNoLongerDown;
        bindScrollbar["draw"] = &tgui::Scrollbar::draw;
        bindScrollbar["create"] = &tgui::Scrollbar::create;
        bindScrollbar["copy"] = &tgui::Scrollbar::copy;
        bindScrollbar["onValueChange"] = &tgui::Scrollbar::onValueChange;
    }
};