#include <Transform/UnitBasedObject.hpp>

namespace obe::transform
{
    void UnitBasedObject::set_working_unit(Units unit)
    {
        m_unit = unit;
        reset_unit(unit);
    }

    Units UnitBasedObject::get_working_unit() const
    {
        return m_unit;
    }
} // namespace obe::transform
