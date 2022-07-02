#include <ostream>

#include <Transform/Matrix2D.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::transform
{
    void UnitVector::init(ViewStruct*& view)
    {
        view = &UnitVector::View;
    }

    void UnitVector::init(const int width, const int height)
    {
        Screen.w = width;
        Screen.h = height;
    }

    UnitVector::UnitVector(const Units unit)
    {
        this->unit = unit;
    }

    UnitVector::UnitVector(const double x, const double y, const Units unit)
    {
        this->x = x;
        this->y = y;
        this->unit = unit;
    }

    void UnitVector::set(const UnitVector& vec)
    {
        const UnitVector p_vec = vec.to(unit);
        x = p_vec.x;
        y = p_vec.y;
    }

    void UnitVector::set(const double x, const double y)
    {
        this->x = x;
        this->y = y;
    }

    void UnitVector::add(const UnitVector& vec)
    {
        const UnitVector p_vec = vec.to(unit);
        x += p_vec.x;
        y += p_vec.y;
    }

    void UnitVector::add(const double x, const double y)
    {
        this->x += x;
        this->y += y;
    }

    UnitVector UnitVector::operator+(const UnitVector& add) const
    {
        const UnitVector p_vec = add.to(unit);
        return UnitVector(x + p_vec.x, y + p_vec.y, unit);
    }

    UnitVector& UnitVector::operator+=(const UnitVector& add)
    {
        const UnitVector p_vec = add.to(unit);
        x += p_vec.x;
        y += p_vec.y;
        return *this;
    }

    UnitVector UnitVector::operator-(const UnitVector& sub) const
    {
        const UnitVector p_vec = sub.to(unit);
        return UnitVector(x - p_vec.x, y - p_vec.y, unit);
    }

    UnitVector& UnitVector::operator-=(const UnitVector& sub)
    {
        const UnitVector p_vec = sub.to(unit);
        x -= p_vec.x;
        y -= p_vec.y;
        return *this;
    }

    UnitVector UnitVector::operator*(const UnitVector& mul) const
    {
        const UnitVector p_vec = mul.to(unit);
        return UnitVector(x * p_vec.x, y * p_vec.y, unit);
    }

    UnitVector& UnitVector::operator*=(const UnitVector& mul)
    {
        const UnitVector p_vec = mul.to(unit);
        x *= p_vec.x;
        y *= p_vec.y;
        return *this;
    }

    UnitVector UnitVector::operator/(const UnitVector& div) const
    {
        const UnitVector p_vec = div.to(unit);
        return UnitVector(x / p_vec.x, y / p_vec.y, unit);
    }

    UnitVector& UnitVector::operator/=(const UnitVector& div)
    {
        const UnitVector p_vec = div.to(unit);
        x /= p_vec.x;
        y /= p_vec.y;
        return *this;
    }

    UnitVector UnitVector::operator+(const double add) const
    {
        return UnitVector(x + add, y + add, unit);
    }

    UnitVector UnitVector::operator-(const double sub) const
    {
        return UnitVector(x - sub, y - sub, unit);
    }

    UnitVector UnitVector::operator*(const double mul) const
    {
        return UnitVector(x * mul, y * mul, unit);
    }

    UnitVector UnitVector::operator/(const double div) const
    {
        return UnitVector(x / div, y / div, unit);
    }

    UnitVector& UnitVector::operator+=(const double add)
    {
        x += add;
        y += add;
        return *this;
    }

    UnitVector& UnitVector::operator-=(const double sub)
    {
        x -= sub;
        y -= sub;
        return *this;
    }

    UnitVector& UnitVector::operator*=(const double mul)
    {
        x *= mul;
        y *= mul;
        return *this;
    }

    UnitVector& UnitVector::operator/=(const double div)
    {
        x /= div;
        y /= div;
        return *this;
    }

    UnitVector UnitVector::operator-() const
    {
        return UnitVector(-x, -y, unit);
    }

    bool UnitVector::operator==(const UnitVector& vec) const
    {
        const UnitVector p_vec = vec.to(unit);
        return (x == p_vec.x && y == p_vec.y);
    }

    bool UnitVector::operator!=(const UnitVector& vec) const
    {
        const UnitVector p_vec = vec.to(unit);
        return (x != p_vec.x || y != p_vec.y);
    }

    UnitVector UnitVector::to(Units p_unit) const
    {
        switch (p_unit)
        {
        case Units::ViewPercentage:
            switch (unit)
            {
            case Units::ViewPercentage:
                return UnitVector(x, y, Units::ViewPercentage);
            case Units::ViewPixels:
                return UnitVector(x / Screen.w, y / Screen.h, Units::ViewPercentage);
            case Units::ViewUnits:
                return UnitVector(x / View.w, y / View.h, Units::ViewPercentage);
            case Units::ScenePixels:
                return UnitVector(x / Screen.w - View.x / View.w, y / Screen.h - View.y / View.h,
                    Units::ViewPercentage);
            case Units::SceneUnits:
                return UnitVector(
                    (x - View.x) / View.w, (y - View.y) / View.h, Units::ViewPercentage);
            default:
                return UnitVector(0, 0);
            }
        case Units::ViewPixels:
            switch (unit)
            {
            case Units::ViewPercentage:
                return UnitVector(x * Screen.w, y * Screen.h, Units::ViewPixels);
            case Units::ViewPixels:
                return UnitVector(x, y, Units::ViewPixels);
            case Units::ViewUnits:
                return UnitVector(x * Screen.w / View.w, y * Screen.h / View.h, Units::ViewPixels);
            case Units::ScenePixels:
                return UnitVector(x - (View.x * Screen.w / View.w),
                    y - (View.y * Screen.h / View.h), Units::ViewPixels);
            case Units::SceneUnits:
                return UnitVector((x - View.x) / View.w * Screen.w,
                    (y - View.y) / View.h * Screen.h, Units::ViewPixels);
            default:
                return UnitVector(0, 0);
            }
        case Units::ViewUnits:
            switch (unit)
            {
            case Units::ViewPercentage:
                return UnitVector(x * View.w, y * View.h, Units::ViewUnits);
            case Units::ViewPixels:
                return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, Units::ViewUnits);
            case Units::ViewUnits:
                return UnitVector(x, y, Units::ViewUnits);
            case Units::ScenePixels:
                return UnitVector(x / (Screen.w / View.w) - View.x,
                    y / (Screen.h / View.h) - View.y, Units::ViewUnits);
            case Units::SceneUnits:
                return UnitVector(x - View.x, y - View.y, Units::ViewUnits);
            default:
                return UnitVector(0, 0);
            }
        case Units::ScenePixels:
            switch (unit)
            {
            case Units::ViewPercentage:
                return UnitVector(Screen.w * (View.x / View.w + x),
                    Screen.h * (View.y / View.h + y), Units::ScenePixels);
            case Units::ViewPixels:
                return UnitVector(Screen.w * View.x / View.w + x, Screen.h * View.y / View.h + y,
                    Units::ScenePixels);
            case Units::ViewUnits:
                return UnitVector(Screen.w * (View.x + x) / View.w,
                    Screen.h * (View.y + y) / View.h, Units::ScenePixels);
            case Units::ScenePixels:
                return UnitVector(x, y, Units::ScenePixels);
            case Units::SceneUnits:
                return UnitVector(x / View.w * Screen.w, y / View.h * Screen.h, Units::ScenePixels);
            default:
                return UnitVector(0, 0);
            }
        case Units::SceneUnits:
            switch (unit)
            {
            case Units::ViewPercentage:
                return UnitVector((View.w * x) + View.x, (View.h * y) + View.y, Units::SceneUnits);
            case Units::ViewPixels:
                return UnitVector((View.w * (x / Screen.w)) + View.x,
                    (View.h * (y / Screen.h)) + View.y, Units::SceneUnits);
            case Units::ViewUnits:
                return UnitVector(View.x + x, View.y + y, Units::SceneUnits);
            case Units::ScenePixels:
                return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, Units::SceneUnits);
            case Units::SceneUnits:
                return UnitVector(x, y, Units::SceneUnits);
            default:
                return UnitVector(0, 0);
            }
        default:
            return UnitVector(0, 0);
        }
    }

    std::tuple<double, double> UnitVector::unpack() const
    {
        return std::make_tuple(x, y);
    }

    std::ostream& operator<<(std::ostream& os, const UnitVector& m)
    {
        os << "(" << m.x << ", " << m.y << ")::" << UnitsMeta::to_string(m.unit);
        return os;
    }

    UnitVector UnitVector::rotate(double angle, UnitVector zero) const
    {
        const double rad_angle = utils::math::convert_to_radian(angle);
        Matrix2D rot({ std::cos(rad_angle), -std::sin(rad_angle), std::sin(rad_angle),
            std::cos(rad_angle) });
        const UnitVector result = rot.product(*this - zero) + zero;
        return result;
    }
    double UnitVector::distance(const UnitVector& vec) const
    {
        return std::sqrt(std::pow(x - vec.x, 2) + std::pow(y - vec.y, 2));
    }
    double UnitVector::magnitude() const
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }
} // namespace obe::transform
