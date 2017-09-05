#pragma once

#include <Transform/UnitVector.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Transform
    {
        enum class MovableType
        {
            Movable,
            Rect,
            Camera,
            LevelSprite,
            PolygonalCollider,
            SceneNode
        };
        class Movable : public Types::Identifiable
        {
        protected:
            MovableType m_type;
            UnitVector m_position;
        public:
            Movable(MovableType type, const std::string& id);
            /**
             * \brief Set the position of the Movable using an UnitVector
             * \param position Position to affect to the Movable
             */
            virtual void setPosition(const UnitVector& position);
            /**
            * \brief Moves the Movable (Adds the given position to the current one)
            * \param position Position to add to the current Position
            */
            virtual void move(const UnitVector& position);
            /**
             * \brief Get the Position of the Movable
             * \return The Position of the given Referencial of the Movable
             */
            virtual UnitVector getPosition() const;
            /**
             * \brief Gets the type of the Movable object
             * \return An enum value from MovableType
             */
            MovableType getType() const;
        };
    }
}