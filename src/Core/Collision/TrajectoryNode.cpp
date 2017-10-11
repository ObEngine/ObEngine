#include <cmath>

#include <Collision/TrajectoryNode.hpp>
#include <Utils/MathUtils.hpp>

namespace obe
{
    namespace Collision
    {
        TrajectoryNode::TrajectoryNode(Transform::SceneNode* sceneNode)
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

        void TrajectoryNode::update(double dt)
        {
            for (auto& trajectory : m_trajectories)
            {
                Trajectory* cTraj = trajectory.second.get();
                if (cTraj->isEnabled())
                {
                    double speed = cTraj->m_speed + cTraj->m_acceleration * dt;
                    double radAngle = (Utils::Math::pi / 180.0) * -cTraj->getAngle();
                    double addX = std::cos(radAngle) * (speed * dt);
                    double addY = std::sin(radAngle) * (speed * dt);
                    Transform::UnitVector cOffset(addX, addY, cTraj->getUnit());
                    for (kaguya::LuaFunction& check : trajectory.second->getChecks())
                    {
                        if (m_probe != nullptr)
                            check(cTraj, &cOffset, m_probe);
                        else
                            check(cTraj, &cOffset);
                    }
                    if (!cTraj->getStatic())
                    {
                        cTraj->m_speed = speed;
                        Transform::UnitVector realOffset = cOffset;
                        if (m_probe != nullptr)
                            realOffset = m_probe->getMaximumDistanceBeforeCollision(cOffset);
                        if (realOffset != cOffset && !trajectory.second->getOnCollideCallback().isNilref())
                            trajectory.second->getOnCollideCallback()(trajectory.second.get(), cOffset, realOffset);
                        m_sceneNode->move(realOffset);
                    }
                }
            }
        }

        Transform::SceneNode* TrajectoryNode::getSceneNode() const
        {
            return m_sceneNode;
        }
    }
}
