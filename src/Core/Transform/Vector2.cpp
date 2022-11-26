#include <ostream>

#include <Transform/Matrix2D.hpp>
#include <Transform/Vector2.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::transform
{
    Vector2::Vector2(const double x, const double y)
        : x(x)
        , y(y)
    {
    }

    Vector2& Vector2::operator=(const Vector2& copy)
    {
        x = copy.x;
        y = copy.y;
        return *this;
    }

    Vector2 Vector2::operator+(const Vector2& add) const
    {
        return Vector2(x + add.x, y + add.y);
    }

    Vector2& Vector2::operator+=(const Vector2& add)
    {
        x += add.x;
        y += add.y;
        return *this;
    }

    Vector2 Vector2::operator-(const Vector2& sub) const
    {
        return Vector2(x - sub.x, y - sub.y);
    }

    Vector2& Vector2::operator-=(const Vector2& sub)
    {
        x -= sub.x;
        y -= sub.y;
        return *this;
    }

    Vector2 Vector2::operator*(const Vector2& mul) const
    {
        return Vector2(x * mul.x, y * mul.y);
    }

    Vector2& Vector2::operator*=(const Vector2& mul)
    {
        x *= mul.x;
        y *= mul.y;
        return *this;
    }

    Vector2 Vector2::operator/(const Vector2& div) const
    {
        return Vector2(x / div.x, y / div.y);
    }

    Vector2& Vector2::operator/=(const Vector2& div)
    {
        x /= div.x;
        y /= div.y;
        return *this;
    }

    Vector2 Vector2::operator+(const double add) const
    {
        return Vector2(x + add, y + add);
    }

    Vector2 Vector2::operator-(const double sub) const
    {
        return Vector2(x - sub, y - sub);
    }

    Vector2 Vector2::operator*(const double mul) const
    {
        return Vector2(x * mul, y * mul);
    }

    Vector2 Vector2::operator/(const double div) const
    {
        return Vector2(x / div, y / div);
    }

    Vector2& Vector2::operator+=(const double add)
    {
        x += add;
        y += add;
        return *this;
    }

    Vector2& Vector2::operator-=(const double sub)
    {
        x -= sub;
        y -= sub;
        return *this;
    }

    Vector2& Vector2::operator*=(const double mul)
    {
        x *= mul;
        y *= mul;
        return *this;
    }

    Vector2& Vector2::operator/=(const double div)
    {
        x /= div;
        y /= div;
        return *this;
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    bool Vector2::operator==(const Vector2& vec) const
    {
        return (x == vec.x && y == vec.y);
    }

    bool Vector2::operator!=(const Vector2& vec) const
    {
        return (x != vec.x || y != vec.y);
    }

    std::tuple<double, double> Vector2::unpack() const
    {
        return std::make_tuple(x, y);
    }

    std::ostream& operator<<(std::ostream& os, const Vector2& m)
    {
        os << "(" << m.x << ", " << m.y << ")::" << UnitsMeta::to_string(m.unit);
        return os;
    }

    Vector2 Vector2::rotate(double angle, Vector2 zero) const
    {
        const double rad_angle = utils::math::convert_to_radian(angle);
        Matrix2D rot({ std::cos(rad_angle), -std::sin(rad_angle), std::sin(rad_angle),
            std::cos(rad_angle) });
        const Vector2 result = rot.product(*this - zero) + zero;
        return result;
    }
    double Vector2::distance(const Vector2& vec) const
    {
        return std::sqrt(std::pow(x - vec.x, 2) + std::pow(y - vec.y, 2));
    }
    double Vector2::magnitude() const
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }
} // namespace obe::transform
