#include <Types/Togglable.hpp>

namespace obe::Types
{
    Togglable::Togglable(bool enabled)
    {
        m_enabled = enabled;
    }

    void Togglable::setEnabled(bool state)
    {
        m_enabled = state;
    }

    void Togglable::toggle()
    {
        m_enabled = !m_enabled;
    }

    void Togglable::enable()
    {
        m_enabled = true;
    }

    void Togglable::disable()
    {
        m_enabled = false;
    }

    bool Togglable::isEnabled() const
    {
        return m_enabled;
    }
} // namespace obe::Types