#include <Transform/ProtectedUnitVector.hpp>

namespace obe
{
    namespace Transform
    {
        ProtectedUnitVector::ProtectedUnitVector(const Units& unit)
        {
            this->unit = unit;
        }

        ProtectedUnitVector::ProtectedUnitVector(const double& x, const double& y, const Units& unit)
        {
            this->x = x;
            this->y = y;
            this->unit = unit;
        }
    }
}
