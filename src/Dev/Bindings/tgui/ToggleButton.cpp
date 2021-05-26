#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ToggleButton.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassToggleButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ToggleButton> bindToggleButton
            = tguiNamespace.new_usertype<tgui::ToggleButton>("ToggleButton",
                sol::call_constructor,
                sol::constructors<tgui::ToggleButton(), tgui::ToggleButton(const char*),
                    tgui::ToggleButton(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::ButtonBase, tgui::ClickableWidget, tgui::Widget>());
        bindToggleButton["setDown"] = &tgui::ToggleButton::setDown;
        bindToggleButton["isDown"] = &tgui::ToggleButton::isDown;
        bindToggleButton["leftMouseReleased"] = &tgui::ToggleButton::leftMouseReleased;
        bindToggleButton["keyPressed"] = &tgui::ToggleButton::keyPressed;
        bindToggleButton["create"] = sol::overload(
            [](tgui::ToggleButton* self) -> tgui::ToggleButton::Ptr {
                return self->create();
            },
            [](tgui::ToggleButton* self, const tgui::String& text)
                -> tgui::ToggleButton::Ptr { return self->create(text); },
            [](tgui::ToggleButton* self, const tgui::String& text, bool down)
                -> tgui::ToggleButton::Ptr { return self->create(text, down); });
        bindToggleButton["copy"] = &tgui::ToggleButton::copy;
        bindToggleButton["onToggle"] = &tgui::ToggleButton::onToggle;
    }
};