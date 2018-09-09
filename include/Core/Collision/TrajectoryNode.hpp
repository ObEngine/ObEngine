#pragma once

#include <unordered_map>

#include <kaguya/kaguya.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Transform/SceneNode.hpp>

namespace obe::Collision
{
    /**
    * \brief A TrajectoryNode links
    */
    class TrajectoryNode
    {
    private:
        PolygonalCollider* m_probe = nullptr;
        Transform::SceneNode* m_sceneNode;
        std::unordered_map<std::string, std::unique_ptr<Trajectory>> m_trajectories;
    public:
        TrajectoryNode(Transform::SceneNode* sceneNode);
        Trajectory* addTrajectory(const std::string& id, Transform::Units unit = Transform::Units::WorldUnits);
        Transform::SceneNode* getSceneNode() const;
        Trajectory* getTrajectory(const std::string& id);
        void removeTrajectory(const std::string& id);
        void setProbe(PolygonalCollider* probe);
        void update(double dt);
    };
}