#include <cmath>

#include <Transform/AABB.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::transform
{
    AABB::AABB(const transform::UnitVector& position, const transform::UnitVector& size)
        : Movable(position)
        , m_size(size)
    {
    }

    double AABB::x() const
    {
        return m_position.x;
    }

    double AABB::y() const
    {
        return m_position.y;
    }

    double AABB::width() const
    {
        return m_size.x;
    }

    double AABB::height() const
    {
        return m_size.y;
    }

    bool AABB::intersects(const AABB& rect) const
    {
        const auto r1_min_x = std::min(m_position.x, m_position.x + m_size.x);
        const auto r1_max_x = std::max(m_position.x, m_position.x + m_size.x);
        const auto r1_min_y = std::min(m_position.y, m_position.y + m_size.y);
        const auto r1_max_y = std::max(m_position.y, m_position.y + m_size.y);

        const auto r2_min_x = std::min(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2_max_x = std::max(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2_min_y = std::min(rect.m_position.y, rect.m_position.y + rect.m_size.y);
        const auto r2_max_y = std::max(rect.m_position.y, rect.m_position.y + rect.m_size.y);

        return !(r2_min_x > r1_max_x || r2_max_x < r1_min_x || r2_min_y > r1_max_y
            || r2_max_y < r1_min_y);
    }

    std::optional<AABB> AABB::intersection(const AABB& rect) const
    {
        const auto r1_min_x = std::min(m_position.x, m_position.x + m_size.x);
        const auto r1_max_x = std::max(m_position.x, m_position.x + m_size.x);
        const auto r1_min_y = std::min(m_position.y, m_position.y + m_size.y);
        const auto r1_max_y = std::max(m_position.y, m_position.y + m_size.y);

        const auto r2_min_x = std::min(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2_max_x = std::max(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2_min_y = std::min(rect.m_position.y, rect.m_position.y + rect.m_size.y);
        const auto r2_max_y = std::max(rect.m_position.y, rect.m_position.y + rect.m_size.y);

        const auto intersection_left = std::max(r1_min_x, r2_min_x);
        const auto intersection_top = std::max(r1_min_y, r2_min_y);
        const auto intersection_right = std::min(r1_max_x, r2_max_x);
        const auto intersection_bottom = std::min(r1_max_y, r2_max_y);

        if ((intersection_left < intersection_right) && (intersection_top < intersection_bottom))
        {
            AABB intersection;
            intersection.set_position(
                UnitVector(intersection_left, intersection_top, m_position.unit));
            intersection.set_size(UnitVector(intersection_right - intersection_left,
                intersection_bottom - intersection_top, m_size.unit));
            return std::make_optional(intersection);
        }
        else
        {
            return std::nullopt;
        }
    }

    bool AABB::contains(const AABB& rect) const
    {
        return contains(rect.get_position(Referential::TopLeft))
            && contains(rect.get_position(Referential::BottomRight));
    }

    bool AABB::contains(const UnitVector& position) const
    {
        const UnitVector converted_position = position.to(m_position.unit);
        const auto min_x = std::min(m_position.x, m_position.x + m_size.x);
        const auto max_x = std::max(m_position.x, m_position.x + m_size.x);
        const auto min_y = std::min(m_position.y, m_position.y + m_size.y);
        const auto max_y = std::max(m_position.y, m_position.y + m_size.y);

        return (converted_position.x >= min_x) && (converted_position.x < max_x)
            && (converted_position.y >= min_y) && (converted_position.y < max_y);
    }

    void AABB::set_point_position(const UnitVector& position, const Referential& ref)
    {
        const UnitVector opposite_point_position = this->get_position(ref.flip());
        transform::UnitVector size = opposite_point_position - position;
        size.set(std::abs(size.x), std::abs(size.y));
        this->set_size(size);
        this->set_position(position, ref);
    }

    UnitVector AABB::get_position(const Referential& ref) const
    {
        return m_position + (m_size * ref.get_offset());
    }

    void AABB::set_position(const UnitVector& position, const Referential& ref)
    {
        transform::UnitVector p_vec = position.to<transform::Units::SceneUnits>();
        m_position = p_vec - (m_size * ref.get_offset());
    }

    void AABB::set_size(const UnitVector& size, const Referential& ref)
    {
        const UnitVector save_position = this->get_position(ref);
        m_size.set(size);
        this->set_position(save_position, ref);
    }

    void AABB::scale(const UnitVector& size, const Referential& ref)
    {
        const UnitVector save_position = this->get_position(ref);
        m_size *= size;
        this->set_position(save_position, ref);
    }

    UnitVector AABB::get_size() const
    {
        return m_size;
    }

    void AABB::move_point(const UnitVector& position, const Referential& ref)
    {
        this->set_point_position(position - this->get_position(ref), ref);
    }
} // namespace obe::transform
