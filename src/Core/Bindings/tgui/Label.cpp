#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Label.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassLabel(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Label> bindLabel
            = tguiNamespace.new_usertype<tgui::Label>("Label", sol::call_constructor,
                sol::constructors<tgui::Label(), tgui::Label(const char*),
                    tgui::Label(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindLabel["getSharedRenderer"] = sol::overload(
            static_cast<tgui::LabelRenderer* (tgui::Label::*)()>(&tgui::Label::getSharedRenderer),
            static_cast<const tgui::LabelRenderer* (tgui::Label::*)() const>(
                &tgui::Label::getSharedRenderer));
        bindLabel["getRenderer"] = sol::overload(
            static_cast<tgui::LabelRenderer* (tgui::Label::*)()>(&tgui::Label::getRenderer),
            static_cast<const tgui::LabelRenderer* (tgui::Label::*)() const>(
                &tgui::Label::getRenderer));
        bindLabel["setSize"] = sol::overload(
            static_cast<void (tgui::Label::*)(const tgui::Layout2d&)>(&tgui::Label::setSize),
            static_cast<void (tgui::Label::*)(const tgui::Layout2d&)>(&tgui::Label::setSize),
            static_cast<void (tgui::Label::*)(tgui::Layout, tgui::Layout)>(&tgui::Label::setSize));
        bindLabel["setText"] = &tgui::Label::setText;
        bindLabel["getText"] = &tgui::Label::getText;
        bindLabel["setTextSize"] = &tgui::Label::setTextSize;
        bindLabel["setHorizontalAlignment"] = &tgui::Label::setHorizontalAlignment;
        bindLabel["getHorizontalAlignment"] = &tgui::Label::getHorizontalAlignment;
        bindLabel["setVerticalAlignment"] = &tgui::Label::setVerticalAlignment;
        bindLabel["getVerticalAlignment"] = &tgui::Label::getVerticalAlignment;
        bindLabel["setScrollbarPolicy"] = &tgui::Label::setScrollbarPolicy;
        bindLabel["getScrollbarPolicy"] = &tgui::Label::getScrollbarPolicy;
        bindLabel["setAutoSize"] = &tgui::Label::setAutoSize;
        bindLabel["getAutoSize"] = &tgui::Label::getAutoSize;
        bindLabel["setMaximumTextWidth"] = &tgui::Label::setMaximumTextWidth;
        bindLabel["getMaximumTextWidth"] = &tgui::Label::getMaximumTextWidth;
        bindLabel["ignoreMouseEvents"] = sol::overload(
            [](tgui::Label* self) -> void { return self->ignoreMouseEvents(); },
            [](tgui::Label* self, bool ignore) -> void { return self->ignoreMouseEvents(ignore); });
        bindLabel["isIgnoringMouseEvents"] = &tgui::Label::isIgnoringMouseEvents;
        bindLabel["setParent"] = &tgui::Label::setParent;
        bindLabel["canGainFocus"] = &tgui::Label::canGainFocus;
        bindLabel["isMouseOnWidget"] = &tgui::Label::isMouseOnWidget;
        bindLabel["leftMousePressed"] = &tgui::Label::leftMousePressed;
        bindLabel["leftMouseReleased"] = &tgui::Label::leftMouseReleased;
        bindLabel["mouseMoved"] = &tgui::Label::mouseMoved;
        bindLabel["mouseWheelScrolled"] = &tgui::Label::mouseWheelScrolled;
        bindLabel["mouseNoLongerOnWidget"] = &tgui::Label::mouseNoLongerOnWidget;
        bindLabel["leftMouseButtonNoLongerDown"] = &tgui::Label::leftMouseButtonNoLongerDown;
        bindLabel["draw"] = &tgui::Label::draw;
        bindLabel["create"]
            = sol::overload([]() -> tgui::Label::Ptr { return tgui::Label::create(); },
                [](tgui::String text) -> tgui::Label::Ptr { return tgui::Label::create(text); });
        bindLabel["copy"] = &tgui::Label::copy;
        bindLabel["onDoubleClick"] = &tgui::Label::onDoubleClick;
    }
};