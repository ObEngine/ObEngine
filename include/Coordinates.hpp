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
            WorldPixels,
            WorldUnits,
            Unknown
        };

        Units stringToUnits(const std::string& unit);
        std::string unitsToString(Units unit);

        struct ViewStruct
        {
            double w;
            double h;
            double x;
            double y;
        };

        struct ScreenStruct
        {
            double w;
            double h;
        };

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
            static void Init(ViewStruct*&);
            static void Init(int width, int height);

            static ViewStruct View;
            static ScreenStruct Screen;

            UnitVector(Units unit = WorldUnits);
            UnitVector(double x, double y, Units unit = WorldUnits);

            double x = 0.0;
            double y = 0.0;
            Units unit;

            void set(const UnitVector& vec);
            void set(double x, double y);
			void add(const UnitVector& vec);
            void add(double x, double y);

            UnitVector operator+(const UnitVector& add) const;
            UnitVector& operator+=(const UnitVector& add);
            UnitVector operator-(const UnitVector& add) const;
            UnitVector& operator-=(const UnitVector& add);
            UnitVector operator*(const UnitVector& add) const;
            UnitVector& operator*=(const UnitVector& add);
            UnitVector operator/(const UnitVector& add) const;
            UnitVector& operator/=(const UnitVector& add);

            template <Units E>
            UnitVector to() const { return {}; };
            UnitVector to(Units pUnit) const;
        };

        class ProtectedUnitVector : public UnitVector
        {
        protected:
            Units unit;
        public:
            ProtectedUnitVector(const Units& unit = WorldUnits);
            ProtectedUnitVector(const double& x, const double& y, const Units& unit = WorldUnits);
        };

        template <>
        inline UnitVector UnitVector::to<ViewPercentage>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<ViewPixels>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<ViewUnits>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<WorldPixels>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<WorldUnits>() const
        {
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

        std::ostream& operator<<(std::ostream& os, const UnitVector& m);
    }
}
