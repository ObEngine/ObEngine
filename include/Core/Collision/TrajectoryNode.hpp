#pragma once

#include <unordered_map>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Scene/SceneNode.hpp>

namespace obe::Collision
{
    /**
     * \brief A Node containing trajectories, a SceneNode to drive and a probe to check
     * for collisions
     * \bind{TrajectoryNode}
     */
    class TrajectoryNode
    {
    private:
        PolygonalCollider* m_probe = nullptr;
        Scene::SceneNode& m_sceneNode;
        std::unordered_map<std::string, std::unique_ptr<Trajectory>> m_trajectories {};

    public:
        explicit TrajectoryNode(Scene::SceneNode& sceneNode);
        Trajectory& addTrajectory(
            const std::string& id, Transform::Units unit = Transform::Units::SceneUnits);
        [[nodiscard]] Scene::SceneNode& getSceneNode() const;
        Trajectory& getTrajectory(const std::string& id);
        void removeTrajectory(const std::string& id);
        void setProbe(PolygonalCollider* probe);
        void update(double dt);
    };
} // namespace obe::Collision