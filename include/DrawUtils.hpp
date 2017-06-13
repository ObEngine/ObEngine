#pragma once

#include <SFML/Graphics.hpp>
#include <any/any.hpp>

namespace obe
{
    namespace Graphics
    {
        namespace Utils
        {
            enum DrawOptions
            {
                Lines,
                Points
            };
            void drawLine(sf::RenderWindow& target, int x1, int y1, int x2, int y2, int w, sf::Color& col);
            void drawPolygon(sf::RenderWindow& target, std::vector<sf::Vector2i>& points, std::map<std::string, obe::Types::any>& options);
        }
    }
}