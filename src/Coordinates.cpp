#include "Coordinates.hpp"

namespace obe
{
	namespace Coord
	{
		WorldStruct UnitVector::World;
		ViewStruct UnitVector::View;
		ScreenStruct UnitVector::Screen;

		void UnitVector::Init(WorldStruct*& world)
		{
			world = &UnitVector::World;
		}

		void UnitVector::Init(ViewStruct*& view)
		{
			view = &UnitVector::View;
		}

		void UnitVector::Init(const int& width, const int& height)
		{
			Screen.w = width;
			Screen.h = height;
		}

		UnitVector::UnitVector(const Units& unit)
		{
			this->unit = unit;
		}

		UnitVector::UnitVector(const double& x, const double& y, const Units & unit)
		{
			this->x = x;
			this->y = y;
			this->unit = unit;
		}

		void UnitVector::set(const double& x, const double& y)
		{
			this->x = x;
			this->y = y;
		}

		void UnitVector::add(const double& x, const double& y)
		{
			this->x += x;
			this->y += y;
		}

		UnitVector UnitVector::operator+(const UnitVector& add) const
		{
			return UnitVector(x + add.x, y + add.y);
		}

		UnitVector UnitVector::operator-(const UnitVector& add) const
		{
			return UnitVector(x - add.x, y - add.y);
		}

		UnitVector UnitVector::operator*(const UnitVector& add) const
		{
			return UnitVector(x * add.x, y * add.y);
		}

		UnitVector UnitVector::operator/(const UnitVector& add) const
		{
			return UnitVector(x / add.x, y / add.y);
		}

		Units stringToUnits(const std::string& unit)
		{
			if (unit == "ViewPercentage")
				return ViewPercentage;
			if (unit == "ViewPixels")
				return ViewPixels;
			if (unit == "ViewUnits")
				return ViewUnits;
			if (unit == "WorldPercentage")
				return WorldPercentage;
			if (unit == "WorldPixels")
				return WorldPixels;
			if (unit == "WorldUnits")
				return WorldUnits;
		}

		std::ostream& operator<<(std::ostream& os, const UnitVector& m)
		{
			os << "(" << m.x << ", " << m.y << ")::" << m.unit;
			return os;
		}
	}
}

