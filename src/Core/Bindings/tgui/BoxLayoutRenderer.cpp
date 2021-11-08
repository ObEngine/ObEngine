#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/BoxLayoutRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBoxLayoutRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayoutRenderer> bindBoxLayoutRenderer
            = tguiNamespace.new_usertype<tgui::BoxLayoutRenderer>("BoxLayoutRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::GroupRenderer, tgui::WidgetRenderer>());
        bindBoxLayoutRenderer["setSpaceBetweenWidgets"]
            = &tgui::BoxLayoutRenderer::setSpaceBetweenWidgets;
        bindBoxLayoutRenderer["getSpaceBetweenWidgets"]
            = &tgui::BoxLayoutRenderer::getSpaceBetweenWidgets;
    }
};