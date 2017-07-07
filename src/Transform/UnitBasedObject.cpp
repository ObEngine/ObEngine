#include <Transform/UnitBasedObject.hpp>

namespace obe
{
    namespace Transform
    {
        void UnitBasedObject::setWorkingUnit(Units unit)
        {
            m_unit = unit;
        }

        Units UnitBasedObject::getWorkingUnit() const
        {
            return m_unit;
        }
    }
}