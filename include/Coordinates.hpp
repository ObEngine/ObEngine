#pragma once

#include <iostream>

namespace obe
{
    namespace Coord
    {
        /**
         * \brief Different Units used to work with elements position / size in the Scene
         */
        enum Units
        {
            /**
             * \brief ViewPercentage is an Unit used to place / scale an element using the View. \n
             * Exemple : x = 0.5, y = 0.5 is the middle of the View
             */
            ViewPercentage,
            /**
            * \brief ViewPercentage is an Unit used to place / scale an element using the pixels of the View. \n
            * Exemple : x = 500, y = 500 is the middle of a 1000x1000 pixels screen
            */
            ViewPixels,
            /**
            * \brief ViewUnits is an Unit used to place / scale an element using the View. \n
            * Exemple : x = 1, y = 1 is the middle of a 1000x1000 pixels screen. \n
            * The screen height will ALWAYS be 2 ViewUnits when the View size is 1, the width will depend on the screen ratio. \n
            * The screen width in ViewUnits can be calculated using this formula : 2 * viewSize * (Screen.Width / Screen.Height)
            */
            ViewUnits,
            /**
            * \brief ViewPercentage is an Unit used to place / scale an element using the pixels of the World. \n
            * Exemple : x = 4000, y = 10000
            */
            WorldPixels,
            /**
            * \brief WorldUnits is an Unit used to place / scale an element using the World. \n
            * Exemple : x = 4.5, y = 2.5\n
            */
            WorldUnits,
            /**
             * \brief This Unit should never be used. (Debug purpose)
             */
            Unknown
        };

        /**
         * \brief Converts a std::string to an Unit
         * \param unit Unit in string form
         * \return The convert Units enum value
         */
        Units stringToUnits(const std::string& unit);
        /**
         * \brief Converts an Unit to a std::string
         * \param unit The Units enum value you want to convert into a std::string
         * \return A std::string containing the Units enum value in string form
         */
        std::string unitsToString(Units unit);

        /**
         * \brief Struct representing the View used for internal UnitVector conversions
         */
        struct ViewStruct
        {
            double w;
            double h;
            double x;
            double y;
        };

        /**
        * \brief Struct representing the Screen used for internal UnitVector conversions
        */
        struct ScreenStruct
        {
            double w;
            double h;
        };

        /**
         * \brief Classes that works with Units should herit from this Class
         */
        class UnitBasedObject
        {
        protected:
            /**
             * \brief Unit used in the Class
             */
            Units m_unit = WorldUnits;
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

        /**
         * \brief Class widely used in the Engine to scale and position elements in a Scene
         */
        class UnitVector
        {
        public:
            static void Init(ViewStruct*&);
            static void Init(int width, int height);

            static ViewStruct View;
            static ScreenStruct Screen;

            UnitVector(Units unit = WorldUnits);
            UnitVector(double x, double y, Units unit = WorldUnits);

            double x = 0.0;
            double y = 0.0;
            Units unit;

            void set(const UnitVector& vec);
            void set(double x, double y);
			void add(const UnitVector& vec);
            void add(double x, double y);

            UnitVector operator+(const UnitVector& add) const;
            UnitVector& operator+=(const UnitVector& add);
            UnitVector operator-(const UnitVector& add) const;
            UnitVector& operator-=(const UnitVector& add);
            UnitVector operator*(const UnitVector& add) const;
            UnitVector& operator*=(const UnitVector& add);
            UnitVector operator/(const UnitVector& add) const;
            UnitVector& operator/=(const UnitVector& add);

            /**
             * \brief Return an UnitVector with the converted values (x, y) to the Unit you want
             * \tparam E An enum value from Coord::Units
             * \return A new UnitVector containing the converted values with the new Units
             */
            template <Units E>
            UnitVector to() const { return {}; };
            /**
             * \brief Return an UnitVector with the converted values (x, y) to the Unit you want
             * \param pUnit An enum value from Coord::Units
             * \return A new UnitVector containing the converted values with the new Units
             */
            UnitVector to(Units pUnit) const;
        };

        /**
         * \brief An UnitVector where you can't access the unit
         */
        class ProtectedUnitVector : public UnitVector
        {
        protected:
            Units unit;
        public:
            ProtectedUnitVector(const Units& unit = WorldUnits);
            ProtectedUnitVector(const double& x, const double& y, const Units& unit = WorldUnits);
        };

