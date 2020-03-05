#include <Bindings/Bindings.hpp>
#include <Bindings/CollisionBindings.hpp>
#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>

#include <kaguya/another_binding_api.hpp>
#include <kaguya/kaguya.hpp>

namespace obe::Bindings::CollisionBindings
{
    void LoadTrajectory(kaguya::State* lua)
    {
        Load(lua, "obe.Togglable");
        (*lua)["obe"]["Trajectory"].setClass(
            kaguya::UserdataMetatable<Collision::Trajectory, Types::Togglable>()
                .addFunction("addAcceleration", &Collision::Trajectory::addAcceleration)
                .addFunction("addAngle", &Collision::Trajectory::addAngle)
                .addFunction("addCheck", &Collision::Trajectory::addCheck)
                .addFunction("addSpeed", &Collision::Trajectory::addSpeed)
                .addFunction("getAcceleration", &Collision::Trajectory::getAcceleration)
                .addFunction("getAngle", &Collision::Trajectory::getAngle)
                .addFunction("getSpeed", &Collision::Trajectory::getSpeed)
                .addFunction("getStatic", &Collision::Trajectory::getStatic)
                .addFunction("getUnit", &Collision::Trajectory::getUnit)
                .addFunction("onCollide", &Collision::Trajectory::onCollide)
                .addFunction("setAcceleration", &Collision::Trajectory::setAcceleration)
                .addFunction("setAngle", &Collision::Trajectory::setAngle)
                .addFunction("setSpeed", &Collision::Trajectory::setSpeed)
                .addFunction("setStatic", &Collision::Trajectory::setStatic));
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(TrajectoryNode_addTrajectory_wrapper,
        Collision::TrajectoryNode, addTrajectory, 1, 2);
    void LoadTrajectoryNode(kaguya::State* lua)
    {
        (*lua)["obe"]["TrajectoryNode"].setClass(
            kaguya::UserdataMetatable<Collision::TrajectoryNode>()
                .setConstructors<Collision::TrajectoryNode(Scene::SceneNode*)>()
                .addFunction("addTrajectory", TrajectoryNode_addTrajectory_wrapper())
                .addFunction("getSceneNode", &Collision::TrajectoryNode::getSceneNode)
                .addFunction("getTrajectory", &Collision::TrajectoryNode::getTrajectory)
                .addFunction(
                    "removeTrajectory", &Collision::TrajectoryNode::removeTrajectory)
                .addFunction("setProbe", &Collision::TrajectoryNode::setProbe)
                .addFunction("update", &Collision::TrajectoryNode::update));
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(
        PolygonalCollider_addPoint_wrapper, Collision::PolygonalCollider, addPoint, 1, 2);
    void LoadPolygonalCollider(kaguya::State* lua)
    {
        // <REVISION> PolygonalCollider should herit from Component (Make
        // Component Bindings)
        Load(lua, "obe.UnitBasedObject");
        Load(lua, "obe.Selectable");
        Load(lua, "obe.Serializable");
        Load(lua, "obe.Movable");
        Load(lua, "obe.Polygon");
        (*lua)["obe"]["PolygonalCollider"].setClass(
            kaguya::UserdataMetatable<Collision::PolygonalCollider,
                kaguya::MultipleBase<Transform::UnitBasedObject, Types::Selectable,
                    Transform::Movable, Types::Serializable, Types::Identifiable,
                    Transform::Polygon>>()
                .setConstructors<Collision::PolygonalCollider(const std::string&)>()

                .addFunction("addPoint", PolygonalCollider_addPoint_wrapper())
                .addFunction("addTag", &Collision::PolygonalCollider::addTag)
                .addFunction("clearTags", &Collision::PolygonalCollider::clearTags)
                .addOverloadedFunctions("doesCollide",
                    static_cast<bool (Collision::PolygonalCollider::*)(
                        const Transform::UnitVector&) const>(
                        &Collision::PolygonalCollider::doesCollide),
                    static_cast<bool (Collision::PolygonalCollider::*)(
                        Collision::PolygonalCollider&, const Transform::UnitVector&)
                            const>(&Collision::PolygonalCollider::doesCollide))
                .addFunction(
                    "doesHaveAnyTag", &Collision::PolygonalCollider::doesHaveAnyTag)
                .addFunction("doesHaveTag", &Collision::PolygonalCollider::doesHaveTag)
                .addFunction("getAllTags", &Collision::PolygonalCollider::getAllTags)
                .addOverloadedFunctions("getMaximumDistanceBeforeCollision",
                    static_cast<Transform::UnitVector (Collision::PolygonalCollider::*)(
                        const Transform::UnitVector&) const>(
                        &Collision::PolygonalCollider::getMaximumDistanceBeforeCollision),
                    static_cast<Transform::UnitVector (Collision::PolygonalCollider::*)(
                        Collision::PolygonalCollider&, const Transform::UnitVector&)
                            const>(
                        &Collision::PolygonalCollider::getMaximumDistanceBeforeCollision))
                .addFunction("getParentId", &Collision::PolygonalCollider::getParentId)
                .addFunction("removeTag", &Collision::PolygonalCollider::removeTag)
                .addFunction("setParentId", &Collision::PolygonalCollider::setParentId));

        (*lua)["obe"]["ColliderTagType"] = kaguya::NewTable();
        (*lua)["obe"]["ColliderTagType"]["Accepted"]
            = Collision::ColliderTagType::Accepted;
        (*lua)["obe"]["ColliderTagType"]["Rejected"]
            = Collision::ColliderTagType::Rejected;
        (*lua)["obe"]["ColliderTagType"]["Tag"] = Collision::ColliderTagType::Tag;
    }
} // namespace obe::Bindings::CollisionBindings