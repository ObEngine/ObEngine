#pragma once

#include <string>

#include <Transform/UnitVector.hpp>

namespace obe::Transform
{
    /**
    * \brief Set or Get Position using Referentials
    */
    enum class Referential
    {
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
        TopLeft,
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
        Top,
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
        TopRight,
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
        Left,
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
        Center,
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
        Right,
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
        BottomLeft,
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
        Bottom,
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
        BottomRight,
    };

    /**
    * \brief Get the opposite Referential in a Rect
    * \param ref Referential you want to get opposite
    * \return The opposite of the given Referential (BottomRight => TopLeft for example)
    */
    Referential reverseReferential(Referential ref);
    /**
    * \brief Get the horizontal opposite Referential in a Rect
    * \param ref Referential you want to get the horizontal opposite
    * \return The horizontal opposite of the given Referential (TopLeft => TopRight for example)
    */
    Referential horizontallyReverseReferential(Referential ref);
    /**
    * \brief Get the vertical opposite Referential in a Rect
    * \param ref Referential you want to get the vertical opposite
    * \return The vertical opposite of the given Referential (TopLeft => BottomLeft for example)
    */
    Referential verticallyReverseReferential(Referential ref);
    /**
    * \brief Get if the Referential is on the left side of a normalized Rect
    * \param ref Referential you want to check
    * \return true if Referential is on left side, false otherwise
    */
    bool isOnLeftSide(Referential ref);
    /**
    * \brief Get if the Referential is on the right side of a normalized Rect
    * \param ref Referential you want to check
    * \return true if Referential is on right side, false otherwise
    */
    bool isOnRightSide(Referential ref);
    /**
    * \brief Get if the Referential is on the top side of a normalized Rect
    * \param ref Referential you want to check
    * \return true if Referential is on top side, false otherwise
    */
    bool isOnTopSide(Referential ref);
    /**
    * \brief Get if the Referential is on the bottom side of a normalized Rect
    * \param ref Referential you want to check
    * \return true if Referential is on bottom side, false otherwise
    */
    bool isOnBottomSide(Referential ref);
    /**
    * \brief Get if the Referential is on a corner of a normalized Rect
    * \param ref Referential you want to check
    * \return true if Referential is on a corner, false otherwise
    */
    bool isOnCorner(Referential ref);
    /**
    * \brief Get if the Referential is on a side of a normalized Rect
    * \param ref Referential you want to check
    * \return true if Referential is on a side, false otherwise
    */
    bool isOnSide(Referential ref);
    /**
    * \brief Get the normalized position of a Referential in a Rect (-1 : Left / Top, 0 = Center, 1 = Right / Bottom)
    * \param ref Referential you want to get the normalized Position
    * \return The normalized position of a Referential in a Rect
    */
    UnitVector getReferentialOffset(Referential ref);
    /**
    * \brief Get the name of a Referential in std::string form
    * \param ref Referential you want to get the name
    * \return The name of the Referential in std::string form
    */
    std::string referentialToString(Referential ref);
    /**
    * \brief Gets a Referential based on its name
    * \param ref Name of the Referential
    * \return The Referential enum value corresponding to the given name
    */
    Referential stringToReferential(const std::string& ref);
    /**
    * \brief Overload of operator<< to print Referentials
    * \param os The stream you want to print the Referential
    * \param m The Referential you want to print
    * \return The given stream to chain calls
    */
    std::ostream& operator<<(std::ostream& os, Referential m);
}
