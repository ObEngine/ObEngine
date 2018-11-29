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
        for (auto& trajectory : m_trajectories)
        {
            Trajectory* cTraj = trajectory.second.get();
            if (cTraj->isEnabled())
            {
                const double speed = cTraj->m_speed + cTraj->m_acceleration * dt;
                const double radAngle = (Utils::Math::pi / 180.0) * -cTraj->getAngle();
                const double addX = std::cos(radAngle) * (speed * dt);
                const double addY = std::sin(radAngle) * (speed * dt);
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
                    //Debug::Log->warn("Trajectory not static");
                    cTraj->m_speed = speed;
                    Transform::UnitVector realOffset = cOffset;
                    if (m_probe != nullptr)
                    {
                        realOffset = m_probe->getMaximumDistanceBeforeCollision(cOffset);
                        //Debug::Log->warn("Probe not nullptr");
                    }
                    //Debug::Log->warn("State before ccheck : (offset diff : {}) (callback : {})", (realOffset != cOffset), (!trajectory.second->getOnCollideCallback().isNilref()));
                    if (realOffset != cOffset && !trajectory.second->getOnCollideCallback().isNilref())
                    {
                        //Debug::Log->warn("Calling callback !");
                        trajectory.second->getOnCollideCallback()(trajectory.second.get(), cOffset, realOffset);
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
}
