#pragma once

#include <unordered_map>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Scene/SceneNode.hpp>

namespace obe::collision
{
    /**
     * \brief A Node containing trajectories, a SceneNode to drive and a probe to check
     * for collisions
     */
    class TrajectoryNode
    {
    private:
        PolygonalCollider* m_probe = nullptr;
        Scene::SceneNode& m_scene_node;
        std::unordered_map<std::string, std::unique_ptr<Trajectory>> m_trajectories {};

    public:
        explicit TrajectoryNode(Scene::SceneNode& scene_node);
        Trajectory& add_trajectory(
            const std::string& id, Transform::Units unit = Transform::Units::SceneUnits);
        [[nodiscard]] Scene::SceneNode& get_scene_node() const;
        [[nodiscard]] Trajectory& get_trajectory(const std::string& id) const;
        void remove_trajectory(const std::string& id);
        void set_probe(PolygonalCollider* probe);
        void update(double dt) const;
    };
} // namespace obe::collision
