#pragma once

#include <unordered_map>

#include <Graphics/Color.hpp>

namespace obe::graphics
{
    class RenderTarget;
}

namespace obe::transform
{
    class UnitVector;
}

/**
 * \brief Some useful Graphics functions.
 * \additionalinclude{Graphics/RenderTarget.hpp}
 */
namespace obe::graphics::utils
{
    /**
     * \brief Draws a Point
     * \param surface RenderSurface where to render the point
     * \param x x Coordinate of the position of the Point
     * \param y y Coordinate of the position of the Point
     * \param radius Radius of the Point to draw
     * \param color Color of the new Point
     */
    void draw_point(RenderTarget surface, int x, int y, float radius, const Color& color);
    /**
     * \brief Draws a Line
     * \param surface RenderSurface where to render the line
     * \param x1 x Coordinate of the first point of the line
     * \param y1 y Coordinate of the first point of the line
     * \param x2 x Coordinate of the second point of the line
     * \param y2 y Coordinate of the second point of the line
     * \param thickness Thickness of the line you want to draw (2 = Minimal
     *        visible size)
     * \param color Color of the line you want to draw
     */
    void draw_line(
        RenderTarget surface, int x1, int y1, int x2, int y2, int thickness, const Color& color);

    struct DrawPolygonOptions
    {
        bool lines = true;
        bool points = true;
        float radius = 6.f;
        Color line_color = Color::White;
        Color point_color = Color::White;
        std::unordered_map<unsigned int, Color> specific_line_color;
        std::unordered_map<unsigned int, Color> specific_point_color;
    };
    /**
     * \brief Draws a Polygon
     * \param surface RenderSurface where to render the polygon
     * \param points List of all the Polygon points positions
     * \param options Drawing options :
     *        - <lines> bool : Are the lines of the Polygon visible ? (true =
     *          visible, false = not visible)
     *        - <points> bool : Are the points of the Polygon visible ? (true =
     *          visible, false = not visible)
     *        - <radius> unsigned int : The radius of the points of the Polygon.
     *        - <line_color> Color : Default color of the lines of the Polygon.
     *        - <line_color_x> Color : Color of a specific line of the Polygon
     *          where x is the index of the line
     *        - <point_color> Color : Default color of the points of the Polygon
     *        - <point_color_x> Color : Color of a specific point of the Polygon
     *          where x is the index of the point
     */
    void draw_polygon(RenderTarget surface, const std::vector<transform::UnitVector>& points,
        const DrawPolygonOptions& options);
} // namespace obe::graphics::utils
