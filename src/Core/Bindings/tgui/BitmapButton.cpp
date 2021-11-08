#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/BitmapButton.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBitmapButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BitmapButton> bindBitmapButton
            = tguiNamespace.new_usertype<tgui::BitmapButton>("BitmapButton", sol::call_constructor,
                sol::constructors<tgui::BitmapButton(), tgui::BitmapButton(const char*),
                    tgui::BitmapButton(const char*, bool),
                    tgui::BitmapButton(const tgui::BitmapButton&)>(),
                sol::base_classes,
                sol::bases<tgui::Button, tgui::ButtonBase, tgui::ClickableWidget, tgui::Widget>());
        bindBitmapButton["operator="] = sol::overload(
            static_cast<tgui::BitmapButton& (tgui::BitmapButton::*)(const tgui::BitmapButton&)>(
                &tgui::BitmapButton::operator=),
            static_cast<tgui::BitmapButton& (tgui::BitmapButton::*)(tgui::BitmapButton &&)>(
                &tgui::BitmapButton::operator=));
        bindBitmapButton["setSize"]
            = sol::overload(static_cast<void (tgui::BitmapButton::*)(const tgui::Layout2d&)>(
                                &tgui::BitmapButton::setSize),
                static_cast<void (tgui::BitmapButton::*)(const tgui::Layout2d&)>(
                    &tgui::BitmapButton::setSize),
                static_cast<void (tgui::BitmapButton::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::BitmapButton::setSize));
        bindBitmapButton["setText"] = &tgui::BitmapButton::setText;
        bindBitmapButton["setImage"] = &tgui::BitmapButton::setImage;
        bindBitmapButton["getImage"] = &tgui::BitmapButton::getImage;
        bindBitmapButton["setImageScaling"] = &tgui::BitmapButton::setImageScaling;
        bindBitmapButton["getImageScaling"] = &tgui::BitmapButton::getImageScaling;
        bindBitmapButton["create"] = sol::overload(
            []() -> tgui::BitmapButton::Ptr { return tgui::BitmapButton::create(); },
            [](const tgui::String& text) -> tgui::BitmapButton::Ptr {
                return tgui::BitmapButton::create(text);
            });
        bindBitmapButton["copy"] = &tgui::BitmapButton::copy;
    }
};