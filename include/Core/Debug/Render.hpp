#include <Transform/Polygon.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Debug::Render
{
    void drawPolygon(const Graphics::RenderTarget target, Transform::Polygon& polygon,
        bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel,
        Transform::UnitVector offset);
}
