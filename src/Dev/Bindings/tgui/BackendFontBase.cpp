#include <Bindings/tgui/tgui.hpp>

#include <TGUI/BackendFont.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBackendFontBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendFontBase> bindBackendFontBase
            = tguiNamespace.new_usertype<tgui::BackendFontBase>("BackendFontBase");
        bindBackendFontBase["loadFromFile"] = &tgui::BackendFontBase::loadFromFile;
        bindBackendFontBase["loadFromMemory"] = &tgui::BackendFontBase::loadFromMemory;
        bindBackendFontBase["getGlyph"] = sol::overload(
            [](tgui::BackendFontBase* self, char32_t codePoint,
                unsigned int characterSize, bool bold) -> tgui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold);
            },
            [](tgui::BackendFontBase* self, char32_t codePoint,
                unsigned int characterSize, bool bold,
                float outlineThickness) -> tgui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold, outlineThickness);
            });
        bindBackendFontBase["getKerning"] = &tgui::BackendFontBase::getKerning;
        bindBackendFontBase["getLineSpacing"] = &tgui::BackendFontBase::getLineSpacing;
    }
};