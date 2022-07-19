#pragma once

#include <Collision/Collider.hpp>
#include <Collision/CollisionSpace.hpp>
#include <Collision/Trajectory.hpp>
#include <Scene/SceneNode.hpp>
#include <unordered_map>

namespace obe::collision
{
    /**
     * \brief A Node containing trajectories, a SceneNode to drive and a probe to check
     * for collisions
     */
    class TrajectoryNode
    {
    private:
        CollisionSpace const* m_collision_space = nullptr;
        Collider* m_probe = nullptr;
        scene::SceneNode& m_scene_node;
        std::unordered_map<std::string, std::unique_ptr<Trajectory>> m_trajectories {};

    public:
        explicit TrajectoryNode(scene::SceneNode& scene_node);
        Trajectory& add_trajectory(
            const std::string& id, transform::Units unit = transform::Units::SceneUnits);
        [[nodiscard]] scene::SceneNode& get_scene_node() const;
        [[nodiscard]] Trajectory& get_trajectory(const std::string& id) const;
        void remove_trajectory(const std::string& id);
        void set_probe(CollisionSpace const* collision_space, Collider* probe);
        void update(double dt) const;
    };
} // namespace obe::collision
