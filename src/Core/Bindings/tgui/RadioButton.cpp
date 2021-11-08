#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/RadioButton.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRadioButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RadioButton> bindRadioButton
            = tguiNamespace.new_usertype<tgui::RadioButton>("RadioButton", sol::call_constructor,
                sol::constructors<tgui::RadioButton(), tgui::RadioButton(const char*),
                    tgui::RadioButton(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindRadioButton["getSharedRenderer"]
            = sol::overload(static_cast<tgui::RadioButtonRenderer* (tgui::RadioButton::*)()>(
                                &tgui::RadioButton::getSharedRenderer),
                static_cast<const tgui::RadioButtonRenderer* (tgui::RadioButton::*)() const>(
                    &tgui::RadioButton::getSharedRenderer));
        bindRadioButton["getRenderer"]
            = sol::overload(static_cast<tgui::RadioButtonRenderer* (tgui::RadioButton::*)()>(
                                &tgui::RadioButton::getRenderer),
                static_cast<const tgui::RadioButtonRenderer* (tgui::RadioButton::*)() const>(
                    &tgui::RadioButton::getRenderer));
        bindRadioButton["setSize"]
            = sol::overload(static_cast<void (tgui::RadioButton::*)(const tgui::Layout2d&)>(
                                &tgui::RadioButton::setSize),
                static_cast<void (tgui::RadioButton::*)(const tgui::Layout2d&)>(
                    &tgui::RadioButton::setSize),
                static_cast<void (tgui::RadioButton::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::RadioButton::setSize));
        bindRadioButton["getFullSize"] = &tgui::RadioButton::getFullSize;
        bindRadioButton["getWidgetOffset"] = &tgui::RadioButton::getWidgetOffset;
        bindRadioButton["setChecked"] = &tgui::RadioButton::setChecked;
        bindRadioButton["isChecked"] = &tgui::RadioButton::isChecked;
        bindRadioButton["setText"] = &tgui::RadioButton::setText;
        bindRadioButton["getText"] = &tgui::RadioButton::getText;
        bindRadioButton["setTextSize"] = &tgui::RadioButton::setTextSize;
        bindRadioButton["getTextSize"] = &tgui::RadioButton::getTextSize;
        bindRadioButton["setTextClickable"] = &tgui::RadioButton::setTextClickable;
        bindRadioButton["isTextClickable"] = &tgui::RadioButton::isTextClickable;
        bindRadioButton["isMouseOnWidget"] = &tgui::RadioButton::isMouseOnWidget;
        bindRadioButton["leftMouseReleased"] = &tgui::RadioButton::leftMouseReleased;
        bindRadioButton["keyPressed"] = &tgui::RadioButton::keyPressed;
        bindRadioButton["draw"] = &tgui::RadioButton::draw;
        bindRadioButton["create"] = &tgui::RadioButton::create;
        bindRadioButton["copy"] = &tgui::RadioButton::copy;
        bindRadioButton["onCheck"] = &tgui::RadioButton::onCheck;
        bindRadioButton["onUncheck"] = &tgui::RadioButton::onUncheck;
        bindRadioButton["onChange"] = &tgui::RadioButton::onChange;
    }
};