#include <cmath>

#include <Collision/TrajectoryNode.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::collision
{
    TrajectoryNode::TrajectoryNode(scene::SceneNode& scene_node)
        : m_scene_node(scene_node)
    {
    }

    void TrajectoryNode::set_probe(PolygonalCollider* probe)
    {
        m_probe = probe;
    }

    Trajectory& TrajectoryNode::add_trajectory(const std::string& id, transform::Units unit)
    {
        m_trajectories[id] = std::make_unique<Trajectory>(unit);
        return *m_trajectories[id];
    }

    Trajectory& TrajectoryNode::get_trajectory(const std::string& id) const
    {
        return *m_trajectories.at(id);
    }

    void TrajectoryNode::remove_trajectory(const std::string& id)
    {
        m_trajectories.erase(id);
    }

    void TrajectoryNode::update(const double dt) const
    {
        auto get_offset = [&dt](const Trajectory& trajectory)
        {
            const double speed = trajectory.get_speed() + trajectory.get_acceleration() * dt;
            const double rad_angle = (utils::math::pi / 180.0) * -trajectory.get_angle();
            const double x_offset = std::cos(rad_angle) * (speed * dt);
            const double y_offset = std::sin(rad_angle) * (speed * dt);
            return transform::UnitVector(x_offset, y_offset, trajectory.get_unit());
        };
        for (auto& trajectory : m_trajectories)
        {
            Trajectory* current_trajectory = trajectory.second.get();
            if (current_trajectory->is_enabled())
            {
                auto base_offset = get_offset(*current_trajectory);

                for (TrajectoryCheckFunction& check : trajectory.second->get_checks())
                {
                    check(*current_trajectory, base_offset, m_probe);
                }
                if (!current_trajectory->is_static())
                {
                    current_trajectory->set_speed(
                        current_trajectory->m_speed + current_trajectory->m_acceleration * dt);
                    base_offset = get_offset(*current_trajectory);
                    obe::collision::CollisionData collision_data;
                    collision_data.offset = base_offset;
                    if (m_probe != nullptr)
                    {
                        collision_data = m_probe->get_distance_before_collision(collision_data.offset);
                    }
                    m_scene_node.move(collision_data.offset);
                    auto on_collide_callback = trajectory.second->get_on_collide_callback();
                    if (collision_data.offset != base_offset && on_collide_callback)
                    {
                        on_collide_callback(*trajectory.second, base_offset, collision_data);
                    }
                }
            }
        }
    }

    scene::SceneNode& TrajectoryNode::get_scene_node() const
    {
        return m_scene_node;
    }
} // namespace obe::collision
