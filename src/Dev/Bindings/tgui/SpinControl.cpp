#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/SpinControl.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSpinControl(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SpinControl> bindSpinControl
            = tguiNamespace.new_usertype<tgui::SpinControl>("SpinControl",
                sol::call_constructor,
                sol::constructors<tgui::SpinControl(), tgui::SpinControl(const char*),
                    tgui::SpinControl(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::SubwidgetContainer, tgui::Widget>());
        bindSpinControl["getSpinButtonSharedRenderer"] = sol::overload(
            static_cast<tgui::SpinButtonRenderer* (tgui::SpinControl::*)()>(
                &tgui::SpinControl::getSpinButtonSharedRenderer),
            static_cast<const tgui::SpinButtonRenderer* (tgui::SpinControl::*)() const>(
                &tgui::SpinControl::getSpinButtonSharedRenderer));
        bindSpinControl["getSpinButtonRenderer"] = sol::overload(
            static_cast<tgui::SpinButtonRenderer* (tgui::SpinControl::*)()>(
                &tgui::SpinControl::getSpinButtonRenderer),
            static_cast<const tgui::SpinButtonRenderer* (tgui::SpinControl::*)() const>(
                &tgui::SpinControl::getSpinButtonRenderer));
        bindSpinControl["getSpinTextSharedRenderer"]
            = sol::overload(static_cast<tgui::EditBoxRenderer* (tgui::SpinControl::*)()>(
                                &tgui::SpinControl::getSpinTextSharedRenderer),
                static_cast<const tgui::EditBoxRenderer* (tgui::SpinControl::*)() const>(
                    &tgui::SpinControl::getSpinTextSharedRenderer));
        bindSpinControl["getSpinTextRenderer"]
            = sol::overload(static_cast<tgui::EditBoxRenderer* (tgui::SpinControl::*)()>(
                                &tgui::SpinControl::getSpinTextRenderer),
                static_cast<const tgui::EditBoxRenderer* (tgui::SpinControl::*)() const>(
                    &tgui::SpinControl::getSpinTextRenderer));
        bindSpinControl["setSize"] = sol::overload(
            static_cast<void (tgui::SpinControl::*)(const tgui::Layout2d&)>(
                &tgui::SpinControl::setSize),
            static_cast<void (tgui::SpinControl::*)(const tgui::Layout2d&)>(
                &tgui::SpinControl::setSize),
            static_cast<void (tgui::SpinControl::*)(const tgui::Layout2d&)>(
                &tgui::SpinControl::setSize),
            static_cast<void (tgui::SpinControl::*)(tgui::Layout, tgui::Layout)>(
                &tgui::SpinControl::setSize));
        bindSpinControl["setMinimum"] = &tgui::SpinControl::setMinimum;
        bindSpinControl["getMinimum"] = &tgui::SpinControl::getMinimum;
        bindSpinControl["setMaximum"] = &tgui::SpinControl::setMaximum;
        bindSpinControl["getMaximum"] = &tgui::SpinControl::getMaximum;
        bindSpinControl["setValue"] = &tgui::SpinControl::setValue;
        bindSpinControl["getValue"] = &tgui::SpinControl::getValue;
        bindSpinControl["setStep"] = &tgui::SpinControl::setStep;
        bindSpinControl["getStep"] = &tgui::SpinControl::getStep;
        bindSpinControl["setDecimalPlaces"] = &tgui::SpinControl::setDecimalPlaces;
        bindSpinControl["getDecimalPlaces"] = &tgui::SpinControl::getDecimalPlaces;
        bindSpinControl["create"] = sol::overload(
            [](tgui::SpinControl* self) -> tgui::SpinControl::Ptr {
                return self->create();
            },
            [](tgui::SpinControl* self, float min) -> tgui::SpinControl::Ptr {
                return self->create(min);
            },
            [](tgui::SpinControl* self, float min, float max) -> tgui::SpinControl::Ptr {
                return self->create(min, max);
            },
            [](tgui::SpinControl* self, float min, float max, float value)
                -> tgui::SpinControl::Ptr { return self->create(min, max, value); },
            [](tgui::SpinControl* self, float min, float max, float value,
                unsigned int decimal) -> tgui::SpinControl::Ptr {
                return self->create(min, max, value, decimal);
            },
            [](tgui::SpinControl* self, float min, float max, float value,
                unsigned int decimal, float step) -> tgui::SpinControl::Ptr {
                return self->create(min, max, value, decimal, step);
            });
        bindSpinControl["copy"] = &tgui::SpinControl::copy;
        bindSpinControl["onValueChange"] = &tgui::SpinControl::onValueChange;
    }
};