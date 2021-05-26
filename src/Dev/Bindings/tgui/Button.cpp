#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/Button.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Button> bindButton
            = tguiNamespace.new_usertype<tgui::Button>("Button", sol::call_constructor,
                sol::constructors<tgui::Button(), tgui::Button(const char*),
                    tgui::Button(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::ButtonBase, tgui::ClickableWidget, tgui::Widget>());
        bindButton["leftMousePressed"] = &tgui::Button::leftMousePressed;
        bindButton["leftMouseReleased"] = &tgui::Button::leftMouseReleased;
        bindButton["leftMouseButtonNoLongerDown"]
            = &tgui::Button::leftMouseButtonNoLongerDown;
        bindButton["keyPressed"] = &tgui::Button::keyPressed;
        bindButton["create"] = sol::overload(
            [](tgui::Button* self) -> tgui::Button::Ptr { return self->create(); },
            [](tgui::Button* self, const tgui::String& text) -> tgui::Button::Ptr {
                return self->create(text);
            });
        bindButton["copy"] = &tgui::Button::copy;
        bindButton["onPress"] = &tgui::Button::onPress;
    }
};