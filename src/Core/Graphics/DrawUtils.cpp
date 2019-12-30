#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>
#include <System/Window.hpp>

namespace obe::Graphics::Utils // <REVISION> Move to Utils/ ?
{
    template <typename T>
    T findOptionOrDefault(const DrawPolygonOptions& options, const char* key, T defaultValue)
    {
        if (options.find(key) == options.end())
            return defaultValue;
        return std::any_cast<T>(options.at(key));
    }

    void drawPoint(int x, int y, unsigned int radius, sf::Color color)
    {
        sf::CircleShape drawPt;
        drawPt.setRadius(radius);
        drawPt.setPosition(sf::Vector2f(x, y));
        drawPt.setFillColor(color);
        System::MainWindow.draw(drawPt);
    }

    void drawLine(int x1, int y1, int x2, int y2, int thickness, sf::Color color)
    {
        sf::Vertex line[]
            = { sf::Vertex(sf::Vector2f(x1, y1), color), sf::Vertex(sf::Vector2f(x2, y2), color) };
        System::MainWindow.draw(line, thickness, sf::Lines);
    }

    void drawPolygon(std::vector<sf::Vector2i>& points, DrawPolygonOptions options)
    {
        const bool drawLines = findOptionOrDefault(options, "lines", true);
        const bool drawPoints = findOptionOrDefault(options, "points", true);
        const int pointRadius = findOptionOrDefault(options, "radius", 6);
        const sf::Color lineColor = findOptionOrDefault(options, "line_color", sf::Color::White);
        const sf::Color pointColor = findOptionOrDefault(options, "point_color", sf::Color::White);
        sf::CircleShape polyPt;
        polyPt.setRadius(pointRadius);
        polyPt.setPointCount(100);
        polyPt.setFillColor(pointColor);
        for (unsigned int i = 0; i < points.size(); i++)
        {
            const sf::Vector2i& point1 = points[i];
            const sf::Vector2i& point2 = points[(i == points.size() - 1) ? 0 : i + 1];
            if (drawLines)
            {
                const sf::Color currentLineColor = findOptionOrDefault(
                    options, ("line_color_" + std::to_string(i)).c_str(), lineColor);
                drawLine(point1.x, point1.y, point2.x, point2.y, 2, currentLineColor);
            }
        }
        for (unsigned int i = 0; i < points.size(); i++)
        {
            const sf::Vector2i& point1 = points[i];
            if (drawPoints)
            {
                const sf::Color currentPointColor = findOptionOrDefault(
                    options, ("point_color_" + std::to_string(i)).c_str(), pointColor);
                polyPt.setFillColor(currentPointColor);
                polyPt.setPosition(point1.x - pointRadius, point1.y - pointRadius);
                System::MainWindow.draw(polyPt);
            }
        }
    }

    sf::Color ClearColor = sf::Color::Black; // <REVISION> Move to Window.hpp ?
} // namespace obe::Graphics::Utils