#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/CheckBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassCheckBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::CheckBox> bindCheckBox
            = tguiNamespace.new_usertype<tgui::CheckBox>("CheckBox",
                sol::call_constructor,
                sol::constructors<tgui::CheckBox(), tgui::CheckBox(const char*),
                    tgui::CheckBox(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::RadioButton, tgui::ClickableWidget, tgui::Widget>());
        bindCheckBox["getSharedRenderer"]
            = sol::overload(static_cast<tgui::CheckBoxRenderer* (tgui::CheckBox::*)()>(
                                &tgui::CheckBox::getSharedRenderer),
                static_cast<const tgui::CheckBoxRenderer* (tgui::CheckBox::*)() const>(
                    &tgui::CheckBox::getSharedRenderer));
        bindCheckBox["getRenderer"]
            = sol::overload(static_cast<tgui::CheckBoxRenderer* (tgui::CheckBox::*)()>(
                                &tgui::CheckBox::getRenderer),
                static_cast<const tgui::CheckBoxRenderer* (tgui::CheckBox::*)() const>(
                    &tgui::CheckBox::getRenderer));
        bindCheckBox["getFullSize"] = &tgui::CheckBox::getFullSize;
        bindCheckBox["getWidgetOffset"] = &tgui::CheckBox::getWidgetOffset;
        bindCheckBox["setChecked"] = &tgui::CheckBox::setChecked;
        bindCheckBox["leftMouseReleased"] = &tgui::CheckBox::leftMouseReleased;
        bindCheckBox["keyPressed"] = &tgui::CheckBox::keyPressed;
        bindCheckBox["draw"] =

            [](tgui::CheckBox* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindCheckBox["create"] = sol::overload(
            [](tgui::CheckBox* self) -> tgui::CheckBox::Ptr { return self->create(); },
            [](tgui::CheckBox* self, tgui::String text) -> tgui::CheckBox::Ptr {
                return self->create(text);
            });
        bindCheckBox["copy"] = &tgui::CheckBox::copy;
    }
};