#pragma once

#include <Collision/PolygonalCollider.hpp>
#include <Scene/Scene.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Editor
{
    struct ColliderDrawOptions
    {
        bool lines = false;
        bool points = false;
        bool centroid = false;
        bool skeleton = false;
        void configure(bool lines, bool points, bool centroid, bool skeleton);
    };

    class ColliderPainter
    {
    private:
        std::unordered_map<Collision::PolygonalCollider*, std::vector<int>>
            m_highlightedPoints;
        std::unordered_map<Collision::PolygonalCollider*, std::vector<int>>
            m_highlightedLines;
        void drawCollider(const Transform::UnitVector& offset,
            Collision::PolygonalCollider& polygon, const ColliderDrawOptions& options);

    public:
        void clearHighlights(Collision::PolygonalCollider* collider);
        void highlightLine(Collision::PolygonalCollider* collider, unsigned int index);
        void draw(Scene::Scene& scene, const ColliderDrawOptions& options);
    };
}