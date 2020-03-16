#pragma once

#include <tuple>

#include <Transform/UnitStructures.hpp>
#include <Transform/Units.hpp>

namespace obe::Transform
{
    /**
     * \brief Class widely used in the Engine to scale and position elements in
     * a Scene
     * \bind{Vector2}
     */
    class UnitVector
    {
    public:
        /**
         * \nobind
         * \brief Initialize the conversion module (Step 1) by passing the
         *        pointer to the ViewStruct
         */
        static void Init(ViewStruct*&);
        /**
         * \nobind
         * \brief Initialize the conversion module (Step 2) by passing the
         *        values of the ScreenSize
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
        explicit UnitVector(Units unit = Units::SceneUnits);
        /**
         * \brief Constructor (with x, y) of UnitVector
         * \param x x Coordinate of the UnitVector
         * \param y y Coordinate of the UnitVector
         * \param unit Unit of the UnitVector
         */
        UnitVector(double x, double y, Units unit = Units::SceneUnits);

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
         * \brief Adds the values of the the given UnitVector but keeps base
         *        Unit
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
         * \param sub The UnitVector used for the decrement
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

        /**
         * \brief Adds a number to both x and y Coordinates of the UnitVector
         *        and return the result
         * \param add Number to add to the two Coordinates of the UnitVector
         * \return An UnitVector equals to the base UnitVector
         *         plus the "add" number on both Coordinates
         */
        UnitVector operator+(double add) const;
        /**
         * \brief Subtracts a number to both x and y Coordinates of the
         *        UnitVector and return the result
         * \param sub Number to subtract to the two Coordinates of the
         *        UnitVector
         * \return An UnitVector equals to the base UnitVector minus the
         *         "sub" number on both Coordinates
         */
        UnitVector operator-(double sub) const;
        /**
         * \brief Multiplies a number to both x and y Coordinates of the
         *        UnitVector and return the result
         * \param mul Number to multiply to the two Coordinates of the
         *        UnitVector
         * \return An UnitVector equals to the base UnitVector with
         *        "mul" number multiplying both Coordinates
         */
        UnitVector operator*(double mul) const;
        /**
         * \brief Divides a number to both x and y Coordinates of the UnitVector
         *        and return the result
         * \param div Number to divide to the two Coordinates of the UnitVector
         * \return An UnitVector equals to the base UnitVector with "div" number
         *         dividing both Coordinates
         */
        UnitVector operator/(double div) const;

        /**
         * \brief Increments both Coordinates of the UnitVector with a given
         *        number
         * \param add Number used to increment both Coordinates of the
         *        UnitVector
         * \return A reference to the current UnitVector (to chain calls)
         */
        UnitVector& operator+=(double add);
        /**
         * \brief Decrements both Coordinates of the UnitVector with a given
         *        number
         * \param sub Number used to decrement both Coordinates of the
         *        UnitVector
         * \return A reference to the current UnitVector (to chain calls)
         */
        UnitVector& operator-=(double sub);
        /**
         * \brief Multiplies and assigns the UnitVector
         * \param mul Number used to multiply and assign both Coordinates of the
         *        UnitVector
         * \return A reference to the current UnitVector (to chain calls)
         */
        UnitVector& operator*=(double mul);
        /**
         * \brief Divides and assigns the UnitVector
         * \param div Number used to divide and assign both Coordinates of the
         *        UnitVector
         * \return A reference to the current UnitVector (to chain
         *         calls)
         */
        UnitVector& operator/=(double div);

        /**
         * \brief Negates both Coordinates of the UnitVector
         * \return Return an UnitVector equals to the base UnitVector with both
         * Coordinates negated
         */
        UnitVector operator-() const;

        /**
         * \brief Tests equality between two UnitVector
         * \param vec Other UnitVector to test equality
         * \return true if both UnitVector are equals, false otherwise (unit not
         * included)
         */
        bool operator==(const UnitVector& vec) const;
        /**
         * \brief Tests inequality between two UnitVector
         * \param vec Other UnitVector to test inequality
         * \return true if both UnitVector are different, false otherwise (unit
         * not included)
         */
        bool operator!=(const UnitVector& vec) const;

        /**
         * \nobind
         * \brief Return an UnitVector with the converted values (x, y) to the
         *        Unit you want
         * \tparam E enum value from Transform::Units
         * \return A new UnitVector containing the converted values with the new Units
         */
        template <Units E>[[nodiscard]] UnitVector to() const;
        /**
         * \brief Return an UnitVector with the converted values (x, y) to the
         *        Unit you want
         * \param pUnit An enum value from Transform::Units
         * \return A new UnitVector containing the converted values with the new Units
         */
        [[nodiscard]] UnitVector to(Units pUnit) const;

