#pragma once

#include <Transform/Units.hpp>

namespace obe::Transform
{
    /**
     * \brief Classes that works with Units should herit from this Class
     * @Bind
     */
    class UnitBasedObject
    {
    protected:
        /**
         * \brief Unit used in the Class
         */
        Units m_unit = Units::SceneUnits;
        virtual void resetUnit(Units unit) = 0;

    public:
        virtual ~UnitBasedObject() = default;
        /**
         * \brief Set the unit the Object should work with
         * \param unit Unit you want the Object to work with
         */
        void setWorkingUnit(Units unit);
        /**
         * \brief Get the unit the Object works with
         * \return The unit the Object works with
         */
        Units getWorkingUnit() const;
    };
} // namespace obe::Transform