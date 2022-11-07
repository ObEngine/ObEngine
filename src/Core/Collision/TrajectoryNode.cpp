#include <cmath>

#include <Collision/Exceptions.hpp>
#include <Collision/TrajectoryNode.hpp>
#include <Utils/MathUtils.hpp>

#include <Debug/Logger.hpp> // TODO: Remove logs

namespace obe::collision
{
    TrajectoryNode::TrajectoryNode(scene::SceneNode& scene_node)
        : m_scene_node(scene_node)
    {
    }

    void TrajectoryNode::set_probe(CollisionSpace const* collision_space, Collider* probe)
    {
        m_collision_space = collision_space;
        m_probe = probe;
    }

    Trajectory& TrajectoryNode::add_trajectory(const std::string& id, transform::Units unit)
    {
        if (m_trajectories.contains(id))
        {
            throw exceptions::TrajectoryAlreadyExists(id, EXC_INFO);
        }
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

    transform::UnitVector make_offset_normal(const transform::UnitVector& offset)
    {
        static double base_offset_normal_scale = 0.0005;
        if (abs(offset.x) >= abs(offset.y))
        {
            return transform::UnitVector(base_offset_normal_scale,
                (offset.y != 0) ? offset.y / offset.x * base_offset_normal_scale : 0, offset.unit);
        }
        else
        {
            return transform::UnitVector(
                (offset.x != 0) ? offset.x / offset.y * base_offset_normal_scale : 0, base_offset_normal_scale, offset.unit);
        }
    }

    void TrajectoryNode::update(const double dt) const
    {
        auto get_offset = [&dt](const Trajectory& trajectory) {
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
                    current_trajectory->m_speed = current_trajectory->m_speed + current_trajectory->m_acceleration * dt;
                    base_offset = get_offset(*current_trajectory);
                    obe::collision::CollisionData collision_data;
                    collision_data.offset = base_offset;
                    if (m_probe != nullptr && m_collision_space != nullptr)
                    {
                        const transform::UnitVector offset_normal = make_offset_normal(base_offset);
                        // Slightly push towards offset to avoid getting stuck inside of it
                        m_probe->move(offset_normal);
                        collision_data.offset = m_collision_space->get_offset_before_collision(
                            *m_probe, collision_data.offset);
                        // Moving away from the normal offset
                        m_probe->move(-offset_normal);
                        /* debug::Log->debug(
                            "<TrajectoryNode> Trajectory '{}'\tBase Offset {}\tOffset {}\tNormal {}\tTOI {}\tDT {}",
                            trajectory.first, base_offset, collision_data.offset, offset_normal, collision_data.offset.x / base_offset.x, dt);*/
                    }

                    m_scene_node.move(collision_data.offset);
                    auto on_collide_callback = trajectory.second->get_on_collide_callback();
                    if (collision_data.offset != base_offset && on_collide_callback)
                    {
                        on_collide_callback(*trajectory.second, collision_data.offset, m_probe);
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
