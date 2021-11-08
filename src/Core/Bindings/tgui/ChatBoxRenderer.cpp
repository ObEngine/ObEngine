#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/ChatBoxRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassChatBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChatBoxRenderer> bindChatBoxRenderer
            = tguiNamespace.new_usertype<tgui::ChatBoxRenderer>("ChatBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindChatBoxRenderer["setBorders"] = &tgui::ChatBoxRenderer::setBorders;
        bindChatBoxRenderer["getBorders"] = &tgui::ChatBoxRenderer::getBorders;
        bindChatBoxRenderer["setPadding"] = &tgui::ChatBoxRenderer::setPadding;
        bindChatBoxRenderer["getPadding"] = &tgui::ChatBoxRenderer::getPadding;
        bindChatBoxRenderer["setBackgroundColor"] = &tgui::ChatBoxRenderer::setBackgroundColor;
        bindChatBoxRenderer["getBackgroundColor"] = &tgui::ChatBoxRenderer::getBackgroundColor;
        bindChatBoxRenderer["setBorderColor"] = &tgui::ChatBoxRenderer::setBorderColor;
        bindChatBoxRenderer["getBorderColor"] = &tgui::ChatBoxRenderer::getBorderColor;
        bindChatBoxRenderer["setTextureBackground"] = &tgui::ChatBoxRenderer::setTextureBackground;
        bindChatBoxRenderer["getTextureBackground"] = &tgui::ChatBoxRenderer::getTextureBackground;
        bindChatBoxRenderer["setScrollbar"] = &tgui::ChatBoxRenderer::setScrollbar;
        bindChatBoxRenderer["getScrollbar"] = &tgui::ChatBoxRenderer::getScrollbar;
        bindChatBoxRenderer["setScrollbarWidth"] = &tgui::ChatBoxRenderer::setScrollbarWidth;
        bindChatBoxRenderer["getScrollbarWidth"] = &tgui::ChatBoxRenderer::getScrollbarWidth;
    }
};