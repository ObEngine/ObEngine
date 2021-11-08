#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/MessageBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMessageBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MessageBox> bindMessageBox
            = tguiNamespace.new_usertype<tgui::MessageBox>("MessageBox", sol::call_constructor,
                sol::constructors<tgui::MessageBox(), tgui::MessageBox(const char*),
                    tgui::MessageBox(const char*, bool),
                    tgui::MessageBox(const tgui::MessageBox&)>(),
                sol::base_classes, sol::bases<tgui::ChildWindow, tgui::Container, tgui::Widget>());
        bindMessageBox["operator="] = sol::overload(
            static_cast<tgui::MessageBox& (tgui::MessageBox::*)(const tgui::MessageBox&)>(
                &tgui::MessageBox::operator=),
            static_cast<tgui::MessageBox& (tgui::MessageBox::*)(tgui::MessageBox &&)>(
                &tgui::MessageBox::operator=));
        bindMessageBox["getSharedRenderer"]
            = sol::overload(static_cast<tgui::MessageBoxRenderer* (tgui::MessageBox::*)()>(
                                &tgui::MessageBox::getSharedRenderer),
                static_cast<const tgui::MessageBoxRenderer* (tgui::MessageBox::*)() const>(
                    &tgui::MessageBox::getSharedRenderer));
        bindMessageBox["getRenderer"]
            = sol::overload(static_cast<tgui::MessageBoxRenderer* (tgui::MessageBox::*)()>(
                                &tgui::MessageBox::getRenderer),
                static_cast<const tgui::MessageBoxRenderer* (tgui::MessageBox::*)() const>(
                    &tgui::MessageBox::getRenderer));
        bindMessageBox["setText"] = &tgui::MessageBox::setText;
        bindMessageBox["getText"] = &tgui::MessageBox::getText;
        bindMessageBox["setTextSize"] = &tgui::MessageBox::setTextSize;
        bindMessageBox["addButton"] = &tgui::MessageBox::addButton;
        bindMessageBox["getButtons"] = &tgui::MessageBox::getButtons;
        bindMessageBox["create"]
            = sol::overload([]() -> tgui::MessageBox::Ptr { return tgui::MessageBox::create(); },
                [](tgui::String title) -> tgui::MessageBox::Ptr {
                    return tgui::MessageBox::create(title);
                },
                [](tgui::String title, tgui::String text) -> tgui::MessageBox::Ptr {
                    return tgui::MessageBox::create(title, text);
                },
                [](tgui::String title, tgui::String text,
                    std::vector<tgui::String> buttons) -> tgui::MessageBox::Ptr {
                    return tgui::MessageBox::create(title, text, buttons);
                });
        bindMessageBox["copy"] = &tgui::MessageBox::copy;
        bindMessageBox["onButtonPress"] = &tgui::MessageBox::onButtonPress;
    }
};