#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Graphics::Utils // <REVISION> Move to Utils/ ?
{
    template <typename Key, typename Value>
    const Value& get_or(
        const std::unordered_map<Key, Value>& m, const Key& key, const Value& default_value)
    {
        auto it = m.find(key);
        if (it == m.end())
        {
            return default_value;
        }
        return it->second;
    }

    void drawPoint(RenderTarget surface, int x, int y, float radius, const Color& color)
    {
        sf::CircleShape drawPt;
        drawPt.setRadius(radius);
        drawPt.setPosition(sf::Vector2f(x, y));
        drawPt.setFillColor(color);
        surface.draw(drawPt);
    }

    void drawLine(
        RenderTarget surface, int x1, int y1, int x2, int y2, int thickness, const Color& color)
    {
        sf::Vertex line[]
            = { sf::Vertex(sf::Vector2f(x1, y1), color), sf::Vertex(sf::Vector2f(x2, y2), color) };
        surface.draw(line, thickness, sf::Lines);
    }

    void drawPolygon(RenderTarget surface, std::vector<Transform::UnitVector>& points,
        const DrawPolygonOptions& options)
    {
        sf::CircleShape polyPt;
        polyPt.setRadius(options.radius);
        polyPt.setPointCount(100);
        polyPt.setFillColor(sf::Color::White);
        for (std::size_t i = 0; i < points.size(); i++)
        {
            const Transform::UnitVector& point1 = points[i].to<Transform::Units::ScenePixels>();
            const Transform::UnitVector& point2
                = points[(i == points.size() - 1) ? 0 : i + 1].to<Transform::Units::ScenePixels>();
            if (options.lines)
            {
                const Color currentLineColor = get_or(
                    options.specificLineColor, static_cast<unsigned int>(i), options.lineColor);
                drawLine(surface, point1.x, point1.y, point2.x, point2.y, 2, currentLineColor);
            }
        }
        for (std::size_t i = 0; i < points.size(); i++)
        {
            const Transform::UnitVector& point1 = points[i].to<Transform::Units::ScenePixels>();
            if (options.points)
            {
                const Color currentPointColor = get_or(
                    options.specificPointColor, static_cast<unsigned int>(i), options.pointColor);
                polyPt.setFillColor(currentPointColor);
                polyPt.setPosition(point1.x - options.radius, point1.y - options.radius);
                surface.draw(polyPt);
            }
        }
    }
} // namespace obe::Graphics::Utils
