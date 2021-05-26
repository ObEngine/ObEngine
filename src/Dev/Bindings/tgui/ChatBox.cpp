#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ChatBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassChatBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChatBox> bindChatBox
            = tguiNamespace.new_usertype<tgui::ChatBox>("ChatBox", sol::call_constructor,
                sol::constructors<tgui::ChatBox(), tgui::ChatBox(const char*),
                    tgui::ChatBox(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindChatBox["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ChatBoxRenderer* (tgui::ChatBox::*)()>(
                                &tgui::ChatBox::getSharedRenderer),
                static_cast<const tgui::ChatBoxRenderer* (tgui::ChatBox::*)() const>(
                    &tgui::ChatBox::getSharedRenderer));
        bindChatBox["getRenderer"]
            = sol::overload(static_cast<tgui::ChatBoxRenderer* (tgui::ChatBox::*)()>(
                                &tgui::ChatBox::getRenderer),
                static_cast<const tgui::ChatBoxRenderer* (tgui::ChatBox::*)() const>(
                    &tgui::ChatBox::getRenderer));
        bindChatBox["setSize"]
            = sol::overload(static_cast<void (tgui::ChatBox::*)(const tgui::Layout2d&)>(
                                &tgui::ChatBox::setSize),
                static_cast<void (tgui::ChatBox::*)(const tgui::Layout2d&)>(
                    &tgui::ChatBox::setSize),
                static_cast<void (tgui::ChatBox::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ChatBox::setSize));
        bindChatBox["addLine"]
            = sol::overload(static_cast<void (tgui::ChatBox::*)(const tgui::String&)>(
                                &tgui::ChatBox::addLine),
                static_cast<void (tgui::ChatBox::*)(const tgui::String&, tgui::Color)>(
                    &tgui::ChatBox::addLine),
                static_cast<void (tgui::ChatBox::*)(const tgui::String&, tgui::Color,
                    tgui::TextStyles)>(&tgui::ChatBox::addLine));
        bindChatBox["getLine"] = &tgui::ChatBox::getLine;
        bindChatBox["getLineColor"] = &tgui::ChatBox::getLineColor;
        bindChatBox["getLineTextStyle"] = &tgui::ChatBox::getLineTextStyle;
        bindChatBox["removeLine"] = &tgui::ChatBox::removeLine;
        bindChatBox["removeAllLines"] = &tgui::ChatBox::removeAllLines;
        bindChatBox["getLineAmount"] = &tgui::ChatBox::getLineAmount;
        bindChatBox["setLineLimit"] = &tgui::ChatBox::setLineLimit;
        bindChatBox["getLineLimit"] = &tgui::ChatBox::getLineLimit;
        bindChatBox["setTextSize"] = &tgui::ChatBox::setTextSize;
        bindChatBox["setTextColor"] = &tgui::ChatBox::setTextColor;
        bindChatBox["getTextColor"] = &tgui::ChatBox::getTextColor;
        bindChatBox["setTextStyle"] = &tgui::ChatBox::setTextStyle;
        bindChatBox["getTextStyle"] = &tgui::ChatBox::getTextStyle;
        bindChatBox["setLinesStartFromTop"] = sol::overload(
            [](tgui::ChatBox* self) -> void { return self->setLinesStartFromTop(); },
            [](tgui::ChatBox* self, bool startFromTop) -> void {
                return self->setLinesStartFromTop(startFromTop);
            });
        bindChatBox["getLinesStartFromTop"] = &tgui::ChatBox::getLinesStartFromTop;
        bindChatBox["setNewLinesBelowOthers"] = sol::overload(
            [](tgui::ChatBox* self) -> void { return self->setNewLinesBelowOthers(); },
            [](tgui::ChatBox* self, bool newLinesBelowOthers) -> void {
                return self->setNewLinesBelowOthers(newLinesBelowOthers);
            });
        bindChatBox["getNewLinesBelowOthers"] = &tgui::ChatBox::getNewLinesBelowOthers;
        bindChatBox["setScrollbarValue"] = &tgui::ChatBox::setScrollbarValue;
        bindChatBox["getScrollbarValue"] = &tgui::ChatBox::getScrollbarValue;
        bindChatBox["isMouseOnWidget"] = &tgui::ChatBox::isMouseOnWidget;
        bindChatBox["leftMousePressed"] = &tgui::ChatBox::leftMousePressed;
        bindChatBox["leftMouseReleased"] = &tgui::ChatBox::leftMouseReleased;
        bindChatBox["mouseMoved"] = &tgui::ChatBox::mouseMoved;
        bindChatBox["mouseWheelScrolled"] = &tgui::ChatBox::mouseWheelScrolled;
        bindChatBox["mouseNoLongerOnWidget"] = &tgui::ChatBox::mouseNoLongerOnWidget;
        bindChatBox["leftMouseButtonNoLongerDown"]
            = &tgui::ChatBox::leftMouseButtonNoLongerDown;
        bindChatBox["create"] = &tgui::ChatBox::create;
        bindChatBox["copy"] = &tgui::ChatBox::copy;
    }
};