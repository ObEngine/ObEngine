#pragma once

#include <Exception.hpp>

namespace obe::Transform::Exceptions
{
    class PolygonNotEnoughPoints : public Exception<PolygonNotEnoughPoints>
    {
    public:
        using Exception::Exception;
        PolygonNotEnoughPoints(void* polygon, std::size_t points, DebugInfo info)
            : Exception(info)
        {
            this->error("Polygon at address @{} has only {} points (minimum: 3)", fmt::ptr(polygon),
                points);
        }
    };

    class PolygonPointIndexOverflow : public Exception<PolygonPointIndexOverflow>
    {
    public:
        using Exception::Exception;
        PolygonPointIndexOverflow(
            const void* polygon, std::size_t index, std::size_t maximum, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to access PolygonPoint at index {} of Polygon at address "
                        "@{} when it "
                        "only contains {} points",
                index, fmt::ptr(polygon), maximum);
        }
    };

    class UnknownReferential : public Exception<UnknownReferential>
    {
    public:
        using Exception::Exception;
        UnknownReferential(std::string_view referential, DebugInfo info)
            : Exception(info)
        {
            this->error("'{}' is not a valid known Referential", referential);
            this->hint("Try one of these Referentials : (TopLeft, Top, TopRight, Left, "
                       "Center, Right, BottomLeft, Bottom, BottomRight, "
                       "Referential<double, double>");
        }
    };

    class UnknownUnit : public Exception<UnknownUnit>
    {
    public:
        using Exception::Exception;
        UnknownUnit(std::string_view unit, DebugInfo info)
            : Exception(info)
        {
            this->error("There is no Units named '{}'", unit);
            this->hint("Try one of these Units : (ScenePixels, SceneUnits, "
                       "ViewPercentage, ViewPixels, ViewUnits)");
        }
    };

    class InvalidUnitsEnumValue : public Exception<InvalidUnitsEnumValue>
    {
    public:
        using Exception::Exception;
        InvalidUnitsEnumValue(int enumValue, DebugInfo info)
            : Exception(info)
        {
            this->error("Enum Units can't have invalid value ({})", enumValue);
        }
    };
}
