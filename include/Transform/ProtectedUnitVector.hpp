#pragma once

#include <Transform/UnitVector.hpp>

namespace obe
{
    namespace Transform
    {
        /**
         * \brief An UnitVector where you can't access the unit
         */
        class ProtectedUnitVector : public UnitVector
        {
        protected:
            Units unit;
        public:
            ProtectedUnitVector(const Units& unit = Units::WorldUnits);
            ProtectedUnitVector(const double& x, const double& y, const Units& unit = Units::WorldUnits);
        };
    }
}