        /**
         * \brief Unpacks the UnitVector to a tuple (can be used with structured
         *        bindings)
         * \return A tuple containing two doubles (x and y)
         */
        [[nodiscard]] std::tuple<double, double> unpack() const;

        /**
         * \brief Display an UnitVector for debug purposes
         * \param os The stream you want to print the UnitVector in
         * \param m The UnitVector you want to print
         * \return The stream passed by reference (To chain calls)
         */
        friend std::ostream& operator<<(std::ostream& os, const UnitVector& m);
        [[nodiscard]] UnitVector rotate(
            double angle, UnitVector zero = UnitVector(0, 0)) const;
        [[nodiscard]] double distance(const UnitVector& vec) const;
    };

    template <> inline UnitVector UnitVector::to<Units::ViewPercentage>() const
    {
        switch (unit)
        {
        case Units::ViewPercentage:
            return UnitVector(x, y, Units::ViewPercentage);
        case Units::ViewPixels:
            return UnitVector(x / Screen.w, y / Screen.h, Units::ViewPercentage);
        case Units::ViewUnits:
            return UnitVector(x / View.w, y / View.h, Units::ViewPercentage);
        case Units::ScenePixels:
            return UnitVector(x / Screen.w - View.x / View.w,
                y / Screen.h - View.y / View.h, Units::ViewPercentage);
        case Units::SceneUnits:
            return UnitVector(
                (x - View.x) / View.w, (y - View.y) / View.h, Units::ViewPercentage);
        default:
            return UnitVector(0, 0);
        }
    }

    template <> inline UnitVector UnitVector::to<Units::ViewPixels>() const
    {
        switch (unit)
        {
        case Units::ViewPercentage:
            return UnitVector(x * Screen.w, y * Screen.h, Units::ViewPixels);
        case Units::ViewPixels:
            return UnitVector(x, y, Units::ViewPixels);
        case Units::ViewUnits:
            return UnitVector(
                x * Screen.w / View.w, y * Screen.h / View.h, Units::ViewPixels);
        case Units::ScenePixels:
            return UnitVector(x - (View.x * Screen.w / View.w),
                y - (View.y * Screen.h / View.h), Units::ViewPixels);
        case Units::SceneUnits:
            return UnitVector((x - View.x) / View.w * Screen.w,
                (y - View.y) / View.h * Screen.h, Units::ViewPixels);
        default:
            return UnitVector(0, 0);
        }
    }

    template <> inline UnitVector UnitVector::to<Units::ViewUnits>() const
    {
        switch (unit)
        {
        case Units::ViewPercentage:
            return UnitVector(x * View.w, y * View.h, Units::ViewUnits);
        case Units::ViewPixels:
            return UnitVector(
                x / Screen.w * View.w, y / Screen.h * View.h, Units::ViewUnits);
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
    }

    template <> inline UnitVector UnitVector::to<Units::ScenePixels>() const
    {
        switch (unit)
        {
        case Units::ViewPercentage:
            return UnitVector(Screen.w * (View.x / View.w + x),
                Screen.h * (View.y / View.h + y), Units::ScenePixels);
        case Units::ViewPixels:
            return UnitVector(Screen.w * View.x / View.w + x,
                Screen.h * View.y / View.h + y, Units::ScenePixels);
        case Units::ViewUnits:
            return UnitVector(Screen.w * (View.x + x) / View.w,
                Screen.h * (View.y + y) / View.h, Units::ScenePixels);
        case Units::ScenePixels:
            return UnitVector(x, y, Units::ScenePixels);
        case Units::SceneUnits:
            return UnitVector(
                x / View.w * Screen.w, y / View.h * Screen.h, Units::ScenePixels);
        default:
            return UnitVector(0, 0);
        }
    }

    template <> inline UnitVector UnitVector::to<Units::SceneUnits>() const
    {
        switch (unit)
        {
        case Units::ViewPercentage:
            return UnitVector(
                (View.w * x) + View.x, (View.h * y) + View.y, Units::SceneUnits);
        case Units::ViewPixels:
            return UnitVector((View.w * (x / Screen.w)) + View.x,
                (View.h * (y / Screen.h)) + View.y, Units::SceneUnits);
        case Units::ViewUnits:
            return UnitVector(View.x + x, View.y + y, Units::SceneUnits);
        case Units::ScenePixels:
            return UnitVector(
                x / Screen.w * View.w, y / Screen.h * View.h, Units::SceneUnits);
        case Units::SceneUnits:
            return UnitVector(x, y, Units::SceneUnits);
        default:
            return UnitVector(0, 0);
        }
    }
} // namespace obe::Transform
