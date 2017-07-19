#include <Transform/Units.hpp>

namespace obe
{
    namespace Transform
    {
        Units stringToUnits(const std::string& unit)
        {
            if (unit == "ViewPercentage")
                return Units::ViewPercentage;
            if (unit == "ViewPixels")
                return Units::ViewPixels;
            if (unit == "ViewUnits")
                return Units::ViewUnits;
            if (unit == "WorldPixels")
                return Units::WorldPixels;
            if (unit == "WorldUnits")
                return Units::WorldUnits;
            return Units::Unknown;
        }

        std::string unitsToString(Units unit)
        {
            switch (unit)
            {
            case Units::ViewPercentage: return "ViewPercentage0";
            case Units::ViewPixels: return "ViewPixels";
            case Units::ViewUnits: return "ViewUnits";
            case Units::WorldPixels: return "WorldPixels";
            case Units::WorldUnits: return "WorldUnits";
            default: return "Error";
            }
            return "Error";
        }
    }
}
