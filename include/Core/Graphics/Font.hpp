#pragma once

#include <SFML/Graphics/Font.hpp>

namespace obe::graphics
{
    class Font
    {
    private:
        sf::Font m_font;

    public:
        Font() = default;
        Font(const Font& font) = default;
        Font(const sf::Font& font);

        bool load_from_file(const std::string& filename);

        bool operator==(const Font& font) const;
        operator sf::Font&();
        operator const sf::Font&() const;
        operator bool() const;
    };

    inline Font::Font(const sf::Font& font)
        : m_font(font)
    {
    }

    inline bool Font::load_from_file(const std::string& filename)
    {
        return m_font.loadFromFile(filename);
    }

    inline bool Font::operator==(const Font& font) const
    {
        return m_font.getInfo().family == font.m_font.getInfo().family;
    }

    inline Font::operator sf::Font&()
    {
        return m_font;
    }

    inline Font::operator const sf::Font&() const
    {
        return m_font;
    }

    inline Font::operator bool() const
    {
        return !m_font.getInfo().family.empty();
    }
} // namespace obe::graphics
