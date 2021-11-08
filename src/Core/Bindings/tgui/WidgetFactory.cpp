#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Loading/WidgetFactory.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassWidgetFactory(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::WidgetFactory> bindWidgetFactory
            = tguiNamespace.new_usertype<tgui::WidgetFactory>(
                "WidgetFactory", sol::call_constructor, sol::default_constructor);
        bindWidgetFactory["setConstructFunction"] = &tgui::WidgetFactory::setConstructFunction;
        bindWidgetFactory["getConstructFunction"] = &tgui::WidgetFactory::getConstructFunction;
    }
};