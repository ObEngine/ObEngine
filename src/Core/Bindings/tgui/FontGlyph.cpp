#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Font.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFontGlyph(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FontGlyph> bindFontGlyph = tguiNamespace.new_usertype<tgui::FontGlyph>(
            "FontGlyph", sol::call_constructor, sol::default_constructor);
        bindFontGlyph["advance"] = &tgui::FontGlyph::advance;
        bindFontGlyph["bounds"] = &tgui::FontGlyph::bounds;
    }
};