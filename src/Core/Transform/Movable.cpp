#include <Transform/Movable.hpp>

namespace obe::Transform
{
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
}