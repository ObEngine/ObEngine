#include <Transform/Exceptions.hpp>
#include <Transform/Referential.hpp>

#include <ostream> // Weird fix on latest versions of MSVC
#include <regex>

namespace obe::transform
{
    Referential Referential::TopLeft = Referential(0, 0);
    Referential Referential::Top = Referential(0.5, 0);
    Referential Referential::TopRight = Referential(1, 0);
    Referential Referential::Left = Referential(0, 0.5);
    Referential Referential::Center = Referential(0.5, 0.5);
    Referential Referential::Right = Referential(1, 0.5);
    Referential Referential::BottomLeft = Referential(0, 1);
    Referential Referential::Bottom = Referential(0.5, 1);
    Referential Referential::BottomRight = Referential(1, 1);
    std::array<Referential, 9> Referential::Referentials = { Referential::TopLeft, Referential::Top,
        Referential::TopRight, Referential::Left, Referential::Center, Referential::Right,
        Referential::BottomLeft, Referential::Bottom, Referential::BottomRight };

    Referential::Referential()
        : m_ref_x(0)
        , m_ref_y(0)
    {
    }

    Referential::Referential(const double x, const double y)
        : m_ref_x(x)
        , m_ref_y(y)
    {
        assert(x >= -1 && x <= 1);
        assert(y >= -1 && y <= 1);
    }

    bool Referential::operator==(const Referential& ref) const
    {
        return (get_offset() == ref.get_offset());
    }
    bool Referential::operator!=(const Referential& ref) const
    {
        return !((*this) == ref);
    }

    Referential Referential::flip(FlipAxis axis) const
    {
        const bool both_or_horizontal = (axis == FlipAxis::Both || axis == FlipAxis::Horizontal);
        const bool both_or_vertical = (axis == FlipAxis::Both || axis == FlipAxis::Vertical);
        return Referential(
            both_or_horizontal ? 1 - m_ref_x : m_ref_x, both_or_vertical ? 1 - m_ref_y : m_ref_y);
    }

    bool Referential::is_on_left_side() const
    {
        return m_ref_x == 0;
    }

    bool Referential::is_on_right_side() const
    {
        return m_ref_x == 1;
    }

    bool Referential::is_on_top_side() const
    {
        return m_ref_y == 0;
    }

    bool Referential::is_on_bottom_side() const
    {
        return m_ref_y == 1;
    }

    bool Referential::is_on_corner() const
    {
        return (is_on_left_side() || is_on_right_side()) && (is_on_top_side() || is_on_bottom_side());
    }

    bool Referential::is_on_side() const
    {
        return (is_on_left_side() || is_on_right_side()) ^ (is_on_top_side() || is_on_bottom_side());
    }

    bool Referential::is_known() const
    {
        return (m_ref_x == 0 || m_ref_x == 0.5 || m_ref_x == 1)
            && (m_ref_y == 0 || m_ref_y == 0.5 || m_ref_y == 1);
    }

    UnitVector Referential::get_offset() const
    {
        return UnitVector(m_ref_x, m_ref_y);
    }

    std::string Referential::to_string(const std::string& format) const
    {
        if (m_ref_x == 0 && m_ref_y == 0)
            return fmt::format(format, "TopLeft");
        if (m_ref_x == 0.5 && m_ref_y == 0)
            return fmt::format(format, "Top");
        if (m_ref_x == 1 && m_ref_y == 0)
            return fmt::format(format, "TopRight");
        if (m_ref_x == 0 && m_ref_y == 0.5)
            return fmt::format(format, "Left");
        if (m_ref_x == 0.5 && m_ref_y == 0.5)
            return fmt::format(format, "Center");
        if (m_ref_x == 1 && m_ref_y == 0.5)
            return fmt::format(format, "Right");
        if (m_ref_x == 0 && m_ref_y == 1)
            return fmt::format(format, "BottomLeft");
        if (m_ref_x == 0.5 && m_ref_y == 1)
            return fmt::format(format, "Bottom");
        if (m_ref_x == 1 && m_ref_y == 1)
            return fmt::format(format, "BottomRight");
        else
            return fmt::format(format, fmt::format("{}, {}", m_ref_x, m_ref_y), m_ref_x, m_ref_y);
    }

    Referential Referential::from_string(const std::string& ref)
    {
        if (ref == "TopLeft")
            return Referential::TopLeft;
        if (ref == "Top")
            return Referential::Top;
        if (ref == "TopRight")
            return Referential::TopRight;
        if (ref == "Left")
            return Referential::Left;
        if (ref == "Center")
            return Referential::Center;
        if (ref == "Right")
            return Referential::Right;
        if (ref == "BottomLeft")
            return Referential::BottomLeft;
        if (ref == "Bottom")
            return Referential::Bottom;
        if (ref == "BottomRight")
            return Referential::BottomRight;
        std::cmatch reg_match;
        const std::regex ref_regex(R"(Referential<\s*(-?\d+(\.\d+)?)\s*,\s*(-?\d+(\.\d+)?)\s*>)");
        std::regex_match(ref.c_str(), reg_match, ref_regex);
        if (reg_match.size() == 5)
        {
            return Referential(std::stod(reg_match[1]), std::stod(reg_match[3]));
        }
        throw exceptions::UnknownReferential(ref, EXC_INFO);
    }

    std::ostream& operator<<(std::ostream& os, Referential m)
    {
        os << m.to_string();
        return os;
    }
} // namespace obe::transform
