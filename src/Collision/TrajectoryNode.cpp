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
            m_trajectories[id] = std::pair<std::unique_ptr<Trajectory>, std::vector<kaguya::LuaFunction>>
            (std::make_unique<Trajectory>(unit), std::vector<kaguya::LuaFunction>());
            return m_trajectories[id].first.get();
        }

        void TrajectoryNode::addCheck(const std::string& id, kaguya::LuaFunction check)
        {
            m_trajectories[id].second.push_back(check);
        }

        void TrajectoryNode::onCollide(kaguya::LuaFunction callback)
        {
            m_onCollideCallback = callback;
        }

        Trajectory* TrajectoryNode::getTrajectory(const std::string& id)
        {
            return m_trajectories[id].first.get();
        }

        void TrajectoryNode::removeTrajectory(const std::string& id)
        {
            m_trajectories.erase(id);
        }

        void TrajectoryNode::update(double dt)
        {
            Transform::UnitVector offset(0, 0);
            for (auto& trajectory : m_trajectories)
            {
                Trajectory* cTraj = trajectory.second.first.get();
                if (cTraj->isEnabled())
                {
                    double speed = cTraj->m_speed + cTraj->m_acceleration * dt;
                    double radAngle = (Utils::Math::pi / 180.0) * -cTraj->getAngle();
                    double addX = std::cos(radAngle) * (speed * dt);
                    double addY = std::sin(radAngle) * (speed * dt);
                    Transform::UnitVector cOffset(addX, addY, cTraj->getUnit());
                    for (kaguya::LuaFunction& check : trajectory.second.second)
                    {
                        if (m_probe != nullptr)
                            check(cTraj, &cOffset, m_probe);
                        else
                            check(cTraj, &cOffset);
                    }
                    if (!cTraj->getStatic())
                    {
                        cTraj->m_speed = speed;
                        offset.add(cOffset);
                    }
                }
            }
            Transform::UnitVector realOffset = offset;
            if (m_probe != nullptr)
                realOffset = m_probe->getMaximumDistanceBeforeCollision(offset);
            if (realOffset != offset && !m_onCollideCallback.isNilref())
                m_onCollideCallback(offset, realOffset);
            m_sceneNode->move(realOffset);
        }

        Transform::SceneNode* TrajectoryNode::getSceneNode() const
        {
            return m_sceneNode;
        }
    }
}
