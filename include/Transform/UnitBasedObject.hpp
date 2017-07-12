#pragma once

#include <Transform/Units.hpp>

namespace obe
{
    namespace Transform
    {
        /**
         * \brief Classes that works with Units should herit from this Class
         */
        class UnitBasedObject
        {
        protected:
            /**
             * \brief Unit used in the Class
             */
            Units m_unit = Units::WorldUnits;
            virtual void resetUnit(Units unit) = 0;
        public:
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
    }
}