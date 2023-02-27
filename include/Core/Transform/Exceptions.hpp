#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::transform::exceptions
{
    class PolygonNotEnoughPoints : public Exception<PolygonNotEnoughPoints>
    {
    public:
        using Exception::Exception;
        PolygonNotEnoughPoints(void* polygon, std::size_t points,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Polygon at address @{} has only {} points (minimum: 3)", fmt::ptr(polygon),
                points);
        }
    };

    class PolygonPointIndexOverflow : public Exception<PolygonPointIndexOverflow>
    {
    public:
        using Exception::Exception;
        PolygonPointIndexOverflow(const void* polygon, std::size_t index, std::size_t maximum,
            std::source_location location = std::source_location::current())
            : Exception(location)
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
        UnknownReferential(std::string_view referential,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("'{}' is not a valid known Referential", referential);
            this->hint("Try one of these Referentials : (TopLeft, Top, TopRight, Left, "
                       "Center, Right, BottomLeft, Bottom, BottomRight, "
                       "Referential<double, double>)");
        }
    };
} // namespace obe::transform::exceptions
