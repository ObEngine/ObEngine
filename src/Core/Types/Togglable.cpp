#include <Types/Togglable.hpp>

namespace obe::types
{
    void Togglable::change_state(bool state)
    {
        if (state != m_enabled)
        {
            m_enabled = state;
            on_state_change();
        }
    }

    void Togglable::on_state_change()
    {
    }

    Togglable::Togglable(bool enabled)
        : m_enabled(enabled)
    {
    }

    void Togglable::set_enabled(bool state)
    {
        change_state(state);
    }

    void Togglable::toggle()
    {
        change_state(!m_enabled);
    }

    void Togglable::enable()
    {
        change_state(true);
    }

    void Togglable::disable()
    {
        change_state(false);
    }

    bool Togglable::is_enabled() const
    {
        return m_enabled;
    }
} // namespace obe::types
