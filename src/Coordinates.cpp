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

		void UnitVector::set(const Coord::UnitVector& vec)
		{
			Coord::UnitVector pVec = vec.to(unit);
			x = pVec.x;
			y = pVec.y;
		}

		void UnitVector::set(double x, double y)
		{
			this->x = x;
			this->y = y;
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
				case ViewPercentage:
					switch (unit)
					{
					case ViewPercentage:
						return UnitVector(x, y, ViewPercentage);
					case ViewPixels:
						return UnitVector(x / Screen.w, y / Screen.h, ViewPercentage);
					case ViewUnits:
						return UnitVector(x / View.w, y / View.h, ViewPercentage);
					case WorldPixels:
						return UnitVector(x / Screen.w - View.x / View.w, y / Screen.h - View.y / View.h, ViewPercentage);
					case WorldUnits:
						return UnitVector((x - View.x) / View.w, (y - View.y) / View.h, ViewPercentage);
					default:
						return UnitVector(0, 0);
					}
				case ViewPixels:
					switch (unit)
					{
					case ViewPercentage:
						return UnitVector(x * Screen.w, y * Screen.h, ViewPixels);
					case ViewPixels:
						return UnitVector(x, y, ViewPixels);
					case ViewUnits:
						return UnitVector(x * Screen.w / View.w, y * Screen.h / View.h, ViewPixels);
					case WorldPixels:
						return UnitVector(x - (View.x * Screen.w / View.w), y - (View.y * Screen.h / View.h), ViewPixels);
					case WorldUnits:
						return UnitVector((x - View.x) / View.w * Screen.w, (y - View.y) / View.h * Screen.h, ViewPixels);
					default:
						return UnitVector(0, 0);
					}
				case ViewUnits:
					switch (unit)
					{
					case ViewPercentage:
						return UnitVector(x * View.w, y * View.h, ViewUnits);
					case ViewPixels:
						return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, ViewUnits);
					case ViewUnits:
						return UnitVector(x, y, ViewUnits);
					case WorldPixels:
						return UnitVector(x / (Screen.w / View.w) - View.x, y / (Screen.h / View.h) - View.y, ViewUnits);
					case WorldUnits:
						return UnitVector(x - View.x, y - View.y, ViewUnits);
					default:
						return UnitVector(0, 0);
					}
				case WorldPixels:
					switch (unit)
					{
					case ViewPercentage:
						return UnitVector(Screen.w * (View.x / View.w + x), Screen.h * (View.y / View.h + y), WorldPixels);
					case ViewPixels:
						return UnitVector(Screen.w * View.x / View.w + x, Screen.h * View.y / View.h + y, WorldPixels);
					case ViewUnits:
						return UnitVector(Screen.w * (View.x + x) / View.w, Screen.h * (View.y + y) / View.h, WorldPixels);
					case WorldPixels:
						return UnitVector(x, y, WorldPixels);
					case WorldUnits:
						return UnitVector(x / View.w * Screen.w, y / View.h * Screen.h, WorldPixels);
					default:
						return UnitVector(0, 0);
					}
				case WorldUnits:
					switch (unit)
					{
					case ViewPercentage:
						return UnitVector((View.w * x) + View.x, (View.h * y) + View.y, WorldUnits);
					case ViewPixels:
						return UnitVector((View.w * (x / Screen.w)) + View.x, (View.h * (y / Screen.h)) + View.y, WorldUnits);
					case ViewUnits:
						return UnitVector(View.x + x, View.y + y, WorldUnits);
					case WorldPixels:
						return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, WorldUnits);
					case WorldUnits:
						return UnitVector(x, y, WorldUnits);
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
				return ViewPercentage;
			else if (unit == "ViewPixels")
				return ViewPixels;
			else if (unit == "ViewUnits")
				return ViewUnits;
			else if (unit == "WorldPixels")
				return WorldPixels;
			else if (unit == "WorldUnits")
				return WorldUnits;
			else
				return Unknown;
		}

		std::string unitsToString(Units unit)
		{
			switch (unit)
			{
			case ViewPercentage: 
				break;
			case ViewPixels: return "ViewPixels";
			case ViewUnits: return "ViewUnits";
			case WorldPixels: return "WorldPixels";
			case WorldUnits: return "WorldUnits";
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

