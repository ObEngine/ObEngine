#include <ostream>

#include <Transform/Matrix2D.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/MathUtils.hpp>
#include <cmath>

namespace obe::Transform
{
    void UnitVector::Init(ViewStruct*& view)
    {
        view = &UnitVector::View;
    }

    void UnitVector::Init(const int width, const int height)
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
        const UnitVector pVec = vec.to(unit);
        x = pVec.x;
        y = pVec.y;
    }

    void UnitVector::set(const double x, const double y)
    {
        this->x = x;
        this->y = y;
    }

    void UnitVector::add(const UnitVector& vec)
    {
        const UnitVector pVec = vec.to(unit);
        x += pVec.x;
        y += pVec.y;
    }

    void UnitVector::add(const double x, const double y)
    {
        this->x += x;
        this->y += y;
    }

    UnitVector UnitVector::operator+(const UnitVector& add) const
    {
        const UnitVector pVec = add.to(unit);
        return UnitVector(x + pVec.x, y + pVec.y, unit);
    }

    UnitVector& UnitVector::operator+=(const UnitVector& add)
    {
        const UnitVector pVec = add.to(unit);
        x += pVec.x;
        y += pVec.y;
        return *this;
    }

    UnitVector UnitVector::operator-(const UnitVector& sub) const
    {
        const UnitVector pVec = sub.to(unit);
        return UnitVector(x - pVec.x, y - pVec.y, unit);
    }

    UnitVector& UnitVector::operator-=(const UnitVector& sub)
    {
        const UnitVector pVec = sub.to(unit);
        x -= pVec.x;
        y -= pVec.y;
        return *this;
    }

    UnitVector UnitVector::operator*(const UnitVector& mul) const
    {
        const UnitVector pVec = mul.to(unit);
        return UnitVector(x * pVec.x, y * pVec.y, unit);
    }

    UnitVector& UnitVector::operator*=(const UnitVector& mul)
    {
        const UnitVector pVec = mul.to(unit);
        x *= pVec.x;
        y *= pVec.y;
        return *this;
    }

    UnitVector UnitVector::operator/(const UnitVector& div) const
    {
        const UnitVector pVec = div.to(unit);
        return UnitVector(x / pVec.x, y / pVec.y, unit);
    }

    UnitVector& UnitVector::operator/=(const UnitVector& div)
    {
        const UnitVector pVec = div.to(unit);
        x /= pVec.x;
        y /= pVec.y;
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
        const UnitVector pVec = vec.to(unit);
        return (x == pVec.x && y == pVec.y);
    }

    bool UnitVector::operator!=(const UnitVector& vec) const
    {
        const UnitVector pVec = vec.to(unit);
        return (x != pVec.x || y != pVec.y);
    }

    UnitVector UnitVector::to(Units pUnit) const
    {
        switch (pUnit)
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
        os << "(" << m.x << ", " << m.y << ")::" << unitsToString(m.unit).c_str();
        return os;
    }

    UnitVector UnitVector::rotate(double angle, UnitVector zero) const
    {
        double rad_angle = Utils::Math::convertToRadian(angle);
        Matrix2D rot({ std::cos(rad_angle), -std::sin(rad_angle), std::sin(rad_angle),
            std::cos(rad_angle) });
        UnitVector result = rot.product(*this - zero) + zero;
        return result;
    }
    double UnitVector::distance(const UnitVector& vec) const
    {
        return std::sqrt(std::pow(x - vec.x, 2) + std::pow(y - vec.y, 2));
    }
} // namespace obe::Transform