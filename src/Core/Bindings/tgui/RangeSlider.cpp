#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/RangeSlider.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRangeSlider(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RangeSlider> bindRangeSlider
            = tguiNamespace.new_usertype<tgui::RangeSlider>("RangeSlider", sol::call_constructor,
                sol::constructors<tgui::RangeSlider(), tgui::RangeSlider(const char*),
                    tgui::RangeSlider(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindRangeSlider["getSharedRenderer"]
            = sol::overload(static_cast<tgui::RangeSliderRenderer* (tgui::RangeSlider::*)()>(
                                &tgui::RangeSlider::getSharedRenderer),
                static_cast<const tgui::RangeSliderRenderer* (tgui::RangeSlider::*)() const>(
                    &tgui::RangeSlider::getSharedRenderer));
        bindRangeSlider["getRenderer"]
            = sol::overload(static_cast<tgui::RangeSliderRenderer* (tgui::RangeSlider::*)()>(
                                &tgui::RangeSlider::getRenderer),
                static_cast<const tgui::RangeSliderRenderer* (tgui::RangeSlider::*)() const>(
                    &tgui::RangeSlider::getRenderer));
        bindRangeSlider["setSize"]
            = sol::overload(static_cast<void (tgui::RangeSlider::*)(const tgui::Layout2d&)>(
                                &tgui::RangeSlider::setSize),
                static_cast<void (tgui::RangeSlider::*)(const tgui::Layout2d&)>(
                    &tgui::RangeSlider::setSize),
                static_cast<void (tgui::RangeSlider::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::RangeSlider::setSize));
        bindRangeSlider["getFullSize"] = &tgui::RangeSlider::getFullSize;
        bindRangeSlider["getWidgetOffset"] = &tgui::RangeSlider::getWidgetOffset;
        bindRangeSlider["setMinimum"] = &tgui::RangeSlider::setMinimum;
        bindRangeSlider["getMinimum"] = &tgui::RangeSlider::getMinimum;
        bindRangeSlider["setMaximum"] = &tgui::RangeSlider::setMaximum;
        bindRangeSlider["getMaximum"] = &tgui::RangeSlider::getMaximum;
        bindRangeSlider["setSelectionStart"] = &tgui::RangeSlider::setSelectionStart;
        bindRangeSlider["getSelectionStart"] = &tgui::RangeSlider::getSelectionStart;
        bindRangeSlider["setSelectionEnd"] = &tgui::RangeSlider::setSelectionEnd;
        bindRangeSlider["getSelectionEnd"] = &tgui::RangeSlider::getSelectionEnd;
        bindRangeSlider["setStep"] = &tgui::RangeSlider::setStep;
        bindRangeSlider["getStep"] = &tgui::RangeSlider::getStep;
        bindRangeSlider["isMouseOnWidget"] = &tgui::RangeSlider::isMouseOnWidget;
        bindRangeSlider["leftMousePressed"] = &tgui::RangeSlider::leftMousePressed;
        bindRangeSlider["leftMouseReleased"] = &tgui::RangeSlider::leftMouseReleased;
        bindRangeSlider["mouseMoved"] = &tgui::RangeSlider::mouseMoved;
        bindRangeSlider["leftMouseButtonNoLongerDown"]
            = &tgui::RangeSlider::leftMouseButtonNoLongerDown;
        bindRangeSlider["draw"] = &tgui::RangeSlider::draw;
        bindRangeSlider["create"]
            = sol::overload([]() -> tgui::RangeSlider::Ptr { return tgui::RangeSlider::create(); },
                [](float minimum) -> tgui::RangeSlider::Ptr {
                    return tgui::RangeSlider::create(minimum);
                },
                [](float minimum, float maximum) -> tgui::RangeSlider::Ptr {
                    return tgui::RangeSlider::create(minimum, maximum);
                });
        bindRangeSlider["copy"] = &tgui::RangeSlider::copy;
        bindRangeSlider["onRangeChange"] = &tgui::RangeSlider::onRangeChange;
    }
};