#pragma once

#include <Transform/UnitVector.hpp>

namespace obe::Transform
{
    /**
     * \brief An UnitVector where you can't access the unit
     * @Bind
     */
    class ProtectedUnitVector : public UnitVector
    {
    protected:
        Units unit;

    public:
        /**
         * \brief Creates a new ProtectedUnitVector
         * \param unit Unit of the ProtectedUnitVector
         */
        explicit ProtectedUnitVector(const Units& unit = Units::SceneUnits);
        /**
         * \brief Creates a new ProtectedUnitVector
         * \param x x Coordinate of the Position of the ProtectedUnitVector
         * \param y y Coordinate of the Position of the ProtectedUnitVector
         * \param unit Unit of the ProtectedUnitVector
         */
        ProtectedUnitVector(const double& x, const double& y,
            const Units& unit = Units::SceneUnits);
    };
} // namespace obe::Transform