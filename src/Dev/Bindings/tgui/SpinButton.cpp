#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/SpinButton.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSpinButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SpinButton> bindSpinButton
            = tguiNamespace.new_usertype<tgui::SpinButton>("SpinButton",
                sol::call_constructor,
                sol::constructors<tgui::SpinButton(), tgui::SpinButton(const char*),
                    tgui::SpinButton(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindSpinButton["getSharedRenderer"] = sol::overload(
            static_cast<tgui::SpinButtonRenderer* (tgui::SpinButton::*)()>(
                &tgui::SpinButton::getSharedRenderer),
            static_cast<const tgui::SpinButtonRenderer* (tgui::SpinButton::*)() const>(
                &tgui::SpinButton::getSharedRenderer));
        bindSpinButton["getRenderer"] = sol::overload(
            static_cast<tgui::SpinButtonRenderer* (tgui::SpinButton::*)()>(
                &tgui::SpinButton::getRenderer),
            static_cast<const tgui::SpinButtonRenderer* (tgui::SpinButton::*)() const>(
                &tgui::SpinButton::getRenderer));
        bindSpinButton["setSize"] = sol::overload(
            static_cast<void (tgui::SpinButton::*)(const tgui::Layout2d&)>(
                &tgui::SpinButton::setSize),
            static_cast<void (tgui::SpinButton::*)(const tgui::Layout2d&)>(
                &tgui::SpinButton::setSize),
            static_cast<void (tgui::SpinButton::*)(tgui::Layout, tgui::Layout)>(
                &tgui::SpinButton::setSize));
        bindSpinButton["setMinimum"] = &tgui::SpinButton::setMinimum;
        bindSpinButton["getMinimum"] = &tgui::SpinButton::getMinimum;
        bindSpinButton["setMaximum"] = &tgui::SpinButton::setMaximum;
        bindSpinButton["getMaximum"] = &tgui::SpinButton::getMaximum;
        bindSpinButton["setValue"] = &tgui::SpinButton::setValue;
        bindSpinButton["getValue"] = &tgui::SpinButton::getValue;
        bindSpinButton["setStep"] = &tgui::SpinButton::setStep;
        bindSpinButton["getStep"] = &tgui::SpinButton::getStep;
        bindSpinButton["setVerticalScroll"] = &tgui::SpinButton::setVerticalScroll;
        bindSpinButton["getVerticalScroll"] = &tgui::SpinButton::getVerticalScroll;
        bindSpinButton["leftMousePressed"] = &tgui::SpinButton::leftMousePressed;
        bindSpinButton["leftMouseReleased"] = &tgui::SpinButton::leftMouseReleased;
        bindSpinButton["mouseMoved"] = &tgui::SpinButton::mouseMoved;
        bindSpinButton["draw"] =

            [](tgui::SpinButton* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindSpinButton["create"] = sol::overload(
            [](tgui::SpinButton* self) -> tgui::SpinButton::Ptr {
                return self->create();
            },
            [](tgui::SpinButton* self, float minimum) -> tgui::SpinButton::Ptr {
                return self->create(minimum);
            },
            [](tgui::SpinButton* self, float minimum, float maximum)
                -> tgui::SpinButton::Ptr { return self->create(minimum, maximum); });
        bindSpinButton["copy"] = &tgui::SpinButton::copy;
        bindSpinButton["onValueChange"] = &tgui::SpinButton::onValueChange;
    }
};