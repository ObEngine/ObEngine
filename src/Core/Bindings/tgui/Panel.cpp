#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Panel.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassPanel(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Panel> bindPanel
            = tguiNamespace.new_usertype<tgui::Panel>("Panel", sol::call_constructor,
                sol::constructors<tgui::Panel(), tgui::Panel(const char*),
                    tgui::Panel(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Group, tgui::Container, tgui::Widget>());
        bindPanel["getSharedRenderer"] = sol::overload(
            static_cast<tgui::PanelRenderer* (tgui::Panel::*)()>(&tgui::Panel::getSharedRenderer),
            static_cast<const tgui::PanelRenderer* (tgui::Panel::*)() const>(
                &tgui::Panel::getSharedRenderer));
        bindPanel["getRenderer"] = sol::overload(
            static_cast<tgui::PanelRenderer* (tgui::Panel::*)()>(&tgui::Panel::getRenderer),
            static_cast<const tgui::PanelRenderer* (tgui::Panel::*)() const>(
                &tgui::Panel::getRenderer));
        bindPanel["setSize"] = sol::overload(
            static_cast<void (tgui::Panel::*)(const tgui::Layout2d&)>(&tgui::Panel::setSize),
            static_cast<void (tgui::Panel::*)(const tgui::Layout2d&)>(&tgui::Panel::setSize),
            static_cast<void (tgui::Panel::*)(tgui::Layout, tgui::Layout)>(&tgui::Panel::setSize));
        bindPanel["getInnerSize"] = &tgui::Panel::getInnerSize;
        bindPanel["getChildWidgetsOffset"] = &tgui::Panel::getChildWidgetsOffset;
        bindPanel["isMouseOnWidget"] = &tgui::Panel::isMouseOnWidget;
        bindPanel["leftMousePressed"] = &tgui::Panel::leftMousePressed;
        bindPanel["leftMouseReleased"] = &tgui::Panel::leftMouseReleased;
        bindPanel["rightMousePressed"] = &tgui::Panel::rightMousePressed;
        bindPanel["rightMouseReleased"] = &tgui::Panel::rightMouseReleased;
        bindPanel["rightMouseButtonNoLongerDown"] = &tgui::Panel::rightMouseButtonNoLongerDown;
        bindPanel["draw"] = &tgui::Panel::draw;
        bindPanel["create"]
            = sol::overload([]() -> tgui::Panel::Ptr { return tgui::Panel::create(); },
                [](tgui::Layout2d size) -> tgui::Panel::Ptr { return tgui::Panel::create(size); });
        bindPanel["copy"] = &tgui::Panel::copy;
        bindPanel["onMousePress"] = &tgui::Panel::onMousePress;
        bindPanel["onMouseRelease"] = &tgui::Panel::onMouseRelease;
        bindPanel["onClick"] = &tgui::Panel::onClick;
        bindPanel["onDoubleClick"] = &tgui::Panel::onDoubleClick;
        bindPanel["onRightMousePress"] = &tgui::Panel::onRightMousePress;
        bindPanel["onRightMouseRelease"] = &tgui::Panel::onRightMouseRelease;
        bindPanel["onRightClick"] = &tgui::Panel::onRightClick;
    }
};