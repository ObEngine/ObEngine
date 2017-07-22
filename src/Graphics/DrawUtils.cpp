#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>

namespace obe
{
    namespace Graphics
    {
        namespace Utils
        {
            template <typename T>
            T findOptionOrDefault(std::map<std::string, Types::Any>& options, const char* key, T defaultValue)
            {
                if (options.find(key) == options.end())
                    return defaultValue;
                return options[key].as<T>();
            }

            void drawPoint(sf::RenderWindow& target, int x, int y, unsigned radius, sf::Color& col)
            {
                sf::CircleShape drawPt;
                drawPt.setRadius(radius);
                drawPt.setPosition(sf::Vector2f(x, y));
                drawPt.setFillColor(col);
                target.draw(drawPt);
            }

            void drawLine(sf::RenderWindow& target, int x1, int y1, int x2, int y2, int w, sf::Color& col)
            {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x1, y1), col),
                    sf::Vertex(sf::Vector2f(x2, y2), col)
                };
                target.draw(line, w, sf::Lines);
            }

            void drawPolygon(sf::RenderWindow& target, std::vector<sf::Vector2i>& points, std::map<std::string, Types::Any>& options)
            {
                bool drawLines = findOptionOrDefault(options, "lines", true);
                bool drawPoints = findOptionOrDefault(options, "points", true);
                int pointRadius = findOptionOrDefault(options, "radius", 6);
                sf::Color lineColor = findOptionOrDefault(options, "line_color", sf::Color::White);
                sf::Color pointColor = findOptionOrDefault(options, "point_color", sf::Color::White);
                sf::CircleShape polyPt;
                polyPt.setRadius(pointRadius);
                polyPt.setPointCount(100);
                polyPt.setFillColor(pointColor);
                for (unsigned int i = 0; i < points.size(); i++)
                {
                    sf::Vector2i& point1 = points[i];
                    sf::Vector2i& point2 = points[(i == points.size() - 1) ? 0 : i + 1];
                    if (drawLines)
                    {
                        sf::Color currentLineColor = findOptionOrDefault(options, ("line_color_" + std::to_string(i)).c_str(), lineColor);
                        drawLine(target, point1.x, point1.y, point2.x, point2.y, 2, currentLineColor);
                    }
                    if (drawPoints)
                    {
                        sf::Color currentPointColor = findOptionOrDefault(options, ("point_color_" + std::to_string(i)).c_str(), pointColor);
                        polyPt.setFillColor(currentPointColor);
                        polyPt.setPosition(point1.x - pointRadius, point1.y - pointRadius);
                        target.draw(polyPt);
                    }
                }
            }
        }
    }
}
