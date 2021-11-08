#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/SubwidgetContainer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSubwidgetContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SubwidgetContainer> bindSubwidgetContainer
            = tguiNamespace.new_usertype<tgui::SubwidgetContainer>(
                "SubwidgetContainer", sol::base_classes, sol::bases<tgui::Widget>());
        bindSubwidgetContainer["setSize"]
            = sol::overload(static_cast<void (tgui::SubwidgetContainer::*)(const tgui::Layout2d&)>(
                                &tgui::SubwidgetContainer::setSize),
                static_cast<void (tgui::SubwidgetContainer::*)(const tgui::Layout2d&)>(
                    &tgui::SubwidgetContainer::setSize),
                static_cast<void (tgui::SubwidgetContainer::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::SubwidgetContainer::setSize));
        bindSubwidgetContainer["setFocused"] = &tgui::SubwidgetContainer::setFocused;
        bindSubwidgetContainer["setTextSize"] = &tgui::SubwidgetContainer::setTextSize;
        bindSubwidgetContainer["getContainer"]
            = sol::overload(static_cast<tgui::Container* (tgui::SubwidgetContainer::*)()>(
                                &tgui::SubwidgetContainer::getContainer),
                static_cast<const tgui::Container* (tgui::SubwidgetContainer::*)() const>(
                    &tgui::SubwidgetContainer::getContainer));
        bindSubwidgetContainer["leftMousePressed"] = &tgui::SubwidgetContainer::leftMousePressed;
        bindSubwidgetContainer["leftMouseReleased"] = &tgui::SubwidgetContainer::leftMouseReleased;
        bindSubwidgetContainer["rightMousePressed"] = &tgui::SubwidgetContainer::rightMousePressed;
        bindSubwidgetContainer["rightMouseReleased"]
            = &tgui::SubwidgetContainer::rightMouseReleased;
        bindSubwidgetContainer["mouseMoved"] = &tgui::SubwidgetContainer::mouseMoved;
        bindSubwidgetContainer["keyPressed"] = &tgui::SubwidgetContainer::keyPressed;
        bindSubwidgetContainer["textEntered"] = &tgui::SubwidgetContainer::textEntered;
        bindSubwidgetContainer["mouseWheelScrolled"]
            = &tgui::SubwidgetContainer::mouseWheelScrolled;
        bindSubwidgetContainer["mouseNoLongerOnWidget"]
            = &tgui::SubwidgetContainer::mouseNoLongerOnWidget;
        bindSubwidgetContainer["leftMouseButtonNoLongerDown"]
            = &tgui::SubwidgetContainer::leftMouseButtonNoLongerDown;
        bindSubwidgetContainer["rightMouseButtonNoLongerDown"]
            = &tgui::SubwidgetContainer::rightMouseButtonNoLongerDown;
        bindSubwidgetContainer["askToolTip"] = &tgui::SubwidgetContainer::askToolTip;
        bindSubwidgetContainer["updateTime"] = &tgui::SubwidgetContainer::updateTime;
        bindSubwidgetContainer["isMouseOnWidget"] = &tgui::SubwidgetContainer::isMouseOnWidget;
        bindSubwidgetContainer["setParent"] = &tgui::SubwidgetContainer::setParent;
    }
};