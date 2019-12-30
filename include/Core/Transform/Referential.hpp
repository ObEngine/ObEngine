#pragma once

#include <string>

#include <Transform/UnitVector.hpp>

namespace obe::Transform
{
    /**
     * \brief Set or Get Position using Referentials
     */
    class Referential
    {
    private:
        double m_refX;
        double m_refY;

    public:
        enum class Axis
        {
            Horizontal,
            Vertical,
            Both
        };

        Referential();
        Referential(double refX, double refY);

        bool operator==(const Referential& ref) const;
        bool operator!=(const Referential& ref) const;

        /**
         * \brief Get the opposite Referential in a Rect
         * \return The opposite of the given Referential (BottomRight => TopLeft
         * for example)
         */
        Referential flip(Axis axis = Axis::Both) const;
        /**
         * \brief Get if the Referential is on the left side of a normalized
         * Rect \return true if Referential is on left side, false otherwise
         */
        bool isOnLeftSide() const;
        /**
         * \brief Get if the Referential is on the right side of a normalized
         * Rect \return true if Referential is on right side, false otherwise
         */
        bool isOnRightSide() const;
        /**
         * \brief Get if the Referential is on the top side of a normalized Rect
         * \return true if Referential is on top side, false otherwise
         */
        bool isOnTopSide() const;
        /**
         * \brief Get if the Referential is on the bottom side of a normalized
         * Rect \return true if Referential is on bottom side, false otherwise
         */
        bool isOnBottomSide() const;
        /**
         * \brief Get if the Referential is on a corner of a normalized Rect
         * \param ref Referential you want to check
         * \return true if Referential is on a corner, false otherwise
         */
        bool isOnCorner() const;
        /**
         * \brief Get if the Referential is on a side of a normalized Rect
         * \return true if Referential is on a side, false otherwise
         */
        bool isOnSide() const;
        /**
         * \brief Get if the Referential is one of the 9 known referentials
         * (TopLeft, Top, TopRight, Left, Center, Right, BottomLeft, Bottom,
         * BottomRight) \return true is the Referential is one of the 9 known
         * referentials, false otherwise
         */
        bool isKnown() const;
        /**
         * \brief Get the normalized position of a Referential in a Rect
         * (-1 : Left / Top, 0 = Center, 1 = Right / Bottom)
         * \return The normalized position of a Referential in a Rect
         */
        UnitVector getOffset() const;

        /**
         * \brief Get the name of a Referential in std::string form
         * \param format Format (fmt) of the string returned
         * \return The name of the Referential in std::string form
         */
        std::string toString(
            const std::string& format = "Referential<{}>") const;
        /**
         * \brief Gets a Referential based on its name
         * \param ref Name of the Referential
         * \return The Referential enum value corresponding to the given name
         */
        static Referential FromString(const std::string& ref);
        /**
         * \brief Overload of operator<< to print Referentials
         * \param os The stream you want to print the Referential
         * \param m The Referential you want to print
         * \return The given stream to chain calls
         */
        friend std::ostream& operator<<(std::ostream& os, Referential m);
        /**
         * \brief Referential TopLeft
         * \code
         * Coeff : w * 0, h * 0
         *
         * o | x | x
         * ----------
         * x | x | x
         * ----------
         * x | x | x
         * \endcode
         */
        static Referential TopLeft;
        /**
         * \brief Referential Top
         * \code
         * Coeff : w * 0.5, h * 1
         *
         * x | o | x
         * ----------
         * x | x | x
         * ----------
         * x | x | x
         * \endcode
         */
        static Referential Top;
        /**
         * \brief Referential TopRight
         * \code
         * Coeff : w * 1, h * 0
         *
         * x | x | o
         * ----------
         * x | x | x
         * ----------
         * x | x | x
         * \endcode
         */
        static Referential TopRight;
        /**
         * \brief Referential Left
         * \code
         * Coeff : w * 0, h * 0.5
         *
         * x | x | x
         * ----------
         * o | x | x
         * ----------
         * x | x | x
         * \endcode
         */
        static Referential Left;
        /**
         * \brief Referential Center
         * \code
         * Coeff : w * 0.5, h * 0.5
         *
         * x | x | x
         * ----------
         * x | o | x
         * ----------
         * x | x | x
         * \endcode
         */
        static Referential Center;
        /**
         * \brief Referential Right
         * \code
         * Coeff : w * 1, h * 0.5
         *
         * x | x | x
         * ----------
         * x | x | o
         * ----------
         * x | x | x
         * \endcode
         */
        static Referential Right;
        /**
         * \brief Referential BottomLeft
         * \code
         * Coeff : w * 0, h * 1
         *
         * x | x | x
         * ----------
         * x | x | x
         * ----------
         * o | x | x
         * \endcode
         */
        static Referential BottomLeft;
        /**
         * \brief Referential Bottom
         * \code
         * Coeff : w * 0.5, h * 1
         *
         * x | x | x
         * ----------
         * x | x | x
         * ----------
         * x | o | x
         * \endcode
         */
        static Referential Bottom;
        /**
         * \brief Referential BottomRight
         * \code
         * Coeff : w * 1, h * 1
         *
         * x | x | x
         * ----------
         * x | x | x
         * ----------
         * x | x | o
         * \endcode
         */
        static Referential BottomRight;
        static std::array<Referential, 9> Referentials;
    };
} // namespace obe::Transform
