#pragma once

#include <Exception.hpp>

namespace obe::Transform::Exceptions
{
    class PolygonNotEnoughPoints : public Exception
    {
    public:
        PolygonNotEnoughPoints(void* polygon, std::size_t points, DebugInfo info)
            : Exception("ChildNotInSceneNode", info)
        {
            this->error("Polygon at address @{} has only {} points (minimum: 3)",
                fmt::ptr(polygon), points);
        }
    };

    class PolygonPointIndexOverflow : public Exception
    {
    public:
        PolygonPointIndexOverflow(
            void* polygon, std::size_t index, std::size_t maximum, DebugInfo info)
            : Exception("PolygonPointIndexOverflow", info)
        {
            this->error("Tried to access PolygonPoint at index {} of Polygon at address "
                        "@{} when it "
                        "only contains {} points",
                index, fmt::ptr(polygon), maximum);
        }
    };

    class UnknownReferential : public Exception
    {
    public:
        UnknownReferential(std::string_view referential, DebugInfo info)
            : Exception("UnknownReferential", info)
        {
            this->error("'{}' is not a valid known Referential", referential);
            this->hint("Try one of these Referentials : (TopLeft, Top, TopRight, Left, "
                       "Center, Right, BottomLeft, Bottom, BottomRight, "
                       "Referential<double, double>");
        }
    };

    class UnknownUnit : public Exception
    {
    public:
        UnknownUnit(std::string_view unit, DebugInfo info)
            : Exception("UnknownUnit", info)
        {
            this->error("There is no Units named '{}'", unit);
            this->hint("Try one of these Units : (ScenePixels, SceneUnits, "
                       "ViewPercentage, ViewPixels, ViewUnits)");
        }
    };

    class InvalidUnitsEnumValue : public Exception
    {
    public:
        InvalidUnitsEnumValue(int enumValue, DebugInfo info)
            : Exception("InvalidUnitsEnumValue", info)
        {
            this->error("Enum Units can't have invalid value ({})", enumValue);
        }
    };
}