#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/WidgetRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassWidgetRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::WidgetRenderer> bindWidgetRenderer
            = tguiNamespace.new_usertype<tgui::WidgetRenderer>("WidgetRenderer",
                sol::call_constructor,
                sol::constructors<tgui::WidgetRenderer(),
                    tgui::WidgetRenderer(const std::shared_ptr<tgui::RendererData>&)>());
        bindWidgetRenderer["setOpacity"] = &tgui::WidgetRenderer::setOpacity;
        bindWidgetRenderer["getOpacity"] = &tgui::WidgetRenderer::getOpacity;
        bindWidgetRenderer["setOpacityDisabled"]
            = &tgui::WidgetRenderer::setOpacityDisabled;
        bindWidgetRenderer["getOpacityDisabled"]
            = &tgui::WidgetRenderer::getOpacityDisabled;
        bindWidgetRenderer["setFont"] = &tgui::WidgetRenderer::setFont;
        bindWidgetRenderer["getFont"] = &tgui::WidgetRenderer::getFont;
        bindWidgetRenderer["setTransparentTexture"]
            = &tgui::WidgetRenderer::setTransparentTexture;
        bindWidgetRenderer["getTransparentTexture"]
            = &tgui::WidgetRenderer::getTransparentTexture;
        bindWidgetRenderer["setProperty"] =

            [](tgui::WidgetRenderer* self, const tgui::String& property,
                tgui::ObjectConverter value) {
                self->setProperty(property, std::move(value));
            }

        ;
        bindWidgetRenderer["getProperty"] = &tgui::WidgetRenderer::getProperty;
        bindWidgetRenderer["getPropertyValuePairs"]
            = &tgui::WidgetRenderer::getPropertyValuePairs;
        bindWidgetRenderer["subscribe"] = &tgui::WidgetRenderer::subscribe;
        bindWidgetRenderer["unsubscribe"] = &tgui::WidgetRenderer::unsubscribe;
        bindWidgetRenderer["setData"] = &tgui::WidgetRenderer::setData;
        bindWidgetRenderer["getData"] = &tgui::WidgetRenderer::getData;
        bindWidgetRenderer["clone"] = &tgui::WidgetRenderer::clone;
    }
};