#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/GroupRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassGroupRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::GroupRenderer> bindGroupRenderer
            = tguiNamespace.new_usertype<tgui::GroupRenderer>("GroupRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindGroupRenderer["setPadding"] = &tgui::GroupRenderer::setPadding;
        bindGroupRenderer["getPadding"] = &tgui::GroupRenderer::getPadding;
    }
};