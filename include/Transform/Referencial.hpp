#pragma once

#include <string>

#include <Transform/UnitVector.hpp>

namespace obe
{
    namespace Transform
    {
        /**
        * \brief Set or Get Position using Referencials
        */
        enum class Referencial
        {
            /**
            * \brief Referencial TopLeft
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
            TopLeft,
            /**
            * \brief Referencial Top
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
            Top,
            /**
            * \brief Referencial TopRight
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
            TopRight,
            /**
            * \brief Referencial Left
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
            Left,
            /**
            * \brief Referencial Center
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
            Center,
            /**
            * \brief Referencial Right
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
            Right,
            /**
            * \brief Referencial BottomLeft
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
            BottomLeft,
            /**
            * \brief Referencial Bottom
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
            Bottom,
            /**
            * \brief Referencial BottomRight
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
            BottomRight,
        };

        /**
         * \brief Get the opposite Referencial in a Rect
         * \param ref Referencial you want to get opposite
         * \return The opposite of the given Referencial (BottomRight => TopLeft for example)
         */
        Referencial reverseReferencial(Referencial ref);
        /**
         * \brief Get the horizontal opposite Referencial in a Rect
         * \param ref Referencial you want to get the horizontal opposite
         * \return The horizontal opposite of the given Referencial (TopLeft => TopRight for example)
         */
        Referencial horizontallyReverseReferencial(Referencial ref);
        /**
        * \brief Get the vertical opposite Referencial in a Rect
        * \param ref Referencial you want to get the vertical opposite
        * \return The vertical opposite of the given Referencial (TopLeft => BottomLeft for example)
        */
        Referencial verticallyReverseReferencial(Referencial ref);
        /**
         * \brief Get if the Referencial is on the left side of a normalized Rect
         * \param ref Referencial you want to check
         * \return true if Referencial is on left side, false otherwise
         */
        bool isOnLeftSide(Referencial ref);
        /**
        * \brief Get if the Referencial is on the right side of a normalized Rect
        * \param ref Referencial you want to check
        * \return true if Referencial is on right side, false otherwise
        */
        bool isOnRightSide(Referencial ref);
        /**
        * \brief Get if the Referencial is on the top side of a normalized Rect
        * \param ref Referencial you want to check
        * \return true if Referencial is on top side, false otherwise
        */
        bool isOnTopSide(Referencial ref);
        /**
        * \brief Get if the Referencial is on the bottom side of a normalized Rect
        * \param ref Referencial you want to check
        * \return true if Referencial is on bottom side, false otherwise
        */
        bool isOnBottomSide(Referencial ref);
        /**
        * \brief Get if the Referencial is on a corner of a normalized Rect
        * \param ref Referencial you want to check
        * \return true if Referencial is on a corner, false otherwise
        */
        bool isOnCorner(Referencial ref);
        /**
        * \brief Get if the Referencial is on a side of a normalized Rect
        * \param ref Referencial you want to check
        * \return true if Referencial is on a side, false otherwise
        */
        bool isOnSide(Referencial ref);
        /**
         * \brief Get the normalized position of a Referencial in a Rect (-1 : Left / Top, 0 = Center, 1 = Right / Bottom)
         * \param ref Referencial you want to get the normalized Position
         * \return The normalized position of a Referencial in a Rect
         */
        UnitVector getReferencialOffset(Referencial ref);
        /**
         * \brief Get the name of a Referencial in std::string form
         * \param ref Referencial you want to get the name
         * \return The name of the Referencial in std::string form
         */
        std::string referencialToString(Referencial ref);
        /**
         * \brief Gets a Referencial based on its name
         * \param ref Name of the Referencial
         * \return The Referencial enum value corresponding to the given name
         */
        Referencial stringToReferencial(const std::string& ref);
        /**
         * \brief Overload of operator<< to print Referencials
         * \param os The stream you want to print the Referencial
         * \param m The Referencial you want to print
         * \return The given stream to chain calls
         */
        std::ostream& operator<<(std::ostream& os, Referencial m);
    }
}
