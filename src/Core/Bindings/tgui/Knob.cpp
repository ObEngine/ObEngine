#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Knob.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassKnob(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Knob> bindKnob
            = tguiNamespace.new_usertype<tgui::Knob>("Knob", sol::call_constructor,
                sol::constructors<tgui::Knob(), tgui::Knob(const char*),
                    tgui::Knob(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindKnob["getSharedRenderer"] = sol::overload(
            static_cast<tgui::KnobRenderer* (tgui::Knob::*)()>(&tgui::Knob::getSharedRenderer),
            static_cast<const tgui::KnobRenderer* (tgui::Knob::*)() const>(
                &tgui::Knob::getSharedRenderer));
        bindKnob["getRenderer"] = sol::overload(
            static_cast<tgui::KnobRenderer* (tgui::Knob::*)()>(&tgui::Knob::getRenderer),
            static_cast<const tgui::KnobRenderer* (tgui::Knob::*)() const>(
                &tgui::Knob::getRenderer));
        bindKnob["setSize"] = sol::overload(
            static_cast<void (tgui::Knob::*)(const tgui::Layout2d&)>(&tgui::Knob::setSize),
            static_cast<void (tgui::Knob::*)(const tgui::Layout2d&)>(&tgui::Knob::setSize),
            static_cast<void (tgui::Knob::*)(tgui::Layout, tgui::Layout)>(&tgui::Knob::setSize));
        bindKnob["setStartRotation"] = &tgui::Knob::setStartRotation;
        bindKnob["getStartRotation"] = &tgui::Knob::getStartRotation;
        bindKnob["setEndRotation"] = &tgui::Knob::setEndRotation;
        bindKnob["getEndRotation"] = &tgui::Knob::getEndRotation;
        bindKnob["setMinimum"] = &tgui::Knob::setMinimum;
        bindKnob["getMinimum"] = &tgui::Knob::getMinimum;
        bindKnob["setMaximum"] = &tgui::Knob::setMaximum;
        bindKnob["getMaximum"] = &tgui::Knob::getMaximum;
        bindKnob["setValue"] = &tgui::Knob::setValue;
        bindKnob["getValue"] = &tgui::Knob::getValue;
        bindKnob["setClockwiseTurning"] = &tgui::Knob::setClockwiseTurning;
        bindKnob["getClockwiseTurning"] = &tgui::Knob::getClockwiseTurning;
        bindKnob["isMouseOnWidget"] = &tgui::Knob::isMouseOnWidget;
        bindKnob["leftMousePressed"] = &tgui::Knob::leftMousePressed;
        bindKnob["mouseMoved"] = &tgui::Knob::mouseMoved;
        bindKnob["draw"] = &tgui::Knob::draw;
        bindKnob["create"] = &tgui::Knob::create;
        bindKnob["copy"] = &tgui::Knob::copy;
        bindKnob["onValueChange"] = &tgui::Knob::onValueChange;
    }
};