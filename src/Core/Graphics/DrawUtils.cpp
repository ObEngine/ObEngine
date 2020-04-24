#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>
#include <System/Window.hpp>

namespace obe::Graphics::Utils // <REVISION> Move to Utils/ ?
{
    template <typename T>
    T findOptionOrDefault(
        const DrawPolygonOptions& options, const char* key, T defaultValue)
    {
        if (options.find(key) == options.end())
            return defaultValue;
        return std::any_cast<T>(options.at(key));
    }

    void drawPoint(RenderTarget surface, int x, int y, float radius, const Color& color)
    {
        sf::CircleShape drawPt;
        drawPt.setRadius(radius);
        drawPt.setPosition(sf::Vector2f(x, y));
        drawPt.setFillColor(color);
        surface.draw(drawPt);
    }

    void drawLine(RenderTarget surface, int x1, int y1, int x2, int y2, int thickness,
        const Color& color)
    {
        sf::Vertex line[] = { sf::Vertex(sf::Vector2f(x1, y1), color),
            sf::Vertex(sf::Vector2f(x2, y2), color) };
        surface.draw(line, thickness, sf::Lines);
    }

    void drawPolygon(RenderTarget surface, std::vector<Transform::UnitVector>& points,
        const DrawPolygonOptions& options)
    {
        const bool drawLines = findOptionOrDefault(options, "lines", true);
        const bool drawPoints = findOptionOrDefault(options, "points", true);
        const float pointRadius = findOptionOrDefault(options, "radius", 6.f);
        const sf::Color lineColor
            = findOptionOrDefault(options, "line_color", sf::Color::White);
        const sf::Color pointColor
            = findOptionOrDefault(options, "point_color", sf::Color::White);
        sf::CircleShape polyPt;
        polyPt.setRadius(pointRadius);
        polyPt.setPointCount(100);
        polyPt.setFillColor(pointColor);
        for (std::size_t i = 0; i < points.size(); i++)
        {
            const Transform::UnitVector& point1
                = points[i].to<Transform::Units::ScenePixels>();
            const Transform::UnitVector& point2
                = points[(i == points.size() - 1) ? 0 : i + 1]
                      .to<Transform::Units::ScenePixels>();
            if (drawLines)
            {
                const sf::Color currentLineColor = findOptionOrDefault(
                    options, ("line_color_" + std::to_string(i)).c_str(), lineColor);
                drawLine(
                    surface, point1.x, point1.y, point2.x, point2.y, 2, currentLineColor);
            }
        }
        for (std::size_t i = 0; i < points.size(); i++)
        {
            const Transform::UnitVector& point1
                = points[i].to<Transform::Units::ScenePixels>();
            if (drawPoints)
            {
                const sf::Color currentPointColor = findOptionOrDefault(
                    options, ("point_color_" + std::to_string(i)).c_str(), pointColor);
                polyPt.setFillColor(currentPointColor);
                polyPt.setPosition(point1.x - pointRadius, point1.y - pointRadius);
                surface.draw(polyPt);
            }
        }
    }
} // namespace obe::Graphics::Utils