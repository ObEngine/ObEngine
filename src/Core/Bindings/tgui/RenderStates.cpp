#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/RenderStates.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRenderStates(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RenderStates> bindRenderStates
            = tguiNamespace.new_usertype<tgui::RenderStates>(
                "RenderStates", sol::call_constructor, sol::default_constructor);
        bindRenderStates["transform"] = &tgui::RenderStates::transform;
    }
};