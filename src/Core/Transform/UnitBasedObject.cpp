#include <Transform/UnitBasedObject.hpp>

namespace obe::Transform
{
    void UnitBasedObject::setWorkingUnit(Units unit)
    {
        m_unit = unit;
        reset_unit(unit);
    }

    Units UnitBasedObject::getWorkingUnit() const
    {
        return m_unit;
    }
} // namespace obe::Transform
