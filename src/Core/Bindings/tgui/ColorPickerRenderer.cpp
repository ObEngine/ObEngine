#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/ColorPickerRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassColorPickerRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ColorPickerRenderer> bindColorPickerRenderer
            = tguiNamespace.new_usertype<tgui::ColorPickerRenderer>("ColorPickerRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::ChildWindowRenderer, tgui::WidgetRenderer>());
        bindColorPickerRenderer["setButton"] = &tgui::ColorPickerRenderer::setButton;
        bindColorPickerRenderer["getButton"] = &tgui::ColorPickerRenderer::getButton;
        bindColorPickerRenderer["setLabel"] = &tgui::ColorPickerRenderer::setLabel;
        bindColorPickerRenderer["getLabel"] = &tgui::ColorPickerRenderer::getLabel;
        bindColorPickerRenderer["setSlider"] = &tgui::ColorPickerRenderer::setSlider;
        bindColorPickerRenderer["getSlider"] = &tgui::ColorPickerRenderer::getSlider;
    }
};