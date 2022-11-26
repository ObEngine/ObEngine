#include <Transform/Movable.hpp>

namespace obe::transform
{
    Movable::Movable(const transform::Vector2& position)
        : m_position(position)
    {
    }

    void Movable::set_position(const Vector2& position)
    {
        m_position = position;
    }

    void Movable::move(const Vector2& position)
    {
        m_position += position;
    }

    Vector2 Movable::get_position() const
    {
        return m_position;
    }
} // namespace obe::transform
