#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Text.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassText(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Text> bindText
            = tguiNamespace.new_usertype<tgui::Text>("Text", sol::call_constructor,
                sol::constructors<tgui::Text(), tgui::Text(const tgui::Text&)>());
        bindText["operator="] = sol::overload(
            static_cast<tgui::Text& (tgui::Text::*)(const tgui::Text&)>(&tgui::Text::operator=),
            static_cast<tgui::Text& (tgui::Text::*)(tgui::Text &&)>(&tgui::Text::operator=));
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
        bindText["getExtraHorizontalPadding"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getExtraHorizontalPadding),
            [](tgui::Font font, unsigned int characterSize) -> float {
                return tgui::Text::getExtraHorizontalPadding(font, characterSize);
            },
            [](tgui::Font font, unsigned int characterSize, tgui::TextStyles textStyle) -> float {
                return tgui::Text::getExtraHorizontalPadding(font, characterSize, textStyle);
            });
        bindText["getExtraHorizontalOffset"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getExtraHorizontalOffset),
            [](tgui::Font font, unsigned int characterSize) -> float {
                return tgui::Text::getExtraHorizontalOffset(font, characterSize);
            },
            [](tgui::Font font, unsigned int characterSize, tgui::TextStyles textStyle) -> float {
                return tgui::Text::getExtraHorizontalOffset(font, characterSize, textStyle);
            });
        bindText["getLineHeight"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getLineHeight),
            [](tgui::Font font, unsigned int characterSize) -> float {
                return tgui::Text::getLineHeight(font, characterSize);
            },
            [](tgui::Font font, unsigned int characterSize, tgui::TextStyles textStyle) -> float {
                return tgui::Text::getLineHeight(font, characterSize, textStyle);
            });
        bindText["getLineWidth"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getLineWidth),
            [](const tgui::String& text, tgui::Font font, unsigned int characterSize) -> float {
                return tgui::Text::getLineWidth(text, font, characterSize);
            },
            [](const tgui::String& text, tgui::Font font, unsigned int characterSize,
                tgui::TextStyles textStyle) -> float {
                return tgui::Text::getLineWidth(text, font, characterSize, textStyle);
            });
        bindText["getBackendText"] = &tgui::Text::getBackendText;
        bindText["getExtraVerticalPadding"] = &tgui::Text::getExtraVerticalPadding;
        bindText["findBestTextSize"] = sol::overload(
            [](tgui::Font font, float height) -> unsigned int {
                return tgui::Text::findBestTextSize(font, height);
            },
            [](tgui::Font font, float height, int fit) -> unsigned int {
                return tgui::Text::findBestTextSize(font, height, fit);
            });
        bindText["calculateExtraVerticalSpace"] = sol::overload(
            [](tgui::Font font, unsigned int characterSize) -> float {
                return tgui::Text::calculateExtraVerticalSpace(font, characterSize);
            },
            [](tgui::Font font, unsigned int characterSize, tgui::TextStyles style) -> float {
                return tgui::Text::calculateExtraVerticalSpace(font, characterSize, style);
            });
        bindText["wordWrap"] = sol::overload(
            [](float maxWidth, const tgui::String& text, tgui::Font font, unsigned int textSize,
                bool bold) -> tgui::String {
                return tgui::Text::wordWrap(maxWidth, text, font, textSize, bold);
            },
            [](float maxWidth, const tgui::String& text, tgui::Font font, unsigned int textSize,
                bool bold, bool dropLeadingSpace) -> tgui::String {
                return tgui::Text::wordWrap(maxWidth, text, font, textSize, bold, dropLeadingSpace);
            });
    }
};