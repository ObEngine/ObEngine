#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Text.hpp>
#include <TGUI/BackendText.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassText(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Text> bindText
            = tguiNamespace.new_usertype<tgui::Text>("Text", sol::call_constructor,
                sol::constructors<tgui::Text(), tgui::Text(const tgui::Text&)>());
        bindText["operator="]
            = sol::overload(static_cast<tgui::Text& (tgui::Text::*)(const tgui::Text&)>(
                                &tgui::Text::operator=),
                [](tgui::Text* self, tgui::Text p0) { self->operator=(std::move(p0)); });
        bindText["setPosition"] = &tgui::Text::setPosition;
        bindText["getPosition"] = &tgui::Text::getPosition;
        bindText["getSize"] = &tgui::Text::getSize;
        bindText["setString"] = &tgui::Text::setString;
        bindText["getString"] = &tgui::Text::getString;
        bindText["setCharacterSize"] = &tgui::Text::setCharacterSize;
        bindText["getCharacterSize"] = &tgui::Text::getCharacterSize;
        bindText["setColor"] = &tgui::Text::setColor;
        bindText["getColor"] = &tgui::Text::getColor;
        bindText["setOpacity"] = &tgui::Text::setOpacity;
        bindText["getOpacity"] = &tgui::Text::getOpacity;
        bindText["setFont"] = &tgui::Text::setFont;
        bindText["getFont"] = &tgui::Text::getFont;
        bindText["setStyle"] = &tgui::Text::setStyle;
        bindText["getStyle"] = &tgui::Text::getStyle;
        bindText["setOutlineColor"] = &tgui::Text::setOutlineColor;
        bindText["getOutlineColor"] = &tgui::Text::getOutlineColor;
        bindText["setOutlineThickness"] = &tgui::Text::setOutlineThickness;
        bindText["getOutlineThickness"] = &tgui::Text::getOutlineThickness;
        bindText["findCharacterPos"] = &tgui::Text::findCharacterPos;
        bindText["getExtraHorizontalPadding"]
            = sol::overload(static_cast<float (tgui::Text::*)() const>(
                                &tgui::Text::getExtraHorizontalPadding),
                static_cast<float (*)(tgui::Font, unsigned int, tgui::TextStyles)>(
                    &tgui::Text::getExtraHorizontalPadding));
        bindText["getExtraHorizontalOffset"]
            = sol::overload(static_cast<float (tgui::Text::*)() const>(
                                &tgui::Text::getExtraHorizontalOffset),
                static_cast<float (*)(tgui::Font, unsigned int, tgui::TextStyles)>(
                    &tgui::Text::getExtraHorizontalOffset));
        bindText["getLineHeight"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getLineHeight),
            static_cast<float (*)(tgui::Font, unsigned int, tgui::TextStyles)>(
                &tgui::Text::getLineHeight));
        bindText["getLineWidth"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getLineWidth),
            static_cast<float (*)(const tgui::String&, tgui::Font, unsigned int,
                tgui::TextStyles)>(&tgui::Text::getLineWidth));
        bindText["getBackendText"] = &tgui::Text::getBackendText;
        bindText["getExtraVerticalPadding"] = &tgui::Text::getExtraVerticalPadding;
        bindText["findBestTextSize"] = sol::overload(
            [](tgui::Text* self, tgui::Font font, float height) -> unsigned int {
                return self->findBestTextSize(font, height);
            },
            [](tgui::Text* self, tgui::Font font, float height, int fit) -> unsigned int {
                return self->findBestTextSize(font, height, fit);
            });
        bindText["calculateExtraVerticalSpace"] = sol::overload(
            [](tgui::Text* self, tgui::Font font, unsigned int characterSize) -> float {
                return self->calculateExtraVerticalSpace(font, characterSize);
            },
            [](tgui::Text* self, tgui::Font font, unsigned int characterSize,
                tgui::TextStyles style) -> float {
                return self->calculateExtraVerticalSpace(font, characterSize, style);
            });
        bindText["wordWrap"] = sol::overload(
            [](tgui::Text* self, float maxWidth, const tgui::String& text,
                tgui::Font font, unsigned int textSize, bool bold) -> tgui::String {
                return self->wordWrap(maxWidth, text, font, textSize, bold);
            },
            [](tgui::Text* self, float maxWidth, const tgui::String& text,
                tgui::Font font, unsigned int textSize, bool bold,
                bool dropLeadingSpace) -> tgui::String {
                return self->wordWrap(
                    maxWidth, text, font, textSize, bold, dropLeadingSpace);
            });
    }
};