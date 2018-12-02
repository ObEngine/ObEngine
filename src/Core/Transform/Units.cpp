#include <vili/ErrorHandler.hpp>

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
        throw aube::ErrorHandler::Raise("obe.Transform.Units.UnknownStringUnit", {{"unit", unit}});
    }

    std::string unitsToString(Units unit)
    {
        switch (unit)
        {
        case Units::ViewPercentage: return "ViewPercentage";
        case Units::ViewPixels: return "ViewPixels";
        case Units::ViewUnits: return "ViewUnits";
        case Units::ScenePixels: return "ScenePixels";
        case Units::SceneUnits: return "SceneUnits";
        }
        throw aube::ErrorHandler::Raise("obe.Transform.Units.UnknownUnit");
    }
}