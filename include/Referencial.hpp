#pragma once

#include <string>

namespace obe
{
    namespace Coord
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
        std::string referencialToString(Referencial ref);
        std::ostream& operator<<(std::ostream& os, Referencial m);
    }
}