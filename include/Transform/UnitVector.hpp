#pragma once

#include <Transform/Units.hpp>
#include <Transform/UnitStructures.hpp>

namespace obe
{
    namespace Transform
    {
        /**
         * \brief Class widely used in the Engine to scale and position elements in a Scene
         */
        class UnitVector
        {
        public:
            static void Init(ViewStruct*&);
            static void Init(int width, int height);

            static ViewStruct View;
            static ScreenStruct Screen;

            UnitVector(Units unit = Units::WorldUnits);
            UnitVector(double x, double y, Units unit = Units::WorldUnits);

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

            /**
             * \brief Return an UnitVector with the converted values (x, y) to the Unit you want
             * \tparam E An enum value from Coord::Units
             * \return A new UnitVector containing the converted values with the new Units
             */
            template <Units E>
            UnitVector to() const { return {}; };
            /**
             * \brief Return an UnitVector with the converted values (x, y) to the Unit you want
             * \param pUnit An enum value from Coord::Units
             * \return A new UnitVector containing the converted values with the new Units
             */
            UnitVector to(Units pUnit) const;
        };

        template <>
        inline UnitVector UnitVector::to<Units::ViewPercentage>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<Units::ViewPixels>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<Units::ViewUnits>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<Units::WorldPixels>() const
        {
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
        }

        template <>
        inline UnitVector UnitVector::to<Units::WorldUnits>() const
        {
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

        /**
         * \brief Display an UnitVector for debug purposes
         * \param os The stream you want to print the UnitVector in
         * \param m The UnitVector you want to print
         * \return The stream passed by reference (To chain calls)
         */
        std::ostream& operator<<(std::ostream& os, const UnitVector& m);
    }
}