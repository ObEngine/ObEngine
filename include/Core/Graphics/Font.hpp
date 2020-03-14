#pragma once

#include <SFML/Graphics/Font.hpp>

namespace obe::Graphics
{
    class Font
    {
    private:
        sf::Font m_font;

    public:
        Font();
        Font(const sf::Font& font);

        bool loadFromFile(const std::string& filename);

        operator sf::Font&();
        operator const sf::Font&() const;
    };

    inline Font::Font()
    {
    }

    inline Font::Font(const sf::Font& font)
    {
        m_font = font;
    }

    inline bool Font::loadFromFile(const std::string& filename)
    {
        return m_font.loadFromFile(filename);
    }

    inline Font::operator sf::Font&()
    {
        return m_font;
    }

    inline Font::operator const sf::Font&() const
    {
        return m_font;
    }
}
