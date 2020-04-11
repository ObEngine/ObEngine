#pragma once

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/Font.hpp>
#include <Transform/Rect.hpp>

namespace sf
{
    class Font;
    class String;
    template <class T> class Rect;
    typedef Rect<float> FloatRect;
}

namespace obe::Graphics
{
    class Text
    {
    public:
        Color color = Color::White;
        Color outline = Color::White;
        unsigned int thickness = 0;
        sf::Text::Style style = sf::Text::Style::Regular;
        std::wstring string;

        Text();
        Text(const std::string& string);
    };

    class RichText : public sf::Drawable, public sf::Transformable
    {
    private:
        /**
         * \nobind
         */
        class Line : public Transformable, public Drawable
        {
        public:
            void setCharacterSize(unsigned int size) const;
            void setFont(const sf::Font& font) const;
            const std::vector<sf::Text>& getTexts() const;
            void appendText(sf::Text text);
            sf::FloatRect getLocalBounds() const;
            sf::FloatRect getGlobalBounds() const;

        protected:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            void updateGeometry() const;
            void updateTextAndGeometry(sf::Text& text) const;
            mutable std::vector<sf::Text> m_texts;
            mutable sf::FloatRect m_bounds;
        };

    public:
        RichText();
        explicit RichText(const Font& font);

        void clear();

        RichText& append(const Text& text);

        const Font& getFont() const;
        void setFont(const Font& font);

        const std::vector<Line>& getLines() const;

        unsigned int getCharacterSize() const;
        void setCharacterSize(unsigned int size);

        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Text createText(const sf::String& string, const Color& color,
            const Color& outline, unsigned int thickness, sf::Text::Style style) const;
        void updateGeometry() const;
        mutable std::vector<Line> m_lines;
        Font m_font;
        unsigned int m_characterSize;
        mutable sf::FloatRect m_bounds;
    };
}
