#include <Bindings/obe/Collision/Collision.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::Collision::Bindings
{
    void LoadEnumColliderTagType(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["Collision"].get<sol::table>();
        CollisionNamespace.new_enum<obe::Collision::ColliderTagType>("ColliderTagType",
            { { "Tag", obe::Collision::ColliderTagType::Tag },
                { "Accepted", obe::Collision::ColliderTagType::Accepted },
                { "Rejected", obe::Collision::ColliderTagType::Rejected } });
    }
    void LoadClassCollisionData(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["Collision"].get<sol::table>();
        sol::usertype<obe::Collision::CollisionData> bindCollisionData
            = CollisionNamespace.new_usertype<obe::Collision::CollisionData>(
                "CollisionData", sol::call_constructor, sol::default_constructor);
        bindCollisionData["colliders"] = &obe::Collision::CollisionData::colliders;
        bindCollisionData["offset"] = &obe::Collision::CollisionData::offset;
    }
    void LoadClassInnerTest(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["Collision"].get<sol::table>();
        sol::usertype<obe::Collision::InnerTest> bindInnerTest
            = CollisionNamespace.new_usertype<obe::Collision::InnerTest>(
                "InnerTest", sol::call_constructor, sol::default_constructor);
        bindInnerTest["build"] = &obe::Collision::InnerTest::build;
    }
    void LoadClassCoolChild(sol::state_view state)
    {
        sol::table InnerTestNamespace = state["obe"]["Collision"]["InnerTest"].get<sol::table>();
        sol::usertype<obe::Collision::InnerTest::CoolChild> bindCoolChild
            = InnerTestNamespace.new_usertype<obe::Collision::InnerTest::CoolChild>(
                "CoolChild", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassPolygonalCollider(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["Collision"].get<sol::table>();
        sol::usertype<obe::Collision::PolygonalCollider> bindPolygonalCollider
            = CollisionNamespace.new_usertype<obe::Collision::PolygonalCollider>(
                "PolygonalCollider", sol::base_classes,
                sol::bases<obe::Transform::Polygon, obe::Transform::UnitBasedObject,
                    obe::Transform::Movable, obe::Types::Selectable,
                    obe::Component::Component<obe::Collision::PolygonalCollider>,
                    obe::Component::ComponentBase, obe::Types::Identifiable,
                    obe::Types::Serializable>());
        bindPolygonalCollider["operator="] = &obe::Collision::PolygonalCollider::operator=;
        bindPolygonalCollider["addTag"] = &obe::Collision::PolygonalCollider::addTag;
        bindPolygonalCollider["clearTags"] = &obe::Collision::PolygonalCollider::clearTags;
        bindPolygonalCollider["doesCollide"] = sol::overload(
            static_cast<obe::Collision::CollisionData (obe::Collision::PolygonalCollider::*)(
                const obe::Transform::UnitVector&) const>(
                &obe::Collision::PolygonalCollider::doesCollide),
            [](obe::Collision::PolygonalCollider* self, obe::Collision::PolygonalCollider& collider,
                const obe::Transform::UnitVector& offset) -> bool {
                return self->doesCollide(collider, offset);
            },
            [](obe::Collision::PolygonalCollider* self, obe::Collision::PolygonalCollider& collider,
                const obe::Transform::UnitVector& offset, const bool doAABBfilter) -> bool {
                return self->doesCollide(collider, offset, doAABBfilter);
            });
        bindPolygonalCollider["doesHaveAnyTag"]
            = &obe::Collision::PolygonalCollider::doesHaveAnyTag;
        bindPolygonalCollider["doesHaveTag"] = &obe::Collision::PolygonalCollider::doesHaveTag;
        bindPolygonalCollider["dump"] = &obe::Collision::PolygonalCollider::dump;
        bindPolygonalCollider["getAllTags"] = &obe::Collision::PolygonalCollider::getAllTags;
        bindPolygonalCollider["getMaximumDistanceBeforeCollision"] = sol::overload(
            static_cast<obe::Collision::CollisionData (obe::Collision::PolygonalCollider::*)(
                const obe::Transform::UnitVector&) const>(
                &obe::Collision::PolygonalCollider::getMaximumDistanceBeforeCollision),
            [](obe::Collision::PolygonalCollider* self, obe::Collision::PolygonalCollider& collider,
                const obe::Transform::UnitVector& offset) -> obe::Transform::UnitVector {
                return self->getMaximumDistanceBeforeCollision(collider, offset);
            },
            [](obe::Collision::PolygonalCollider* self, obe::Collision::PolygonalCollider& collider,
                const obe::Transform::UnitVector& offset,
                const bool doAABBfilter) -> obe::Transform::UnitVector {
                return self->getMaximumDistanceBeforeCollision(collider, offset, doAABBfilter);
            });
        bindPolygonalCollider["getParentId"] = &obe::Collision::PolygonalCollider::getParentId;
        bindPolygonalCollider["load"] = &obe::Collision::PolygonalCollider::load;
        bindPolygonalCollider["removeTag"] = &obe::Collision::PolygonalCollider::removeTag;
        bindPolygonalCollider["setParentId"] = &obe::Collision::PolygonalCollider::setParentId;
        bindPolygonalCollider["type"] = &obe::Collision::PolygonalCollider::type;
        bindPolygonalCollider["getBoundingBox"]
            = &obe::Collision::PolygonalCollider::getBoundingBox;
        bindPolygonalCollider["addPoint"] = sol::overload(
            [](obe::Collision::PolygonalCollider* self, const obe::Transform::UnitVector& position)
                -> void { return self->addPoint(position); },
            [](obe::Collision::PolygonalCollider* self, const obe::Transform::UnitVector& position,
                int pointIndex) -> void { return self->addPoint(position, pointIndex); });
        bindPolygonalCollider["move"] = &obe::Collision::PolygonalCollider::move;
        bindPolygonalCollider["rotate"] = &obe::Collision::PolygonalCollider::rotate;
        bindPolygonalCollider["setPosition"] = &obe::Collision::PolygonalCollider::setPosition;
        bindPolygonalCollider["setRotation"] = &obe::Collision::PolygonalCollider::setRotation;
        bindPolygonalCollider["setPositionFromCentroid"]
            = &obe::Collision::PolygonalCollider::setPositionFromCentroid;
    }
    void LoadClassTrajectory(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["Collision"].get<sol::table>();
        sol::usertype<obe::Collision::Trajectory> bindTrajectory
            = CollisionNamespace.new_usertype<obe::Collision::Trajectory>("Trajectory",
                sol::call_constructor,
                sol::constructors<obe::Collision::Trajectory(),
                    obe::Collision::Trajectory(obe::Transform::Units)>(),
                sol::base_classes, sol::bases<obe::Types::Togglable>());
        bindTrajectory["addAcceleration"] = &obe::Collision::Trajectory::addAcceleration;
        bindTrajectory["addAngle"] = &obe::Collision::Trajectory::addAngle;
        bindTrajectory["addCheck"] = &obe::Collision::Trajectory::addCheck;
        bindTrajectory["addSpeed"] = &obe::Collision::Trajectory::addSpeed;
        bindTrajectory["getAcceleration"] = &obe::Collision::Trajectory::getAcceleration;
        bindTrajectory["getAngle"] = &obe::Collision::Trajectory::getAngle;
        bindTrajectory["getChecks"] = &obe::Collision::Trajectory::getChecks;
        bindTrajectory["getOnCollideCallback"] = &obe::Collision::Trajectory::getOnCollideCallback;
        bindTrajectory["getSpeed"] = &obe::Collision::Trajectory::getSpeed;
        bindTrajectory["getStatic"] = &obe::Collision::Trajectory::getStatic;
        bindTrajectory["getUnit"] = &obe::Collision::Trajectory::getUnit;
        bindTrajectory["onCollide"] = &obe::Collision::Trajectory::onCollide;
        bindTrajectory["setAcceleration"] = &obe::Collision::Trajectory::setAcceleration;
        bindTrajectory["setAngle"] = &obe::Collision::Trajectory::setAngle;
        bindTrajectory["setSpeed"] = &obe::Collision::Trajectory::setSpeed;
        bindTrajectory["setStatic"] = &obe::Collision::Trajectory::setStatic;
    }
    void LoadClassTrajectoryNode(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["Collision"].get<sol::table>();
        sol::usertype<obe::Collision::TrajectoryNode> bindTrajectoryNode
            = CollisionNamespace.new_usertype<obe::Collision::TrajectoryNode>("TrajectoryNode",
                sol::call_constructor,
                sol::constructors<obe::Collision::TrajectoryNode(obe::Scene::SceneNode&)>());
        bindTrajectoryNode["addTrajectory"]
            = sol::overload([](obe::Collision::TrajectoryNode* self, const std::string& id)
                                -> obe::Collision::Trajectory& { return self->addTrajectory(id); },
                [](obe::Collision::TrajectoryNode* self, const std::string& id,
                    obe::Transform::Units unit) -> obe::Collision::Trajectory& {
                    return self->addTrajectory(id, unit);
                });
        bindTrajectoryNode["getSceneNode"] = &obe::Collision::TrajectoryNode::getSceneNode;
        bindTrajectoryNode["getTrajectory"] = &obe::Collision::TrajectoryNode::getTrajectory;
        bindTrajectoryNode["removeTrajectory"] = &obe::Collision::TrajectoryNode::removeTrajectory;
        bindTrajectoryNode["setProbe"] = &obe::Collision::TrajectoryNode::setProbe;
        bindTrajectoryNode["update"] = &obe::Collision::TrajectoryNode::update;
    }
};