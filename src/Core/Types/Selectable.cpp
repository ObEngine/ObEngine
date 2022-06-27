#include <Types/Selectable.hpp>

namespace obe::types
{
    Selectable::Selectable(bool selected)
    {
        m_selected = selected;
    }

    void Selectable::set_selected(bool selected)
    {
        m_selected = selected;
    }

    void Selectable::toggle_selected()
    {
        m_selected = !m_selected;
    }

    void Selectable::select()
    {
        m_selected = true;
    }

    void Selectable::unselect()
    {
        m_selected = false;
    }

    bool Selectable::is_selected() const
    {
        return m_selected;
    }
} // namespace obe::types
