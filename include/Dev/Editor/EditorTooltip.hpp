#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fmt/format.h>

namespace obe::Editor
{
    class Tooltip
    {
    private:
        sf::RectangleShape m_background;
        sf::Text m_text;
        bool m_empty = true;

    public:
        Tooltip();
        void clear();
        void draw() const;
        bool empty() const;
        template <class... T> void setText(const std::string& text, T... args);
        void setPosition(int x, int y);
    };

    template <class... T>
    void Tooltip::setText(const std::string& text, T... args)
    {
        m_text.setString(fmt::format(text, args...));

        sf::FloatRect bounds = m_text.getGlobalBounds();
        m_background.setSize(
            sf::Vector2f(bounds.width + 20, bounds.height - 10));

        m_empty = false;
    }
} // namespace obe::Editor