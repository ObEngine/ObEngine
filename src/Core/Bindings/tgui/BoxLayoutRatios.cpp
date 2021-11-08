#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/BoxLayoutRatios.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBoxLayoutRatios(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayoutRatios> bindBoxLayoutRatios
            = tguiNamespace.new_usertype<tgui::BoxLayoutRatios>("BoxLayoutRatios",
                sol::base_classes,
                sol::bases<tgui::BoxLayout, tgui::Group, tgui::Container, tgui::Widget>());
        bindBoxLayoutRatios["add"] = sol::overload(
            [](tgui::BoxLayoutRatios* self, const tgui::Widget::Ptr& widget) -> void {
                return self->add(widget);
            },
            [](tgui::BoxLayoutRatios* self, const tgui::Widget::Ptr& widget,
                const tgui::String& widgetName) -> void { return self->add(widget, widgetName); },
            [](tgui::BoxLayoutRatios* self, const tgui::Widget::Ptr& widget, float ratio) -> void {
                return self->add(widget, ratio);
            },
            [](tgui::BoxLayoutRatios* self, const tgui::Widget::Ptr& widget, float ratio,
                const tgui::String& widgetName) -> void {
                return self->add(widget, ratio, widgetName);
            });
        bindBoxLayoutRatios["insert"] = sol::overload(
            [](tgui::BoxLayoutRatios* self, std::size_t index,
                const tgui::Widget::Ptr& widget) -> void { return self->insert(index, widget); },
            [](tgui::BoxLayoutRatios* self, std::size_t index, const tgui::Widget::Ptr& widget,
                const tgui::String& widgetName) -> void {
                return self->insert(index, widget, widgetName);
            },
            [](tgui::BoxLayoutRatios* self, std::size_t index, const tgui::Widget::Ptr& widget,
                float ratio) -> void { return self->insert(index, widget, ratio); },
            [](tgui::BoxLayoutRatios* self, std::size_t index, const tgui::Widget::Ptr& widget,
                float ratio, const tgui::String& widgetName) -> void {
                return self->insert(index, widget, ratio, widgetName);
            });
        bindBoxLayoutRatios["remove"]
            = sol::overload(static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t)>(
                                &tgui::BoxLayoutRatios::remove),
                static_cast<bool (tgui::BoxLayoutRatios::*)(const tgui::Widget::Ptr&)>(
                    &tgui::BoxLayoutRatios::remove),
                static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t)>(
                    &tgui::BoxLayoutRatios::remove));
        bindBoxLayoutRatios["removeAllWidgets"] = &tgui::BoxLayoutRatios::removeAllWidgets;
        bindBoxLayoutRatios["addSpace"] = &tgui::BoxLayoutRatios::addSpace;
        bindBoxLayoutRatios["insertSpace"] = &tgui::BoxLayoutRatios::insertSpace;
        bindBoxLayoutRatios["setRatio"]
            = sol::overload(static_cast<bool (tgui::BoxLayoutRatios::*)(tgui::Widget::Ptr, float)>(
                                &tgui::BoxLayoutRatios::setRatio),
                static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t, float)>(
                    &tgui::BoxLayoutRatios::setRatio));
        bindBoxLayoutRatios["getRatio"]
            = sol::overload(static_cast<float (tgui::BoxLayoutRatios::*)(tgui::Widget::Ptr) const>(
                                &tgui::BoxLayoutRatios::getRatio),
                static_cast<float (tgui::BoxLayoutRatios::*)(std::size_t) const>(
                    &tgui::BoxLayoutRatios::getRatio));
    }
};