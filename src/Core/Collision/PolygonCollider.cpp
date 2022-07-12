#include <span>

#include <Collision/PolygonCollider.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::collision
{
    void* PolygonCollider::get_c2_shape()
    {
        return static_cast<void*>(&m_shape);
    }

    void PolygonCollider::update_shape()
    {
        const float radians = utils::math::convert_to_radian(m_angle);
        const float x = static_cast<float>(Collider::m_position.x);
        const float y = static_cast<float>(Collider::m_position.y);
        m_global_transform.p = c2v { x, y };
        m_global_transform.r = c2Rot(radians);
        c2MakePoly(&m_shape);
    }

    ColliderType PolygonCollider::get_collider_type() const
    {
        return PolygonCollider::Type;
    }

    PolygonCollider::PolygonCollider()
    {
        m_shape.count = 0;
        update_shape();
    }

    PolygonCollider::PolygonCollider(const transform::UnitVector& position)
        : Collider(position)
    {
        m_shape.count = 0;
        update_shape();
    }

    transform::Rect PolygonCollider::get_bounding_box() const
    {
        const auto verts_span = std::span { m_shape.verts };
        auto [min_x, max_x] = std::minmax_element(verts_span.begin(), verts_span.begin() + m_shape.count,
            [](auto& point1, auto& point2) { return point1.x < point2.x; });
        auto [min_y, max_y]
            = std::minmax_element(verts_span.begin(), verts_span.begin() + m_shape.count,
            [](auto& point1, auto& point2) { return point1.y < point2.y; });
        const double width = max_x->x - min_x->x;
        const double height = max_y->y - min_y->y;
        return transform::Rect(transform::UnitVector(min_x->x, min_y->y),
            transform::UnitVector(width, height));
    }

    transform::UnitVector PolygonCollider::get_position() const
    {
        return Collider::get_position();
    }

    void PolygonCollider::set_position(const transform::UnitVector& position)
    {
        Collider::set_position(position);
        update_shape();
    }

    void PolygonCollider::move(const transform::UnitVector& position)
    {
        Collider::move(position);
        update_shape();
    }

    void PolygonCollider::add_point(const transform::UnitVector& position, int point_index)
    {
        if (point_index < 0)
        {
            point_index = m_shape.count;
            m_shape.count++;
        }
        m_shape.verts[point_index] = c2v(position.x, position.y);
        update_shape();
    }

    std::size_t PolygonCollider::get_points_amount() const
    {
        return m_shape.count;
    }

    void PolygonCollider::set_rotation(float angle)
    {
        m_angle = angle;
        update_shape();
    }

    void PolygonCollider::rotate(float angle)
    {
        m_angle += angle;
        update_shape();
    }

    float PolygonCollider::get_rotation() const
    {
        return m_angle;
    }
}
