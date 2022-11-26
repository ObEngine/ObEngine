#pragma once

#include <tuple>

namespace obe::animation
{
    template <class T>
    class TweenImpl;
}

namespace obe::transform
{
    /**
     * \brief Class widely used in the Engine to scale and position elements in
     * a Scene
     * TODO: /bind{Vector2}
     */
    class Vector2
    {
        friend class animation::TweenImpl<Vector2>;

    public:
        /**
         * \brief Constructor of Vector2
         * \param unit Unit of the Vector2
         */
        Vector2() = default;
        /**
         * \brief Constructor (with x, y) of Vector2
         * \param x x Coordinate of the Vector2
         * \param y y Coordinate of the Vector2
         * \param unit Unit of the Vector2
         */
        Vector2(double x, double y);
        Vector2(const Vector2& copy);
        Vector2& operator=(const Vector2& copy);

        /**
         * \brief x Coordinate of the Vector2 (related to Unit)
         */
        double x = 0.0;
        /**
         * \brief y Coordinate of the Vector2 (related to Unit)
         */
        double y = 0.0;

        /**
         * \brief Adds two Vector2
         * \param add the other Vector2 to add
         * \return The sum of the two Vector2
         */
        Vector2 operator+(const Vector2& add) const;
        /**
         * \brief Increments the Vector2
         * \param add The Vector2 used for the incrementation
         * \return A Reference to the current Vector2 (to chain calls)
         */
        Vector2& operator+=(const Vector2& add);
        /**
         * \brief Subtracts two Vector2
         * \param sub the other Vector2 to subtract
         * \return The difference of the two Vector2
         */
        Vector2 operator-(const Vector2& sub) const;
        /**
         * \brief Decrements the Vector2
         * \param sub The Vector2 used for the decrement
         * \return A Reference to the current Vector2 (to chain calls)
         */
        Vector2& operator-=(const Vector2& sub);
        /**
         * \brief Multiply two Vector2
         * \param mul the other Vector2 to multiply
         * \return The product of the two Vector2
         */
        Vector2 operator*(const Vector2& mul) const;
        /**
         * \brief Multiply and assign the Vector2
         * \param mul The Vector2 used for the multiplication
         * \return A Reference to the current Vector2 (to chain calls)
         */
        Vector2& operator*=(const Vector2& mul);
        /**
         * \brief Divides two Vector2
         * \param div the other Vector2 to divide
         * \return The quotient of the two Vector2
         */
        Vector2 operator/(const Vector2& div) const;
        /**
         * \brief Divides and assign the Vector2
         * \param div The Vector2 used for the division
         * \return A Reference to the current Vector2 (to chain calls)
         */
        Vector2& operator/=(const Vector2& div);

        /**
         * \brief Adds a number to both x and y Coordinates of the Vector2
         *        and return the result
         * \param add Number to add to the two Coordinates of the Vector2
         * \return An Vector2 equals to the base Vector2
         *         plus the "add" number on both Coordinates
         */
        Vector2 operator+(double add) const;
        /**
         * \brief Subtracts a number to both x and y Coordinates of the
         *        Vector2 and return the result
         * \param sub Number to subtract to the two Coordinates of the
         *        Vector2
         * \return An Vector2 equals to the base Vector2 minus the
         *         "sub" number on both Coordinates
         */
        Vector2 operator-(double sub) const;
        /**
         * \brief Multiplies a number to both x and y Coordinates of the
         *        Vector2 and return the result
         * \param mul Number to multiply to the two Coordinates of the
         *        Vector2
         * \return An Vector2 equals to the base Vector2 with
         *        "mul" number multiplying both Coordinates
         */
        Vector2 operator*(double mul) const;
        /**
         * \brief Divides a number to both x and y Coordinates of the Vector2
         *        and return the result
         * \param div Number to divide to the two Coordinates of the Vector2
         * \return An Vector2 equals to the base Vector2 with "div" number
         *         dividing both Coordinates
         */
        Vector2 operator/(double div) const;

        /**
         * \brief Increments both Coordinates of the Vector2 with a given
         *        number
         * \param add Number used to increment both Coordinates of the
         *        Vector2
         * \return A reference to the current Vector2 (to chain calls)
         */
        Vector2& operator+=(double add);
        /**
         * \brief Decrements both Coordinates of the Vector2 with a given
         *        number
         * \param sub Number used to decrement both Coordinates of the
         *        Vector2
         * \return A reference to the current Vector2 (to chain calls)
         */
        Vector2& operator-=(double sub);
        /**
         * \brief Multiplies and assigns the Vector2
         * \param mul Number used to multiply and assign both Coordinates of the
         *        Vector2
         * \return A reference to the current Vector2 (to chain calls)
         */
        Vector2& operator*=(double mul);
        /**
         * \brief Divides and assigns the Vector2
         * \param div Number used to divide and assign both Coordinates of the
         *        Vector2
         * \return A reference to the current Vector2 (to chain
         *         calls)
         */
        Vector2& operator/=(double div);

        /**
         * \brief Negates both Coordinates of the Vector2
         * \return Return an Vector2 equals to the base Vector2 with both
         * Coordinates negated
         */
        Vector2 operator-() const;

        /**
         * \brief Tests equality between two Vector2
         * \param vec Other Vector2 to test equality
         * \return true if both Vector2 are equals, false otherwise (unit not
         * included)
         */
        bool operator==(const Vector2& vec) const;
        /**
         * \brief Tests inequality between two Vector2
         * \param vec Other Vector2 to test inequality
         * \return true if both Vector2 are different, false otherwise (unit
         * not included)
         */
        bool operator!=(const Vector2& vec) const;

        /**
         * \brief Unpacks the Vector2 to a tuple (can be used with structured
         *        bindings)
         * \return A tuple containing two doubles (x and y)
         */
        [[nodiscard]] std::tuple<double, double> unpack() const;

        /**
         * \brief Display an Vector2 for debug purposes
         * \param os The stream you want to print the Vector2 in
         * \param m The Vector2 you want to print
         * \return The stream passed by reference (To chain calls)
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector2& m);
        [[nodiscard]] Vector2 rotate(double angle, Vector2 zero = Vector2(0, 0)) const;
        [[nodiscard]] double distance(const Vector2& vec) const;
        /**
         * \brief Return the length of the Vector2
         */
        [[nodiscard]] double magnitude() const;
    };
} // namespace obe::transform
