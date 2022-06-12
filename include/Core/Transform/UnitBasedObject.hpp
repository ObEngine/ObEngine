#pragma once

#include <Transform/Units.hpp>

namespace obe::Transform
{
    /**
     * \brief Classes that works with Units should inherit from this Class
     * \todo Refactor classes that inherits from this so it really use the working unit
     */
    class UnitBasedObject
    {
    protected:
        /**
         * \brief Unit used in the Class
         */
        Units m_unit = Units::SceneUnits;
        virtual void reset_unit(Units unit) = 0;

    public:
        virtual ~UnitBasedObject() = default;
        UnitBasedObject& operator=(UnitBasedObject&&) = delete;

        /**
         * \brief Set the unit the Object should work with
         * \param unit Unit you want the Object to work with
         */
        void setWorkingUnit(Units unit);
        /**
         * \brief Get the unit the Object works with
         * \return The unit the Object works with
         */
        [[nodiscard]] Units getWorkingUnit() const;
    };
} // namespace obe::Transform
