#include <Transform/Polygon.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::debug::render
{
    void draw_polygon(const graphics::RenderTarget target, Transform::Polygon& polygon,
        bool draw_lines, bool draw_points, bool draw_centroid, bool draw_skeleton,
        Transform::UnitVector offset);
}
