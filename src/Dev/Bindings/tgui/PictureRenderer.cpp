#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/PictureRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassPictureRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::PictureRenderer> bindPictureRenderer
            = tguiNamespace.new_usertype<tgui::PictureRenderer>("PictureRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindPictureRenderer["setTexture"] = &tgui::PictureRenderer::setTexture;
        bindPictureRenderer["getTexture"] = &tgui::PictureRenderer::getTexture;
    }
};