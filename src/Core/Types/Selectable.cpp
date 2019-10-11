#include <Types/Selectable.hpp>

namespace obe::Types
{
    Selectable::Selectable(bool selected)
    {
        m_selected = selected;
    }

    void Selectable::setSelected(bool selected)
    {
        m_selected = selected;
    }

    void Selectable::toggleSelected()
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

    bool Selectable::isSelected() const
    {
        return m_selected;
    }
} // namespace obe::Types