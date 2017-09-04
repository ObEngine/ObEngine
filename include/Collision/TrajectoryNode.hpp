#pragma once

#include <map>

#include <kaguya/kaguya.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Transform/Node2D.hpp>

namespace obe
{
    namespace Collision
    {
        class TrajectoryNode
        {
        private:
            std::map<std::string, std::pair<std::unique_ptr<Trajectory>, std::vector<kaguya::LuaFunction>>> m_trajectories;
            PolygonalCollider* m_probe = nullptr;
            Transform::Node2D* m_sceneNode;
            kaguya::LuaFunction m_onCollideCallback;
        public:
            TrajectoryNode(Transform::Node2D* sceneNode);
            void setProbe(PolygonalCollider* probe);
            Trajectory* addTrajectory(const std::string& id, Transform::Units unit = Transform::Units::WorldUnits);
            void addCheck(const std::string& id, kaguya::LuaFunction check);
            void onCollide(kaguya::LuaFunction callback);
            Trajectory* getTrajectory(const std::string& id);
            void removeTrajectory(const std::string& id);
            void update(double dt);
            Transform::Node2D* getSceneNode() const;
        };
    }
}
