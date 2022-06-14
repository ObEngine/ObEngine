#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Transform/Polygon.hpp>

namespace obe::debug::render
{
    void draw_polygon(const graphics::RenderTarget target, transform::Polygon& polygon,
        bool draw_lines, bool draw_points, bool draw_centroid, bool draw_skeleton,
        transform::UnitVector offset)
    {
        if (polygon.get_points_amount() >= 3)
        {
            const transform::UnitVector centroid
                = polygon.get_centroid().to<transform::Units::ScenePixels>();

            const float r = 6.f;

            const graphics::utils::DrawPolygonOptions draw_options {
                .lines = draw_lines,
                .points = draw_points,
                .radius = r
            };

            std::vector<transform::UnitVector> draw_points;
            std::vector<transform::UnitVector> pixel_points;
            const transform::PolygonPath& polygon_points = polygon.get_all_points();
            pixel_points.reserve(polygon_points.size());
            draw_points.reserve(polygon_points.size());

            std::ranges::transform(polygon_points,
                std::back_inserter(pixel_points),
                [](const auto& point) { return point->to(transform::Units::ScenePixels); });

            for (const transform::UnitVector& point : pixel_points)
            {
                draw_points.emplace_back(point - offset);
            }

            if (draw_centroid)
            {
                const sf::Color skeleton_color = sf::Color(255, 200, 0);
                const sf::Color centroid_color = sf::Color(255, 150, 0);
                sf::CircleShape point_shape;
                point_shape.setPosition(
                    sf::Vector2f(centroid.x - offset.x - r, centroid.y - offset.y - r));
                point_shape.setRadius(r);

                point_shape.setFillColor(centroid_color);
                target.draw(point_shape);
                if (draw_skeleton)
                {
                    for (const transform::UnitVector& point : pixel_points)
                    {

                        graphics::utils::draw_line(target, point.x - offset.x, point.y - offset.y,
                            centroid.x - offset.x, centroid.y - offset.y, 2, skeleton_color);
                    }
                }
            }
            graphics::utils::draw_polygon(target, draw_points, draw_options);
        }
    }
}
