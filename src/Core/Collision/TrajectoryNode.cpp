#include <cmath>

#include <Collision/TrajectoryNode.hpp>
#include <Debug/Logger.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::Collision
{
    TrajectoryNode::TrajectoryNode(Scene::SceneNode& sceneNode)
        : m_sceneNode(sceneNode)
    {
    }

    void TrajectoryNode::setProbe(PolygonalCollider* probe)
    {
        m_probe = probe;
    }

    Trajectory& TrajectoryNode::addTrajectory(
        const std::string& id, Transform::Units unit)
    {
        m_trajectories[id] = std::make_unique<Trajectory>(unit);
        return *m_trajectories[id].get();
    }

    Trajectory& TrajectoryNode::getTrajectory(const std::string& id)
    {
        return *m_trajectories[id].get();
    }

    void TrajectoryNode::removeTrajectory(const std::string& id)
    {
        m_trajectories.erase(id);
    }

    void TrajectoryNode::update(const double dt)
    {
        auto getOffset = [&dt](Trajectory& trajectory) {
            const double speed
                = trajectory.getSpeed() + trajectory.getAcceleration() * dt;
            const double radAngle = (Utils::Math::pi / 180.0) * -trajectory.getAngle();
            const double addX = std::cos(radAngle) * (speed * dt);
            const double addY = std::sin(radAngle) * (speed * dt);
            return Transform::UnitVector(addX, addY, trajectory.getUnit());
        };
        for (auto& trajectory : m_trajectories)
        {
            Trajectory* currentTrajectory = trajectory.second.get();
            if (currentTrajectory->isEnabled())
            {
                auto baseOffset = getOffset(*currentTrajectory);

                for (TrajectoryCheckFunction& check : trajectory.second->getChecks())
                {
                    check(*currentTrajectory, baseOffset, m_probe);
                }
                if (!currentTrajectory->getStatic())
                {
                    currentTrajectory->setSpeed(currentTrajectory->m_speed
                        + currentTrajectory->m_acceleration * dt);
                    baseOffset = getOffset(*currentTrajectory);
                    obe::Collision::CollisionData collData;
                    collData.offset = baseOffset;
                    if (m_probe != nullptr)
                    {
                        collData
                            = m_probe->getMaximumDistanceBeforeCollision(collData.offset);
                    }
                    auto onCollideCallback = trajectory.second->getOnCollideCallback();
                    if (collData.offset != baseOffset && onCollideCallback)
                    {
                        onCollideCallback(
                            *trajectory.second.get(), baseOffset, collData);
                    }
                    m_sceneNode.move(collData.offset);
                }
            }
        }
    }

    Scene::SceneNode& TrajectoryNode::getSceneNode() const
    {
        return m_sceneNode;
    }
} // namespace obe::Collision
