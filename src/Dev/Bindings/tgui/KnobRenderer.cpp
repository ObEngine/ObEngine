#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/KnobRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassKnobRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::KnobRenderer> bindKnobRenderer
            = tguiNamespace.new_usertype<tgui::KnobRenderer>("KnobRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindKnobRenderer["setBorders"] = &tgui::KnobRenderer::setBorders;
        bindKnobRenderer["getBorders"] = &tgui::KnobRenderer::getBorders;
        bindKnobRenderer["setBackgroundColor"] = &tgui::KnobRenderer::setBackgroundColor;
        bindKnobRenderer["getBackgroundColor"] = &tgui::KnobRenderer::getBackgroundColor;
        bindKnobRenderer["setThumbColor"] = &tgui::KnobRenderer::setThumbColor;
        bindKnobRenderer["getThumbColor"] = &tgui::KnobRenderer::getThumbColor;
        bindKnobRenderer["setBorderColor"] = &tgui::KnobRenderer::setBorderColor;
        bindKnobRenderer["getBorderColor"] = &tgui::KnobRenderer::getBorderColor;
        bindKnobRenderer["setTextureBackground"]
            = &tgui::KnobRenderer::setTextureBackground;
        bindKnobRenderer["getTextureBackground"]
            = &tgui::KnobRenderer::getTextureBackground;
        bindKnobRenderer["setTextureForeground"]
            = &tgui::KnobRenderer::setTextureForeground;
        bindKnobRenderer["getTextureForeground"]
            = &tgui::KnobRenderer::getTextureForeground;
        bindKnobRenderer["setImageRotation"] = &tgui::KnobRenderer::setImageRotation;
        bindKnobRenderer["getImageRotation"] = &tgui::KnobRenderer::getImageRotation;
    }
};