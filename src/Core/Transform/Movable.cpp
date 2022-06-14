#include <Transform/Movable.hpp>

namespace obe::transform
{
    void Movable::set_position(const UnitVector& position)
    {
        m_position.set(position);
    }

    void Movable::move(const UnitVector& position)
    {
        m_position.add(position);
    }

    UnitVector Movable::get_position() const
    {
        return m_position;
    }
} // namespace obe::transform
