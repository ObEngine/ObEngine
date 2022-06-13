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
    template <class T>
    class Rect;
    typedef Rect<float> FloatRect;
}

namespace obe::graphics
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
            void set_character_size(unsigned int size) const;
            void set_font(const sf::Font& font) const;
            const std::vector<sf::Text>& get_texts() const;
            void append_text(sf::Text text) const;
            // todo: return proper obe Rect
            sf::FloatRect get_local_bounds() const;
            sf::FloatRect get_global_bounds() const;

        protected:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            void update_geometry() const;
            void update_text_and_geometry(sf::Text& text) const;
            mutable std::vector<sf::Text> m_texts;
            mutable sf::FloatRect m_bounds;
        };

    public:
        RichText();
        explicit RichText(const Font& font);

        void clear();

        RichText& append(const Text& text);

        const Font& get_font() const;
        void set_font(const Font& font);

        const std::vector<Line>& get_lines() const;

        unsigned int get_character_size() const;
        void set_character_size(unsigned int size);

        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Text create_text(const sf::String& string, const Color& color, const Color& outline,
            unsigned int thickness, sf::Text::Style style) const;
        void update_geometry() const;
        mutable std::vector<Line> m_lines;
        Font m_font;
        unsigned int m_character_size;
        mutable sf::FloatRect m_bounds;
    };
}
