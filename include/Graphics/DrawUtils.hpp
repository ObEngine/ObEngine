#pragma once

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <Types/Any.hpp>

namespace obe
{
    namespace Graphics
    {
        /**
         * \brief Some useful Graphics functions.
         */
        namespace Utils
        {
            /**
             * \brief Draws a Line
             * \param target Window you want to draw the Line on
             * \param x1 x Coordinate of the first point of the line
             * \param y1 y Coordinate of the first point of the line
             * \param x2 x Coordinate of the second point of the line
             * \param y2 y Coordinate of the second point of the line
             * \param w Thickness of the line you want to draw (2 = Minimal visible size)
             * \param col Color of the line you want to draw
             */
            void drawLine(sf::RenderWindow& target, int x1, int y1, int x2, int y2, int w, sf::Color& col);
            /**
             * \brief Draws a Polygon
             * \param target Window you want to draw the Line on
             * \param points List of all the Polygon points positions
             * \param options Drawing options :\n
             *        - <lines> bool : Are the lines of the Polygon visible ? (true = visible, false = not visible)
             *        - <points> bool : Are the points of the Polygon visible ? (true = visible, false = not visible)
             *        - <radius> unsigned int : The radius of the points of the Polygon.
             *        - <line_color> sf::Color : Default color of the lines of the Polygon.
             *          - <line_color_x> sf::Color : Color of a specific line of the Polygon where x is the index of the line
             *        - <point_color> sf::Color : Default color of the points of the Polygon
             *          - <point_color_x> sf::Color : Color of a specific point of the Polygon where x is the index of the point
             */
            void drawPolygon(sf::RenderWindow& target, std::vector<sf::Vector2i>& points, std::map<std::string, Types::Any>& options);
        }
    }
}