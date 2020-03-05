#include <Editor/ColliderPainter.hpp>
#include <Graphics/DrawUtils.hpp>
#include <System/Window.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Editor
{
    void ColliderPainter::drawCollider(const Transform::UnitVector& offset,
        Collision::PolygonalCollider& polygon, const ColliderDrawOptions& options)
    {
        std::vector<int> highlightedPoints = m_highlightedPoints[&polygon];
        std::vector<int> highlightedLines = m_highlightedLines[&polygon];
        if (polygon.getPointsAmount() >= 3)
        {
            const Transform::UnitVector centroidPostion
                = polygon.getCentroid().to<Transform::Units::ScenePixels>();

            int r = 6;
            Graphics::Utils::DrawPolygonOptions drawOptions
                = { { "lines", options.lines }, { "points", options.points },
                      { "radius", r }, { "point_color", sf::Color::White },
                      { "line_color", sf::Color::White } };

            std::vector<sf::Vector2i> pointsPositions;

            for (int i = 0; i < polygon.getPointsAmount(); i++)
            {
                const Transform::UnitVector point
                    = polygon.get(i).to<Transform::Units::ScenePixels>();

                if (Utils::Vector::contains(i, highlightedPoints) && polygon.isSelected())
                    drawOptions["point_color_" + std::to_string(i)]
                        = sf::Color(255, 0, 0);
                if (Utils::Vector::contains(
                        (i != polygon.getPointsAmount() - 1) ? i + 1 : 0,
                        highlightedLines)
                    && polygon.isSelected())
                    drawOptions["line_color_" + std::to_string(i)] = sf::Color(0, 255, 0);

                pointsPositions.emplace_back(point.x - offset.x, point.y - offset.y);
            }

            if (Utils::Vector::contains(0, highlightedPoints) && polygon.isSelected())
                drawOptions["point_color_0"] = sf::Color(255, 255, 0);
            else if (polygon.isSelected())
                drawOptions["point_color_0"] = sf::Color(0, 255, 0);

            if (options.centroid)
            {
                sf::CircleShape polyPt;
                polyPt.setPosition(sf::Vector2f(
                    centroidPostion.x - offset.x - r, centroidPostion.y - offset.y - r));
                polyPt.setRadius(r);
                const sf::Color polyPtColor = polygon.isSelected()
                    ? sf::Color(0, 150, 255)
                    : sf::Color(255, 150, 0);
                polyPt.setFillColor(polyPtColor);
                System::MainWindow.draw(polyPt);
                if (options.skeleton)
                {
                    for (int i = 0; i < polygon.getPointsAmount(); i++)
                    {
                        const Transform::UnitVector point
                            = polygon.get(i).to<Transform::Units::ScenePixels>();
                        const sf::Color currentLineColor = polygon.isSelected()
                            ? sf::Color(0, 200, 255)
                            : sf::Color(255, 200, 0);
                        Graphics::Utils::drawLine(point.x - offset.x, point.y - offset.y,
                            centroidPostion.x - offset.x, centroidPostion.y - offset.y, 2,
                            currentLineColor);
                    }
                }
            }
            Graphics::Utils::drawPolygon(pointsPositions, drawOptions);
        }
    }

    void ColliderPainter::clearHighlights(Collision::PolygonalCollider* collider)
    {
        m_highlightedLines.at(collider).clear();
        m_highlightedPoints.at(collider).clear();
    }

    void ColliderPainter::highlightLine(
        Collision::PolygonalCollider* collider, unsigned int index)
    {
        m_highlightedLines.at(collider).push_back(index);
    }

    void ColliderPainter::draw(Scene::Scene& scene, const ColliderDrawOptions& options)
    {
        const Transform::UnitVector offset
            = scene.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
        for (auto polygon : scene.getAllColliders())
        {
            this->drawCollider(offset, *polygon, options);
        }
    }
    void ColliderDrawOptions::configure(
        bool lines, bool points, bool centroid, bool skeleton)
    {
        this->lines = lines;
        this->points = points;
        this->centroid = centroid;
        this->skeleton = skeleton;
    }
}