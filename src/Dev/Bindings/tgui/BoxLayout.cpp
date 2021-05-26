#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/BoxLayout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBoxLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayout> bindBoxLayout
            = tguiNamespace.new_usertype<tgui::BoxLayout>("BoxLayout", sol::base_classes,
                sol::bases<tgui::Group, tgui::Container, tgui::Widget>());
        bindBoxLayout["getSharedRenderer"]
            = sol::overload(static_cast<tgui::BoxLayoutRenderer* (tgui::BoxLayout::*)()>(
                                &tgui::BoxLayout::getSharedRenderer),
                static_cast<const tgui::BoxLayoutRenderer* (tgui::BoxLayout::*)() const>(
                    &tgui::BoxLayout::getSharedRenderer));
        bindBoxLayout["getRenderer"]
            = sol::overload(static_cast<tgui::BoxLayoutRenderer* (tgui::BoxLayout::*)()>(
                                &tgui::BoxLayout::getRenderer),
                static_cast<const tgui::BoxLayoutRenderer* (tgui::BoxLayout::*)() const>(
                    &tgui::BoxLayout::getRenderer));
        bindBoxLayout["setSize"]
            = sol::overload(static_cast<void (tgui::BoxLayout::*)(const tgui::Layout2d&)>(
                                &tgui::BoxLayout::setSize),
                static_cast<void (tgui::BoxLayout::*)(const tgui::Layout2d&)>(
                    &tgui::BoxLayout::setSize),
                static_cast<void (tgui::BoxLayout::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::BoxLayout::setSize));
        bindBoxLayout["add"] = sol::overload(
            [](tgui::BoxLayout* self, const tgui::Widget::Ptr& widget) -> void {
                return self->add(widget);
            },
            [](tgui::BoxLayout* self, const tgui::Widget::Ptr& widget,
                const tgui::String& widgetName) -> void {
                return self->add(widget, widgetName);
            });
        bindBoxLayout["insert"] = sol::overload(
            [](tgui::BoxLayout* self, std::size_t index, const tgui::Widget::Ptr& widget)
                -> void { return self->insert(index, widget); },
            [](tgui::BoxLayout* self, std::size_t index, const tgui::Widget::Ptr& widget,
                const tgui::String& widgetName) -> void {
                return self->insert(index, widget, widgetName);
            });
        bindBoxLayout["remove"] = sol::overload(
            static_cast<bool (tgui::BoxLayout::*)(const tgui::Widget::Ptr&)>(
                &tgui::BoxLayout::remove),
            static_cast<bool (tgui::BoxLayout::*)(std::size_t)>(
                &tgui::BoxLayout::remove));
        bindBoxLayout["get"] = static_cast<tgui::Widget::Ptr (tgui::BoxLayout::*)(std::size_t) const>(
                &tgui::BoxLayout::get);
    }
};