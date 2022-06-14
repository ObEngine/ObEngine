#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::graphics::utils // <REVISION> Move to utils/ ?
{
    template <typename Key, typename Value>
    const Value& get_key_or(
        const std::unordered_map<Key, Value>& m, const Key& key, const Value& default_value)
    {
        auto it = m.find(key);
        if (it == m.end())
        {
            return default_value;
        }
        return it->second;
    }

    void draw_point(RenderTarget surface, int x, int y, float radius, const Color& color)
    {
        sf::CircleShape point_shape;
        point_shape.setRadius(radius);
        point_shape.setPosition(sf::Vector2f(x, y));
        point_shape.setFillColor(color);
        surface.draw(point_shape);
    }

    void draw_line(
        RenderTarget surface, int x1, int y1, int x2, int y2, int thickness, const Color& color)
    {
        const sf::Vertex line[]
            = { sf::Vertex(sf::Vector2f(x1, y1), color), sf::Vertex(sf::Vector2f(x2, y2), color) };
        surface.draw(line, thickness, sf::Lines);
    }

    void draw_polygon(RenderTarget surface, const std::vector<transform::UnitVector>& points,
        const DrawPolygonOptions& options)
    {
        sf::CircleShape point_shape;
        point_shape.setRadius(options.radius);
        point_shape.setPointCount(100);
        point_shape.setFillColor(sf::Color::White);
        for (std::size_t i = 0; i < points.size(); i++)
        {
            const transform::UnitVector& point1 = points[i].to<transform::Units::ScenePixels>();
            const transform::UnitVector& point2
                = points[(i == points.size() - 1) ? 0 : i + 1].to<transform::Units::ScenePixels>();
            if (options.lines)
            {
                const Color current_line_color = get_key_or(
                    options.specific_line_color, static_cast<unsigned int>(i), options.line_color);
                draw_line(surface, point1.x, point1.y, point2.x, point2.y, 2, current_line_color);
            }
        }
        for (std::size_t i = 0; i < points.size(); i++)
        {
            const transform::UnitVector& point1 = points[i].to<transform::Units::ScenePixels>();
            if (options.points)
            {
                const Color current_point_color = get_key_or(
                    options.specific_point_color, static_cast<unsigned int>(i), options.point_color);
                point_shape.setFillColor(current_point_color);
                point_shape.setPosition(point1.x - options.radius, point1.y - options.radius);
                surface.draw(point_shape);
            }
        }
    }
} // namespace obe::graphics::utils
