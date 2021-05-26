#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Font.hpp>
#include <TGUI/BackendFont.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFont(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Font> bindFont
            = tguiNamespace.new_usertype<tgui::Font>("Font", sol::call_constructor,
                sol::constructors<tgui::Font(), tgui::Font(std::nullptr_t),
                    tgui::Font(const tgui::String&), tgui::Font(const char*),
                    tgui::Font(const void*, std::size_t),
                    tgui::Font(
                        std::shared_ptr<tgui::BackendFontBase>, const tgui::String&)>());
        bindFont["getId"] = &tgui::Font::getId;
        bindFont[sol::meta_function::equal_to]
            = sol::overload(static_cast<bool (tgui::Font::*)(std::nullptr_t) const>(
                                &tgui::Font::operator==),
                static_cast<bool (tgui::Font::*)(const tgui::Font&) const>(
                    &tgui::Font::operator==));
        bindFont["getGlyph"] = sol::overload(
            [](tgui::Font* self, char32_t codePoint, unsigned int characterSize,
                bool bold) -> tgui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold);
            },
            [](tgui::Font* self, char32_t codePoint, unsigned int characterSize,
                bool bold, float outlineThickness) -> tgui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold, outlineThickness);
            });
        bindFont["getKerning"] = &tgui::Font::getKerning;
        bindFont["getLineSpacing"] = &tgui::Font::getLineSpacing;
        bindFont["getBackendFont"] = &tgui::Font::getBackendFont;
        bindFont["setGlobalFont"] = &tgui::Font::setGlobalFont;
        bindFont["getGlobalFont"] = &tgui::Font::getGlobalFont;
    }
};