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
            /**
             * \brief Initialize the conversion module (Step 1) by passing the pointer to the ViewStruct
             */
            static void Init(ViewStruct*&);
            /**
             * \brief Initialize the conversion module (Step 2) by passing the values of the ScreenSize
             * \param width Width of the screen
             * \param height Height of the screen
             */
            static void Init(int width, int height);

            /**
             * \brief Struct used for UnitVector conversions, do not modify !
             */
            static ViewStruct View;
            /**
             * \brief Struct used for UnitVector conversions, do not modify !
             */
            static ScreenStruct Screen;

            /**
             * \brief Constructor of UnitVector
             * \param unit Unit of the UnitVector
             */
            UnitVector(Units unit = Units::WorldUnits);
            /**
             * \brief Constructor (with x, y) of UnitVector
             * \param x x Coordinate of the UnitVector
             * \param y y Coordinate of the UnitVector
             * \param unit Unit of the UnitVector
             */
            UnitVector(double x, double y, Units unit = Units::WorldUnits);

            /**
             * \brief x Coordinate of the UnitVector (related to Unit)
             */
            double x = 0.0;
            /**
             * \brief y Coordinate of the UnitVector (related to Unit)
             */
            double y = 0.0;
            /**
             * \brief Unit of the UnitVector
             */
            Units unit;

            /**
             * \brief Set the values of the given UnitVector but keeps base Unit
             * \param vec UnitVector containing the new values
             */
            void set(const UnitVector& vec);
            /**
             * \brief Set the new given values but keeps base Unit
             * \param x New x Coordinate
             * \param y New y Coordinate
             */
            void set(double x, double y);
            /**
			 * \brief Adds the values of the the given UnitVector but keeps base Unit
			 * \param vec UnitVector containing the values to add
			 */
            void add(const UnitVector& vec);
            /**
             * \brief Add the new given values but keeps base Unit
             * \param x x Coordinate to add
             * \param y y Coordinate to add
             */
            void add(double x, double y);

            /**
             * \brief Adds two UnitVector
             * \param add the other UnitVector to add
             * \return The sum of the two UnitVector
             */
            UnitVector operator+(const UnitVector& add) const;
            /**
             * \brief Increments the UnitVector
             * \param add The UnitVector used for the incrementation
             * \return A Reference to the current UnitVector (to chain calls)
             */
            UnitVector& operator+=(const UnitVector& add);
            /**
            * \brief Subtracts two UnitVector
            * \param sub the other UnitVector to subtract
            * \return The difference of the two UnitVector
            */
            UnitVector operator-(const UnitVector& sub) const;
            /**
            * \brief Decrements the UnitVector
            * \param sub The UnitVector used for the decrementation
            * \return A Reference to the current UnitVector (to chain calls)
            */
            UnitVector& operator-=(const UnitVector& sub);
            /**
            * \brief Multiply two UnitVector
            * \param mul the other UnitVector to multiply
            * \return The product of the two UnitVector
            */
            UnitVector operator*(const UnitVector& mul) const;
            /**
            * \brief Multiply and assign the UnitVector
            * \param mul The UnitVector used for the multiplication
            * \return A Reference to the current UnitVector (to chain calls)
            */
            UnitVector& operator*=(const UnitVector& mul);
            /**
            * \brief Divides two UnitVector
            * \param div the other UnitVector to divide
            * \return The quotient of the two UnitVector
            */
            UnitVector operator/(const UnitVector& div) const;
            /**
            * \brief Divides and assign the UnitVector
            * \param div The UnitVector used for the division
            * \return A Reference to the current UnitVector (to chain calls)
            */
            UnitVector& operator/=(const UnitVector& div);

            UnitVector operator*(double mul) const;

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
