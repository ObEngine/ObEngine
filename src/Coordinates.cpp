#include "Coordinates.hpp"

namespace obe
{
    namespace Coord
    {
        ViewStruct UnitVector::View;
        ScreenStruct UnitVector::Screen;

        void UnitBasedObject::setWorkingUnit(Units unit)
        {
            m_unit = unit;
        }

        Units UnitBasedObject::getWorkingUnit() const
        {
            return m_unit;
        }

        void UnitVector::Init(ViewStruct*& view)
        {
            view = &UnitVector::View;
        }

        void UnitVector::Init(int width, int height)
        {
            Screen.w = width;
            Screen.h = height;
        }

        UnitVector::UnitVector(Units unit)
        {
            this->unit = unit;
        }

        UnitVector::UnitVector(double x, double y, Units unit)
        {
            this->x = x;
            this->y = y;
            this->unit = unit;
        }

        void UnitVector::set(const UnitVector& vec)
        {
            UnitVector pVec = vec.to(unit);
            x = pVec.x;
            y = pVec.y;
        }

        void UnitVector::set(double x, double y)
        {
            this->x = x;
            this->y = y;
        }

	    void UnitVector::add(const UnitVector& vec)
	    {
			UnitVector pVec = vec.to(unit);
			x += pVec.x;
			y += pVec.y;
	    }

	    void UnitVector::add(double x, double y)
        {
            this->x += x;
            this->y += y;
        }

        UnitVector UnitVector::operator+(const UnitVector& add) const
        {
            UnitVector pVec = add.to(unit);
            return UnitVector(x + pVec.x, y + pVec.y, unit);
        }

        UnitVector& UnitVector::operator+=(const UnitVector& add)
        {
            UnitVector pVec = add.to(unit);
            x += pVec.x;
            y += pVec.y;
            return *this;
        }

        UnitVector UnitVector::operator-(const UnitVector& add) const
        {
            UnitVector pVec = add.to(unit);
            return UnitVector(x - pVec.x, y - pVec.y, unit);
        }

        UnitVector& UnitVector::operator-=(const UnitVector& add)
        {
            UnitVector pVec = add.to(unit);
            x -= pVec.x;
            y -= pVec.y;
            return *this;
        }

        UnitVector UnitVector::operator*(const UnitVector& add) const
        {
            UnitVector pVec = add.to(unit);
            return UnitVector(x * pVec.x, y * pVec.y, unit);
        }

        UnitVector& UnitVector::operator*=(const UnitVector& add)
        {
            UnitVector pVec = add.to(unit);
            x *= pVec.x;
            y *= pVec.y;
            return *this;
        }

        UnitVector UnitVector::operator/(const UnitVector& add) const
        {
            UnitVector pVec = add.to(unit);
            return UnitVector(x / pVec.x, y / pVec.y, unit);
        }

        UnitVector& UnitVector::operator/=(const UnitVector& add)
        {
            UnitVector pVec = add.to(unit);
            x /= pVec.x;
            y /= pVec.y;
            return *this;
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
                case Units::WorldPixels:
                    return UnitVector(x / Screen.w - View.x / View.w, y / Screen.h - View.y / View.h, Units::ViewPercentage);
                case Units::WorldUnits:
                    return UnitVector((x - View.x) / View.w, (y - View.y) / View.h, Units::ViewPercentage);
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
                case Units::WorldPixels:
                    return UnitVector(x - (View.x * Screen.w / View.w), y - (View.y * Screen.h / View.h), Units::ViewPixels);
                case Units::WorldUnits:
                    return UnitVector((x - View.x) / View.w * Screen.w, (y - View.y) / View.h * Screen.h, Units::ViewPixels);
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
                case Units::WorldPixels:
                    return UnitVector(x / (Screen.w / View.w) - View.x, y / (Screen.h / View.h) - View.y, Units::ViewUnits);
                case Units::WorldUnits:
                    return UnitVector(x - View.x, y - View.y, Units::ViewUnits);
                default:
                    return UnitVector(0, 0);
                }
            case Units::WorldPixels:
                switch (unit)
                {
                case Units::ViewPercentage:
                    return UnitVector(Screen.w * (View.x / View.w + x), Screen.h * (View.y / View.h + y), Units::WorldPixels);
                case Units::ViewPixels:
                    return UnitVector(Screen.w * View.x / View.w + x, Screen.h * View.y / View.h + y, Units::WorldPixels);
                case Units::ViewUnits:
                    return UnitVector(Screen.w * (View.x + x) / View.w, Screen.h * (View.y + y) / View.h, Units::WorldPixels);
                case Units::WorldPixels:
                    return UnitVector(x, y, Units::WorldPixels);
                case Units::WorldUnits:
                    return UnitVector(x / View.w * Screen.w, y / View.h * Screen.h, Units::WorldPixels);
                default:
                    return UnitVector(0, 0);
                }
            case Units::WorldUnits:
                switch (unit)
                {
                case Units::ViewPercentage:
                    return UnitVector((View.w * x) + View.x, (View.h * y) + View.y, Units::WorldUnits);
                case Units::ViewPixels:
                    return UnitVector((View.w * (x / Screen.w)) + View.x, (View.h * (y / Screen.h)) + View.y, Units::WorldUnits);
                case Units::ViewUnits:
                    return UnitVector(View.x + x, View.y + y, Units::WorldUnits);
                case Units::WorldPixels:
                    return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, Units::WorldUnits);
                case Units::WorldUnits:
                    return UnitVector(x, y, Units::WorldUnits);
                default:
                    return UnitVector(0, 0);
                }
            }
        }

        ProtectedUnitVector::ProtectedUnitVector(const Units& unit)
        {
            this->unit = unit;
        }

        ProtectedUnitVector::ProtectedUnitVector(const double& x, const double& y, const Units& unit)
        {
            this->x = x;
            this->y = y;
            this->unit = unit;
        }

        Units stringToUnits(const std::string& unit)
        {
            if (unit == "ViewPercentage")
                return Units::ViewPercentage;
            if (unit == "ViewPixels")
                return Units::ViewPixels;
            if (unit == "ViewUnits")
                return Units::ViewUnits;
            if (unit == "WorldPixels")
                return Units::WorldPixels;
            if (unit == "WorldUnits")
                return Units::WorldUnits;
            else
                return Units::Unknown;
        }

        std::string unitsToString(Units unit)
        {
            switch (unit)
            {
            case Units::ViewPercentage: return "ViewPercentage0";
            case Units::ViewPixels: return "ViewPixels";
            case Units::ViewUnits: return "ViewUnits";
            case Units::WorldPixels: return "WorldPixels";
            case Units::WorldUnits: return "WorldUnits";
            default: return "Error";
            }
            return "Error";
        }

        std::ostream& operator<<(std::ostream& os, const UnitVector& m)
        {
            os << "(" << m.x << ", " << m.y << ")::" << unitsToString(m.unit).c_str();
            return os;
        }
    }
}
