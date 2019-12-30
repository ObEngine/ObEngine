#include <cmath>

#include <Collision/TrajectoryNode.hpp>
#include <Debug/Logger.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::Collision
{
    TrajectoryNode::TrajectoryNode(Scene::SceneNode* sceneNode)
    {
        m_sceneNode = sceneNode;
    }

    void TrajectoryNode::setProbe(PolygonalCollider* probe)
    {
        m_probe = probe;
    }

    Trajectory* TrajectoryNode::addTrajectory(const std::string& id, Transform::Units unit)
    {
        m_trajectories[id] = std::make_unique<Trajectory>(unit);
        return m_trajectories[id].get();
    }

    Trajectory* TrajectoryNode::getTrajectory(const std::string& id)
    {
        return m_trajectories[id].get();
    }

    void TrajectoryNode::removeTrajectory(const std::string& id)
    {
        m_trajectories.erase(id);
    }

    void TrajectoryNode::update(const double dt)
    {
        auto getOffset = [&dt](Trajectory& trajectory) {
            const double speed = trajectory.getSpeed() + trajectory.getAcceleration() * dt;
            const double radAngle = (Utils::Math::pi / 180.0) * -trajectory.getAngle();
            const double addX = std::cos(radAngle) * (speed * dt);
            const double addY = std::sin(radAngle) * (speed * dt);
            return Transform::UnitVector(addX, addY, trajectory.getUnit());
        };
        for (auto& trajectory : m_trajectories)
        {
            Trajectory* cTraj = trajectory.second.get();
            if (cTraj->isEnabled())
            {
                auto baseOffset = getOffset(*cTraj);

                for (kaguya::LuaFunction& check : trajectory.second->getChecks())
                {
                    if (m_probe != nullptr)
                    {
                        check(cTraj, &baseOffset, m_probe);
                    }
                    else
                    {
                        check(cTraj, &baseOffset);
                    }
                }
                if (!cTraj->getStatic())
                {
                    cTraj->setSpeed(cTraj->m_speed + cTraj->m_acceleration * dt);
                    baseOffset = getOffset(*cTraj);
                    Transform::UnitVector realOffset = baseOffset;
                    if (m_probe != nullptr)
                    {
                        realOffset = m_probe->getMaximumDistanceBeforeCollision(realOffset);
                    }
                    if (realOffset != baseOffset
                        && !trajectory.second->getOnCollideCallback().isNilref())
                    {
                        trajectory.second->getOnCollideCallback()(
                            trajectory.second.get(), baseOffset, realOffset);
                    }
                    m_sceneNode->move(realOffset);
                }
            }
        }
    }

    Scene::SceneNode* TrajectoryNode::getSceneNode() const
    {
        return m_sceneNode;
    }
} // namespace obe::Collision
