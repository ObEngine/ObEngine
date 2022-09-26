#include <span>

#include <Collision/PolygonCollider.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::collision
{
    const void* PolygonCollider::get_c2_shape() const
    {
        return static_cast<const void*>(&m_shape);
    }

    const c2x* PolygonCollider::get_c2_space_transform() const
    {
        return &m_transform;
    }

    void PolygonCollider::update_transform()
    {
        const c2v position = { static_cast<float>(m_position.x), static_cast<float>(m_position.y) };
        const c2r rotation = c2Rot(utils::math::convert_to_radian(m_angle));
        m_transform.p = position;
        m_transform.r = rotation;
    }

    void PolygonCollider::update_shape()
    {
        if (m_shape.count > 2)
        {
            c2MakePoly(&m_shape);
        }
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
        // TODO: handle rotation
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
        update_transform();
    }

    void PolygonCollider::move(const transform::UnitVector& position)
    {
        Collider::move(position);
        update_transform();
    }

    void PolygonCollider::add_point(const transform::UnitVector& position, int point_index)
    {
        if (point_index < 0)
        {
            point_index = m_shape.count;
            m_shape.count++;
        }
        m_shape.verts[point_index] = c2v { static_cast<float>(position.x), static_cast<float>(position.y) };
        update_shape();
    }

    std::size_t PolygonCollider::get_points_amount() const
    {
        return m_shape.count;
    }

    transform::Polygon PolygonCollider::get_polygon() const
    {
        transform::Polygon result;
        for (uint32_t point_index = 0; point_index < m_shape.count; point_index++)
        {
            c2v point = m_shape.verts[point_index];
            result.add_point(transform::UnitVector(point.x + m_position.x, point.y + m_position.y));
        }
        result.set_rotation(m_angle, m_position);
        return result;
    }

    void PolygonCollider::set_rotation(float angle)
    {
        m_angle = angle;
        update_transform();
    }

    void PolygonCollider::rotate(float angle)
    {
        m_angle += angle;
        update_transform();
    }

    float PolygonCollider::get_rotation() const
    {
        return m_angle;
    }
}