        template <>
        inline UnitVector UnitVector::to<ViewPercentage>() const
        {
            switch (unit)
            {
            case ViewPercentage:
                return UnitVector(x, y, ViewPercentage);
            case ViewPixels:
                return UnitVector(x / Screen.w, y / Screen.h, ViewPercentage);
            case ViewUnits:
                return UnitVector(x / View.w, y / View.h, ViewPercentage);
            case WorldPixels:
                return UnitVector(x / Screen.w - View.x / View.w, y / Screen.h - View.y / View.h, ViewPercentage);
            case WorldUnits:
                return UnitVector((x - View.x) / View.w, (y - View.y) / View.h, ViewPercentage);
            default:
                return UnitVector(0, 0);
            }
        }

        template <>
        inline UnitVector UnitVector::to<ViewPixels>() const
        {
            switch (unit)
            {
            case ViewPercentage:
                return UnitVector(x * Screen.w, y * Screen.h, ViewPixels);
            case ViewPixels:
                return UnitVector(x, y, ViewPixels);
            case ViewUnits:
                return UnitVector(x * Screen.w / View.w, y * Screen.h / View.h, ViewPixels);
            case WorldPixels:
                return UnitVector(x - (View.x * Screen.w / View.w), y - (View.y * Screen.h / View.h), ViewPixels);
            case WorldUnits:
                return UnitVector((x - View.x) / View.w * Screen.w, (y - View.y) / View.h * Screen.h, ViewPixels);
            default:
                return UnitVector(0, 0);
            }
        }

        template <>
        inline UnitVector UnitVector::to<ViewUnits>() const
        {
            switch (unit)
            {
            case ViewPercentage:
                return UnitVector(x * View.w, y * View.h, ViewUnits);
            case ViewPixels:
                return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, ViewUnits);
            case ViewUnits:
                return UnitVector(x, y, ViewUnits);
            case WorldPixels:
                return UnitVector(x / (Screen.w / View.w) - View.x, y / (Screen.h / View.h) - View.y, ViewUnits);
            case WorldUnits:
                return UnitVector(x - View.x, y - View.y, ViewUnits);
            default:
                return UnitVector(0, 0);
            }
        }

        template <>
        inline UnitVector UnitVector::to<WorldPixels>() const
        {
            switch (unit)
            {
            case ViewPercentage:
                return UnitVector(Screen.w * (View.x / View.w + x), Screen.h * (View.y / View.h + y), WorldPixels);
            case ViewPixels:
                return UnitVector(Screen.w * View.x / View.w + x, Screen.h * View.y / View.h + y, WorldPixels);
            case ViewUnits:
                return UnitVector(Screen.w * (View.x + x) / View.w, Screen.h * (View.y + y) / View.h, WorldPixels);
            case WorldPixels:
                return UnitVector(x, y, WorldPixels);
            case WorldUnits:
                return UnitVector(x / View.w * Screen.w, y / View.h * Screen.h, WorldPixels);
            default:
                return UnitVector(0, 0);
            }
        }

        template <>
        inline UnitVector UnitVector::to<WorldUnits>() const
        {
            switch (unit)
            {
            case ViewPercentage:
                return UnitVector((View.w * x) + View.x, (View.h * y) + View.y, WorldUnits);
            case ViewPixels:
                return UnitVector((View.w * (x / Screen.w)) + View.x, (View.h * (y / Screen.h)) + View.y, WorldUnits);
            case ViewUnits:
                return UnitVector(View.x + x, View.y + y, WorldUnits);
            case WorldPixels:
                return UnitVector(x / Screen.w * View.w, y / Screen.h * View.h, WorldUnits);
            case WorldUnits:
                return UnitVector(x, y, WorldUnits);
            default:
                return UnitVector(0, 0);
            }
        }

        /**
         * \brief Display an UnitVector for debug purposes
         * \param os The stream you want to print the UnitVector in
         * \param m The UnitVector you want to print
         * \return The stream passed by reference (To chain calls)
         */
        std::ostream& operator<<(std::ostream& os, const UnitVector& m);
    }
}
