#pragma once

#include <Transform/UnitVector.hpp>

namespace obe::transform
{
    /**
     * \brief A class which implements position and basic methods to manipulate it
     */
    class Movable
    {
    protected:
        UnitVector m_position;

    public:
        Movable() = default;
        explicit Movable(const transform::UnitVector& position);
        virtual ~Movable() = default;
        /**
         * \brief Set the position of the Movable using an UnitVector
         * \param position Position to affect to the Movable
         */
        virtual void set_position(const UnitVector& position);
        /**
         * \brief Moves the Movable (Adds the given position to the current one)
         * \param position Position to add to the current Position
         */
        virtual void move(const UnitVector& position);
        /**
         * \brief Get the Position of the Movable
         * \return The Position of the given Referential of the Movable
         */
        [[nodiscard]] virtual UnitVector get_position() const;
        /**
         * \brief Gets the type of the Movable object
         * \return An enum value from MovableType
         */
    };
} // namespace obe::transform
