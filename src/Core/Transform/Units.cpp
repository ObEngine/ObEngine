#include <Transform/Exceptions.hpp>
#include <Transform/Units.hpp>

namespace obe::Transform
{
    Units stringToUnits(const std::string& unit)
    {
        if (unit == "ViewPercentage")
            return Units::ViewPercentage;
        if (unit == "ViewPixels")
            return Units::ViewPixels;
        if (unit == "ViewUnits")
            return Units::ViewUnits;
        if (unit == "ScenePixels")
            return Units::ScenePixels;
        if (unit == "SceneUnits")
            return Units::SceneUnits;
        throw Exceptions::UnknownUnit(unit, EXC_INFO);
    }

    std::string unitsToString(Units unit)
    {
        switch (unit)
        {
        case Units::ViewPercentage:
            return "ViewPercentage";
        case Units::ViewPixels:
            return "ViewPixels";
        case Units::ViewUnits:
            return "ViewUnits";
        case Units::ScenePixels:
            return "ScenePixels";
        case Units::SceneUnits:
            return "SceneUnits";
        }
        const int enumValue = static_cast<std::underlying_type_t<Units>>(unit);
        throw Exceptions::InvalidUnitsEnumValue(enumValue, EXC_INFO);
    }
} // namespace obe::Transform