#include <Transform/Movable.hpp>

namespace obe
{
    namespace Transform
    {
        Movable::Movable(MovableType type)
        {
            m_type = type;
        }

        void Movable::setPosition(const UnitVector& position)
        {
            m_position.set(position);
        }

        void Movable::move(const UnitVector& position)
        {
            m_position.add(position);
        }

        UnitVector Movable::getPosition() const
        {
            return m_position;
        }

        MovableType Movable::getType() const
        {
            return m_type;
        }
    }
}
