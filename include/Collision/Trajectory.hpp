#pragma once

namespace obe
{
    namespace Collision
    {
        class Trajectory
        {
        private:
            double m_angle;
            double m_speed;
            double m_acceleration;
            std::vector<PolygonalCollider*> m_probes;
            Transform::Node2D m_sceneNode;
        };
    }
}