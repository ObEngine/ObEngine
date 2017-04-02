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

		struct WorldStruct { double w; double h; };
		struct ViewStruct { double w; double h; double x; double y; };
		struct ScreenStruct { double w; double h; };
		
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
		};

		template <> inline UnitVector UnitVector::to<ViewPercentage>() {
			switch (unit)
			{
			case ViewPercentage:
				return UnitVector(x, y, ViewPercentage);
			case ViewPixels:
				return UnitVector(x * Screen.w, y * Screen.h, ViewPixels);
			case ViewUnits:
				return UnitVector(x * View.w, y * View.h, ViewUnits);
			case WorldPercentage:
				return UnitVector((View.x / World.w) + (View.w * x / World.w), (View.y / World.h) + (View.h * y / World.h), WorldPercentage);
			case WorldPixels:
				return UnitVector(Screen.w * (View.x / View.w + x), Screen.h * (View.y / View.h + y), WorldPixels);
			case WorldUnits:
				return UnitVector(View.x + x * View.w, View.y + y * View.h, WorldUnits);
			default:
				return UnitVector(0, 0);
			}
		}
		template <> inline UnitVector UnitVector::to<ViewPixels>() {
			switch (unit)
			{
			case ViewPercentage:
				return UnitVector(x / Screen.w, y / Screen.h, ViewPercentage);
			case ViewPixels:
				return UnitVector(x, y, ViewPixels);
			case ViewUnits:
				return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, ViewUnits);
			case WorldPercentage:
				return UnitVector((View.x / World.w) + (View.w * x / Screen.w / World.w), (View.y / World.h) + (View.h * y / Screen.h / World.h), WorldPercentage);
			case WorldPixels:
				return UnitVector(Screen.w * (View.x / View.w + x / Screen.w), Screen.h * (View.y / View.h + y / Screen.h), WorldPixels);
			case WorldUnits:
				return UnitVector(View.x + x / Screen.w * View.w, View.y + y / Screen.h * View.h, WorldUnits);
			default:
				return UnitVector(0, 0);
			}
		}
		template <> inline UnitVector UnitVector::to<ViewUnits>() {
			switch (unit)
			{
			case ViewPercentage:
				return UnitVector(x / View.w, y / View.h, ViewPercentage);
			case ViewPixels:
				return UnitVector(x * Screen.w / View.w, y * Screen.h / View.h, ViewPixels);
			case ViewUnits:
				return UnitVector(x, y, ViewUnits);
			case WorldPercentage:
				return UnitVector((View.w + x) / World.w, (View.h + x) / World.h, WorldPercentage);
			case WorldPixels:
				return UnitVector((Screen.w * (View.x + x)) / View.w, (Screen.h * (View.y + x)) / View.h, WorldPixels);
			case WorldUnits:
				return UnitVector(View.x + x, View.y + y, WorldUnits);
			default:
				return UnitVector(0, 0);
			}
		}
		template <> inline UnitVector UnitVector::to<WorldPercentage>() {
			switch (unit)
			{
			case ViewPercentage:
				return UnitVector(0, 0);
			case ViewPixels:
				return UnitVector(0, 0);
			case ViewUnits:
				return UnitVector(0, 0);
			case WorldPercentage:
				return UnitVector(x, y, WorldPercentage);
			case WorldPixels:
				return UnitVector(World.w / View.w * Screen.w * x, World.h / View.h * Screen.h * y);
			case WorldUnits:
				return UnitVector(x * World.w, y * World.h, WorldUnits);
			default:
				return UnitVector(0, 0);
			}
		}
		template <> inline UnitVector UnitVector::to<WorldPixels>() {
			switch (unit)
			{
			case ViewPercentage:
				return UnitVector(0, 0);
			case ViewPixels:
				return UnitVector(0, 0);
			case ViewUnits:
				return UnitVector(0, 0);
			case WorldPercentage:
				return UnitVector(0, 0);
			case WorldPixels:
				return UnitVector(x, y, WorldPixels);
			case WorldUnits:
				//std::cout << "Screen : " << Screen.w << ", " << Screen.h << std::endl << "View : " << View.w << ", " << View.h << std::endl << "Pos : " << x << ", " << y << std::endl;
				return UnitVector(x / View.w * Screen.w, y / View.h * Screen.h, WorldPixels);
			default:
				return UnitVector(0, 0);
			}
		}
		template <> inline UnitVector UnitVector::to<WorldUnits>() {
			switch (unit)
			{
			case ViewPercentage:
				return UnitVector(0, 0);
			case ViewPixels:
				return UnitVector(0, 0);
			case ViewUnits:
				return UnitVector(0, 0);
			case WorldPercentage:
				return UnitVector(x / World.w, y / World.h, WorldPercentage);
			case WorldPixels:
				return UnitVector(Screen.w * x / View.w, Screen.h * y / View.h, WorldPixels);
			case WorldUnits:
				return UnitVector(x, y, WorldUnits);
			default:
				return UnitVector(0, 0);
			}
		}
		
		std::ostream &operator<<(std::ostream &os, const UnitVector& m);
	}
}