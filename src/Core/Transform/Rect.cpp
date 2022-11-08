#include <cmath>

#include <Graphics/DrawUtils.hpp>
#include <Transform/Rect.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::transform
{
    UnitVector rotate_point_around_center(
        const UnitVector& center, const UnitVector& around, double angle)
    {
        const double c_y = std::cos(angle);
        const double s_y = std::sin(angle);

        UnitVector moved;
        const UnitVector delta = around - center;
        moved.x = (delta.x * c_y - delta.y * s_y) + center.x;
        moved.y = (delta.x * s_y + delta.y * c_y) + center.y;

        return moved;
    };

    double Rect::get_rotation() const
    {
        return m_angle;
    }

    void Rect::set_rotation(double angle, transform::UnitVector origin)
    {
        this->rotate(angle - m_angle, origin);
    }

    void Rect::rotate(double angle, transform::UnitVector origin)
    {
        const double rad_angle = utils::math::convert_to_radian(-angle);

        m_position = rotate_point_around_center(origin, m_position, rad_angle);
        m_angle += angle;
        if (m_angle < 0 || m_angle > 360)
            m_angle = utils::math::normalize(m_angle, 0, 360);
    }

    void Rect::transform_referential(
        UnitVector& vec, const Referential& ref, ReferentialConversionType type) const
    {
        const double factor = (type == ReferentialConversionType::From) ? 1.0 : -1.0;
        const double rad_angle = utils::math::convert_to_radian(-m_angle);
        const double cos_angle = std::cos(rad_angle);
        const double sin_angle = std::sin(rad_angle);

        const auto delta = (ref.get_offset() * m_size);

        vec.add(UnitVector((delta.x * cos_angle - delta.y * sin_angle) * factor,
            (delta.x * sin_angle + delta.y * cos_angle) * factor));
    }

    Rect::Rect(const transform::UnitVector& position, const transform::UnitVector& size)
        : m_size(size)
    {
        m_position = position;
    }

    void Rect::draw(graphics::RenderTarget surface, int x, int y) const
    {
        float radius = 6.f;

        std::vector<transform::UnitVector> draw_points;
        const UnitVector d_pos(x, y, transform::Units::ScenePixels);

        const std::vector<Referential> fix_display_order = { Referential::TopLeft, Referential::Top,
            Referential::TopRight, Referential::Right, Referential::BottomRight,
            Referential::Bottom, Referential::BottomLeft, Referential::Left };

        for (uint8_t i = 0; i < 8; ++i)
        {
            UnitVector pt;
            this->transform_referential(pt, fix_display_order[i], ReferentialConversionType::From);

            UnitVector world = (pt + d_pos).to<Units::ScenePixels>();
            draw_points.push_back(world);
        }

        const double rad_angle = utils::math::convert_to_radian(-m_angle);
        const double cos_angle = std::cos(rad_angle);
        const double sin_angle = std::sin(rad_angle);
        UnitVector top_pos;
        this->transform_referential(top_pos, Referential::Top, ReferentialConversionType::From);
        top_pos = top_pos.to<Units::ScenePixels>();
        top_pos += d_pos;
        UnitVector vec = top_pos;
        UnitVector result;
        const double dy = m_size.y / 4;
        result.x = (-dy * sin_angle) * -1;
        result.y = (dy * cos_angle) * -1;
        vec += result;
        graphics::utils::draw_point(surface, static_cast<int>(vec.x - radius),
            static_cast<int>(vec.y - radius), radius, sf::Color::White);
        graphics::utils::draw_line(surface, static_cast<int>(vec.x), static_cast<int>(vec.y),
            static_cast<int>(top_pos.x), static_cast<int>(top_pos.y), 2, sf::Color::White);

        std::unordered_map<unsigned int, graphics::Color> points_color
            = { { 0, graphics::Color::Red }, { 1, graphics::Color(255, 128, 0) },
                  { 2, graphics::Color::Yellow }, { 3, graphics::Color(128, 255, 0) },
                  { 4, graphics::Color::Green }, { 5, graphics::Color(0, 255, 128) },
                  { 6, graphics::Color::Magenta }, { 7, graphics::Color(0, 128, 255) },
                  { 8, graphics::Color::Blue } };

        graphics::utils::DrawPolygonOptions options {
            .lines = true, .points = true, .radius = radius, .specific_point_color = points_color
        };

        graphics::utils::draw_polygon(surface, draw_points, options);
    }

    double Rect::x() const
    {
        return m_position.x;
    }

    double Rect::y() const
    {
        return m_position.y;
    }

    double Rect::width() const
    {
        return m_size.x;
    }

    double Rect::height() const
    {
        return m_size.y;
    }

    bool Rect::intersects(const Rect& rect) const
    {
        // TODO: fix for non-AABB rectangle
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

    std::optional<Rect> Rect::intersection(const Rect& rect) const
    {
        // TODO: fix for non-AABB rectangle
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
            Rect intersection;
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

    bool Rect::contains(const Rect& rect) const
    {
        // TODO: fix for non-AABB rectangle
        return contains(rect.get_position(Referential::TopLeft))
            && contains(rect.get_position(Referential::BottomRight));
    }

    bool Rect::contains(const UnitVector& position) const
    {
        // TODO: fix for non-AABB rectangle
        const UnitVector converted_position = position.to(m_position.unit);
        const auto min_x = std::min(m_position.x, m_position.x + m_size.x);
        const auto max_x = std::max(m_position.x, m_position.x + m_size.x);
        const auto min_y = std::min(m_position.y, m_position.y + m_size.y);
        const auto max_y = std::max(m_position.y, m_position.y + m_size.y);

        return (converted_position.x >= min_x) && (converted_position.x < max_x)
            && (converted_position.y >= min_y) && (converted_position.y < max_y);
    }

    void Rect::set_point_position(const UnitVector& position, const Referential& ref)
    {
        const UnitVector opposite_point_position = this->get_position(ref.flip());
        const double rad_angle = utils::math::convert_to_radian(-m_angle);
        const UnitVector moved_point
            = rotate_point_around_center(position, opposite_point_position, -rad_angle);

        this->set_position(position, ref);

        if (ref.is_on_corner())
        {
            if (ref.is_on_top_side())
            {
                this->set_size({ moved_point.x - position.x, moved_point.y - position.y }, ref);
            }
            else
            {
                this->set_size({ position.x - moved_point.x, position.y - moved_point.y }, ref);
            }
        }
        if (ref.is_on_left_side() || ref.is_on_right_side())
        {
            if (ref.is_on_left_side())
            {
                this->set_size({ moved_point.x - position.x, m_size.y }, ref);
            }
            else
            {
                this->set_size({ position.x - moved_point.x, m_size.y }, ref);
            }
        }
        else // we are on TopSide or BottomSide here, no need to specify the
            // condition
        {
            if (ref.is_on_top_side())
            {
                this->set_size({ m_size.x, moved_point.y - position.y }, ref);
            }
            else
            {
                this->set_size({ m_size.x, position.y - moved_point.y }, ref);
            }
        }
    }

    UnitVector Rect::get_position(const Referential& ref) const
    {
        UnitVector pos_vec = m_position;
        this->transform_referential(pos_vec, ref, ReferentialConversionType::From);
        return pos_vec;
    }

    void Rect::set_position(const UnitVector& position, const Referential& ref)
    {
        UnitVector p_vec = position.to<Units::SceneUnits>();
        this->transform_referential(p_vec, ref, ReferentialConversionType::To);
        m_position.set(p_vec);
    }

    void Rect::set_size(const UnitVector& size, const Referential& ref)
    {
        const UnitVector save_position = this->get_position(ref);
        m_size.set(size);
        this->set_position(save_position, ref);
    }

    void Rect::scale(const UnitVector& size, const Referential& ref)
    {
        const UnitVector save_position = this->get_position(ref);
        m_size *= size;
        this->set_position(save_position, ref);
    }

    UnitVector Rect::get_size() const
    {
        return m_size;
    }

    void Rect::move_point(const UnitVector& position, const Referential& ref)
    {
        this->set_point_position(position - this->get_position(ref), ref);
    }

    UnitVector Rect::get_scale_factor() const
    {
        return UnitVector(utils::math::sign(m_size.x), utils::math::sign(m_size.y));
    }
} // namespace obe::transform
