#include <Transform/UnitBasedObject.hpp>

namespace obe::Transform
{
    void UnitBasedObject::setWorkingUnit(Units unit)
    {
        m_unit = unit;
        resetUnit(unit);
    }

    Units UnitBasedObject::getWorkingUnit() const
    {
        return m_unit;
    }
} // namespace obe::Transform
