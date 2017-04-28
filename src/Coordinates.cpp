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

		UnitVector UnitVector::to(Units pUnit)
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
					case WorldPercentage:
						return UnitVector((x * World.w - View.x) / View.w, ((y * World.h) - View.y) / View.h, ViewPercentage);
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
					case WorldPercentage:
						return UnitVector(Screen.w * (World.w * x / View.w - View.x / View.w), Screen.h * (World.h * y / View.h - View.y / View.h), ViewPixels);
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
					case WorldPercentage:
						return UnitVector(x * World.w - View.x, y * World.h - View.y, ViewUnits);
					case WorldPixels:
						return UnitVector(x / (Screen.w / View.w) - View.x, y / (Screen.h / View.h) - View.y, ViewUnits);
					case WorldUnits:
						return UnitVector(x - View.x, y - View.y, ViewUnits);
					default:
						return UnitVector(0, 0);
					}
				case WorldPercentage:
					switch (unit)
					{
					case ViewPercentage:
						return UnitVector(((View.w * x) + View.x) / World.w, ((View.h * y) + View.y) / World.h, WorldPercentage);
					case ViewPixels:
						return UnitVector(((View.w * (x / Screen.w)) + View.x) / World.w, ((View.h * (y / Screen.h)) + View.y) / World.h, WorldPercentage);
					case ViewUnits:
						return UnitVector((View.x + x) / World.w, (View.y + y) / World.h, WorldPercentage);
					case WorldPercentage:
						return UnitVector(x, y, WorldPercentage);
					case WorldPixels:
						return UnitVector(x / Screen.w * View.w / World.w, y / Screen.h * View.h / World.h, WorldPercentage);
					case WorldUnits:
						return UnitVector(x / World.w, y / World.h, WorldPercentage);
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
					case WorldPercentage:
						return UnitVector(x * World.w * (Screen.w / View.w), y * World.h * (Screen.h / View.h), WorldPixels);
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
					case WorldPercentage:
						return UnitVector(x * World.w, y * World.h, WorldUnits);
					case WorldPixels:
						return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, WorldUnits);
					case WorldUnits:
						return UnitVector(x, y, WorldUnits);
					default:
						return UnitVector(0, 0);
					}
			}
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

