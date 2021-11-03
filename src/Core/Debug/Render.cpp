#include <SFML/Graphics/CircleShape.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Transform/Polygon.hpp>

namespace obe::Debug::Render
{
    void drawPolygon(const Graphics::RenderTarget target, Transform::Polygon& polygon,
        bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel,
        Transform::UnitVector offset)
    {
        if (polygon.getPointsAmount() >= 3)
        {
            const Transform::UnitVector centroid
                = polygon.getCentroid().to<Transform::Units::ScenePixels>();

            const float r = 6.f;
            // TODO: Refactor using C++20 designated initializers
            const Graphics::Utils::DrawPolygonOptions drawOptions { drawLines, drawPoints, r };

            std::vector<Transform::UnitVector> drawPoints;
            std::vector<Transform::UnitVector> pixelPoints;
            const Transform::PolygonPath& polygonPoints = polygon.getAllPoints();
            pixelPoints.reserve(polygonPoints.size());
            drawPoints.reserve(polygonPoints.size());

            std::transform(polygonPoints.begin(), polygonPoints.end(),
                std::back_inserter(pixelPoints),
                [](const auto& point) { return point->to(Transform::Units::ScenePixels); });

            for (const Transform::UnitVector& point : pixelPoints)
            {
                drawPoints.emplace_back(point - offset);
            }

            if (drawMasterPoint)
            {
                const sf::Color skeletonColor = sf::Color(255, 200, 0);
                const sf::Color centroidColor = sf::Color(255, 150, 0);
                sf::CircleShape polyPt;
                polyPt.setPosition(
                    sf::Vector2f(centroid.x - offset.x - r, centroid.y - offset.y - r));
                polyPt.setRadius(r);

                polyPt.setFillColor(centroidColor);
                target.draw(polyPt);
                if (drawSkel)
                {
                    for (const Transform::UnitVector& point : pixelPoints)
                    {

                        Graphics::Utils::drawLine(target, point.x - offset.x, point.y - offset.y,
                            centroid.x - offset.x, centroid.y - offset.y, 2, skeletonColor);
                    }
                }
            }
            Graphics::Utils::drawPolygon(target, drawPoints, drawOptions);
        }
    }
}
