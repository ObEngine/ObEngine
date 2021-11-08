#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ScrollablePanel.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassScrollablePanel(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollablePanel> bindScrollablePanel
            = tguiNamespace.new_usertype<tgui::ScrollablePanel>("ScrollablePanel",
                sol::call_constructor,
                sol::constructors<tgui::ScrollablePanel(), tgui::ScrollablePanel(const char*),
                    tgui::ScrollablePanel(const char*, bool),
                    tgui::ScrollablePanel(const tgui::ScrollablePanel&)>(),
                sol::base_classes,
                sol::bases<tgui::Panel, tgui::Group, tgui::Container, tgui::Widget>());
        bindScrollablePanel["operator="]
            = sol::overload(static_cast<tgui::ScrollablePanel& (
                                tgui::ScrollablePanel::*)(const tgui::ScrollablePanel&)>(
                                &tgui::ScrollablePanel::operator=),
                static_cast<tgui::ScrollablePanel& (tgui::ScrollablePanel::*)(tgui::ScrollablePanel
                    &&)>(&tgui::ScrollablePanel::operator=));
        bindScrollablePanel["getSharedRenderer"] = sol::overload(
            static_cast<tgui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)()>(
                &tgui::ScrollablePanel::getSharedRenderer),
            static_cast<const tgui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)() const>(
                &tgui::ScrollablePanel::getSharedRenderer));
        bindScrollablePanel["getRenderer"] = sol::overload(
            static_cast<tgui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)()>(
                &tgui::ScrollablePanel::getRenderer),
            static_cast<const tgui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)() const>(
                &tgui::ScrollablePanel::getRenderer));
        bindScrollablePanel["setSize"]
            = sol::overload(static_cast<void (tgui::ScrollablePanel::*)(const tgui::Layout2d&)>(
                                &tgui::ScrollablePanel::setSize),
                static_cast<void (tgui::ScrollablePanel::*)(const tgui::Layout2d&)>(
                    &tgui::ScrollablePanel::setSize),
                static_cast<void (tgui::ScrollablePanel::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ScrollablePanel::setSize));
        bindScrollablePanel["getAbsolutePosition"] = &tgui::ScrollablePanel::getAbsolutePosition;
        bindScrollablePanel["add"] = sol::overload(
            [](tgui::ScrollablePanel* self, const tgui::Widget::Ptr& widget) -> void {
                return self->add(widget);
            },
            [](tgui::ScrollablePanel* self, const tgui::Widget::Ptr& widget,
                const tgui::String& widgetName) -> void { return self->add(widget, widgetName); });
        bindScrollablePanel["remove"] = &tgui::ScrollablePanel::remove;
        bindScrollablePanel["removeAllWidgets"] = &tgui::ScrollablePanel::removeAllWidgets;
        bindScrollablePanel["setContentSize"] = &tgui::ScrollablePanel::setContentSize;
        bindScrollablePanel["getContentSize"] = &tgui::ScrollablePanel::getContentSize;
        bindScrollablePanel["getContentOffset"] = &tgui::ScrollablePanel::getContentOffset;
        bindScrollablePanel["getScrollbarWidth"] = &tgui::ScrollablePanel::getScrollbarWidth;
        bindScrollablePanel["setVerticalScrollbarPolicy"]
            = &tgui::ScrollablePanel::setVerticalScrollbarPolicy;
        bindScrollablePanel["getVerticalScrollbarPolicy"]
            = &tgui::ScrollablePanel::getVerticalScrollbarPolicy;
        bindScrollablePanel["setHorizontalScrollbarPolicy"]
            = &tgui::ScrollablePanel::setHorizontalScrollbarPolicy;
        bindScrollablePanel["getHorizontalScrollbarPolicy"]
            = &tgui::ScrollablePanel::getHorizontalScrollbarPolicy;
        bindScrollablePanel["setVerticalScrollAmount"]
            = &tgui::ScrollablePanel::setVerticalScrollAmount;
        bindScrollablePanel["getVerticalScrollAmount"]
            = &tgui::ScrollablePanel::getVerticalScrollAmount;
        bindScrollablePanel["setHorizontalScrollAmount"]
            = &tgui::ScrollablePanel::setHorizontalScrollAmount;
        bindScrollablePanel["getHorizontalScrollAmount"]
            = &tgui::ScrollablePanel::getHorizontalScrollAmount;
        bindScrollablePanel["setVerticalScrollbarValue"]
            = &tgui::ScrollablePanel::setVerticalScrollbarValue;
        bindScrollablePanel["getVerticalScrollbarValue"]
            = &tgui::ScrollablePanel::getVerticalScrollbarValue;
        bindScrollablePanel["setHorizontalScrollbarValue"]
            = &tgui::ScrollablePanel::setHorizontalScrollbarValue;
        bindScrollablePanel["getHorizontalScrollbarValue"]
            = &tgui::ScrollablePanel::getHorizontalScrollbarValue;
        bindScrollablePanel["getWidgetAtPosition"] = &tgui::ScrollablePanel::getWidgetAtPosition;
        bindScrollablePanel["leftMousePressed"] = &tgui::ScrollablePanel::leftMousePressed;
        bindScrollablePanel["leftMouseReleased"] = &tgui::ScrollablePanel::leftMouseReleased;
        bindScrollablePanel["mouseMoved"] = &tgui::ScrollablePanel::mouseMoved;
        bindScrollablePanel["mouseWheelScrolled"] = &tgui::ScrollablePanel::mouseWheelScrolled;
        bindScrollablePanel["mouseNoLongerOnWidget"]
            = &tgui::ScrollablePanel::mouseNoLongerOnWidget;
        bindScrollablePanel["leftMouseButtonNoLongerDown"]
            = &tgui::ScrollablePanel::leftMouseButtonNoLongerDown;
        bindScrollablePanel["askToolTip"] = &tgui::ScrollablePanel::askToolTip;
        bindScrollablePanel["draw"] = &tgui::ScrollablePanel::draw;
        bindScrollablePanel["create"] = sol::overload(
            []() -> tgui::ScrollablePanel::Ptr { return tgui::ScrollablePanel::create(); },
            [](tgui::Layout2d size) -> tgui::ScrollablePanel::Ptr {
                return tgui::ScrollablePanel::create(size);
            },
            [](tgui::Layout2d size, tgui::Vector2f contentSize) -> tgui::ScrollablePanel::Ptr {
                return tgui::ScrollablePanel::create(size, contentSize);
            });
        bindScrollablePanel["copy"] = &tgui::ScrollablePanel::copy;
    }
};