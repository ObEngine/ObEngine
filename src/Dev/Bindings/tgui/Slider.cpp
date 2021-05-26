#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/Slider.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSlider(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Slider> bindSlider
            = tguiNamespace.new_usertype<tgui::Slider>("Slider", sol::call_constructor,
                sol::constructors<tgui::Slider(), tgui::Slider(const char*),
                    tgui::Slider(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindSlider["getSharedRenderer"]
            = sol::overload(static_cast<tgui::SliderRenderer* (tgui::Slider::*)()>(
                                &tgui::Slider::getSharedRenderer),
                static_cast<const tgui::SliderRenderer* (tgui::Slider::*)() const>(
                    &tgui::Slider::getSharedRenderer));
        bindSlider["getRenderer"]
            = sol::overload(static_cast<tgui::SliderRenderer* (tgui::Slider::*)()>(
                                &tgui::Slider::getRenderer),
                static_cast<const tgui::SliderRenderer* (tgui::Slider::*)() const>(
                    &tgui::Slider::getRenderer));
        bindSlider["setSize"]
            = sol::overload(static_cast<void (tgui::Slider::*)(const tgui::Layout2d&)>(
                                &tgui::Slider::setSize),
                static_cast<void (tgui::Slider::*)(const tgui::Layout2d&)>(
                    &tgui::Slider::setSize),
                static_cast<void (tgui::Slider::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::Slider::setSize));
        bindSlider["getFullSize"] = &tgui::Slider::getFullSize;
        bindSlider["getWidgetOffset"] = &tgui::Slider::getWidgetOffset;
        bindSlider["setMinimum"] = &tgui::Slider::setMinimum;
        bindSlider["getMinimum"] = &tgui::Slider::getMinimum;
        bindSlider["setMaximum"] = &tgui::Slider::setMaximum;
        bindSlider["getMaximum"] = &tgui::Slider::getMaximum;
        bindSlider["setValue"] = &tgui::Slider::setValue;
        bindSlider["getValue"] = &tgui::Slider::getValue;
        bindSlider["setStep"] = &tgui::Slider::setStep;
        bindSlider["getStep"] = &tgui::Slider::getStep;
        bindSlider["setVerticalScroll"] = &tgui::Slider::setVerticalScroll;
        bindSlider["getVerticalScroll"] = &tgui::Slider::getVerticalScroll;
        bindSlider["setInvertedDirection"] = &tgui::Slider::setInvertedDirection;
        bindSlider["getInvertedDirection"] = &tgui::Slider::getInvertedDirection;
        bindSlider["setChangeValueOnScroll"] = &tgui::Slider::setChangeValueOnScroll;
        bindSlider["getChangeValueOnScroll"] = &tgui::Slider::getChangeValueOnScroll;
        bindSlider["isMouseOnWidget"] = &tgui::Slider::isMouseOnWidget;
        bindSlider["leftMousePressed"] = &tgui::Slider::leftMousePressed;
        bindSlider["leftMouseReleased"] = &tgui::Slider::leftMouseReleased;
        bindSlider["mouseMoved"] = &tgui::Slider::mouseMoved;
        bindSlider["mouseWheelScrolled"] = &tgui::Slider::mouseWheelScrolled;
        bindSlider["leftMouseButtonNoLongerDown"]
            = &tgui::Slider::leftMouseButtonNoLongerDown;
        bindSlider["draw"] =

            [](tgui::Slider* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindSlider["create"] = sol::overload(
            [](tgui::Slider* self) -> tgui::Slider::Ptr { return self->create(); },
            [](tgui::Slider* self, float minimum) -> tgui::Slider::Ptr {
                return self->create(minimum);
            },
            [](tgui::Slider* self, float minimum, float maximum) -> tgui::Slider::Ptr {
                return self->create(minimum, maximum);
            });
        bindSlider["copy"] = &tgui::Slider::copy;
        bindSlider["onValueChange"] = &tgui::Slider::onValueChange;
    }
};