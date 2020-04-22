#include <Types/Togglable.hpp>

namespace obe::Types
{
    void Togglable::changeState(bool state)
    {
        if (state != m_enabled)
        {
            m_enabled = state;
            onStateChange();
        }
    }

    void Togglable::onStateChange()
    {
    }

    Togglable::Togglable(bool enabled)
        : m_enabled(enabled)
    {
    }

    void Togglable::setEnabled(bool state)
    {
        changeState(state);
    }

    void Togglable::toggle()
    {
        changeState(!m_enabled);
    }

    void Togglable::enable()
    {
        changeState(true);
    }

    void Togglable::disable()
    {
        changeState(false);
    }

    bool Togglable::isEnabled() const
    {
        return m_enabled;
    }
} // namespace obe::Types