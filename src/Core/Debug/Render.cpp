#include <SFML/Graphics/CircleShape.hpp>

#include <Debug/Render.hpp>
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
                .lines = draw_lines, .points = draw_points, .radius = r
            };

            std::vector<transform::UnitVector> draw_points;
            std::vector<transform::UnitVector> pixel_points;
            const transform::PolygonPath& polygon_points = polygon.get_all_points();
            pixel_points.reserve(polygon_points.size());
            draw_points.reserve(polygon_points.size());

            std::transform(polygon_points.begin(), polygon_points.end(),
                std::back_inserter(pixel_points),
                [](const auto& point)
                {
                    return point.to(transform::Units::ScenePixels);
                });

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

    void draw_circle_collider(const graphics::RenderTarget target,
        const collision::CircleCollider& collider, const ColliderRenderOptions& render_options)
    {
        const transform::UnitVector px_position
            = collider.get_position().to<transform::Units::ScenePixels>();
        const double px_radius
            = transform::UnitVector(collider.get_radius(), 0).to<transform::Units::ScenePixels>().x;
        sf::CircleShape shape(px_radius);
        shape.setPosition(px_position.x - px_radius, px_position.y - px_radius);
        shape.setFillColor(render_options.color);
        target.draw(shape);
    }

    void draw_rectangle_collider(const graphics::RenderTarget target,
        const collision::RectangleCollider& collider, const ColliderRenderOptions& render_options)
    {
        const transform::UnitVector px_position
            = collider.get_position().to<transform::Units::ScenePixels>();
        const transform::UnitVector px_size
            = collider.get_size().to<transform::Units::ScenePixels>();
        sf::RectangleShape shape(sf::Vector2f(px_size.x, px_size.y));
        shape.setPosition(px_position.x, px_position.y);
        shape.setFillColor(render_options.color);
        target.draw(shape);
    }

    void draw_capsule_collider(const graphics::RenderTarget target,
        const collision::CapsuleCollider& collider, const ColliderRenderOptions& render_options)
    {
    }

    void draw_polygon_collider(const graphics::RenderTarget target,
        const collision::PolygonCollider& collider, const ColliderRenderOptions& render_options)
    {
        const transform::UnitVector px_position
            = collider.get_position().to<transform::Units::ScenePixels>();
        sf::ConvexShape shape(collider.get_points_amount());
        size_t idx = 0;
        transform::Polygon polygon = collider.get_polygon();
        const auto& points = polygon.get_all_points();
        for (const auto& point : points)
        {
            auto point_pos_px = point.to<transform::Units::ScenePixels>();
            shape.setPoint(idx++, sf::Vector2f(point_pos_px.x, point_pos_px.y));
        }
        shape.setFillColor(render_options.color);
        target.draw(shape);
    }

    void draw_collider(const graphics::RenderTarget target,
        const collision::ColliderComponent& collider, const ColliderRenderOptions& render_options)
    {
        switch (collider.get_collider_type())
        {
        case collision::ColliderType::Collider:
            break;
        case collision::ColliderType::Circle:
            draw_circle_collider(target,
                *static_cast<const collision::CircleCollider*>(collider.get_inner_collider()),
                render_options);
            break;
        case collision::ColliderType::Rectangle:
            draw_rectangle_collider(target,
                *static_cast<const collision::RectangleCollider*>(collider.get_inner_collider()),
                render_options);
            break;
        case collision::ColliderType::Capsule:
            draw_capsule_collider(target,
                *static_cast<const collision::CapsuleCollider*>(collider.get_inner_collider()),
                render_options);
            break;
        case collision::ColliderType::Polygon:
            draw_polygon_collider(target,
                *static_cast<const collision::PolygonCollider*>(collider.get_inner_collider()),
                render_options);
            break;
        default:;
        }
    }
}
