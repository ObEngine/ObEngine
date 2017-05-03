#pragma once

#include <iostream>

namespace obe
{
	namespace Coord
	{
		enum Units
		{
			ViewPercentage,
			ViewPixels,
			ViewUnits,
			WorldPercentage,
			WorldPixels,
			WorldUnits
		};

		Units stringToUnits(const std::string& unit);

		struct WorldStruct { double w; double h; };
		struct ViewStruct { double w; double h; double x; double y; };
		struct ScreenStruct { double w; double h; };

		class UnitBasedObject
		{
		protected:
			Units m_unit = WorldUnits;
		public:
			void setWorkingUnit(Units unit);
			Units getWorkingUnit() const;
		};
		
		class UnitVector
		{
			public:
				static void Init(WorldStruct*&);
				static void Init(ViewStruct*&);
				static void Init(const int& width, const int& height);

				static WorldStruct World;
				static ViewStruct View;
				static ScreenStruct Screen;

				UnitVector(const Units& unit = Units::WorldUnits);
				UnitVector(const double& x, const double& y, const Units& unit = Units::WorldUnits);

				double x = 0.0;
				double y = 0.0;
				Units unit;

				void set(const double& x, const double& y);
				void add(const double& x, const double& y);

				UnitVector operator+(const UnitVector& add) const;
				UnitVector operator-(const UnitVector& add) const;
				UnitVector operator*(const UnitVector& add) const;
				UnitVector operator/(const UnitVector& add) const;

				template <Units E> 
				UnitVector to() { return {}; };
				UnitVector to(Units pUnit);
		};

		template <> inline UnitVector UnitVector::to<ViewPercentage>() {
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
		}
		template <> inline UnitVector UnitVector::to<ViewPixels>() {
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
		}
		template <> inline UnitVector UnitVector::to<ViewUnits>() {
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
		}
		template <> inline UnitVector UnitVector::to<WorldPercentage>() {
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
		}
		template <> inline UnitVector UnitVector::to<WorldPixels>() {
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
		}
		template <> inline UnitVector UnitVector::to<WorldUnits>() {
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
		
		std::ostream &operator<<(std::ostream &os, const UnitVector& m);
	}
}
