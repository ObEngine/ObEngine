#include <Bindings/obe/Collision/Collision.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::collision::Bindings
{
    void LoadEnumColliderTagType(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["collision"].get<sol::table>();
        CollisionNamespace.new_enum<obe::collision::ColliderTagType>("ColliderTagType",
            { { "Tag", obe::collision::ColliderTagType::Tag },
                { "Accepted", obe::collision::ColliderTagType::Accepted },
                { "Rejected", obe::collision::ColliderTagType::Rejected } });
    }
    void LoadClassCollisionData(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::CollisionData> bindCollisionData
            = CollisionNamespace.new_usertype<obe::collision::CollisionData>(
                "CollisionData", sol::call_constructor, sol::default_constructor);
        bindCollisionData["colliders"] = &obe::collision::CollisionData::colliders;
        bindCollisionData["offset"] = &obe::collision::CollisionData::offset;
    }
    void LoadClassPolygonalCollider(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::PolygonalCollider> bindPolygonalCollider
            = CollisionNamespace.new_usertype<obe::collision::PolygonalCollider>(
                "PolygonalCollider", sol::base_classes,
                sol::bases<obe::transform::Polygon, obe::transform::UnitBasedObject,
                    obe::transform::Movable, obe::Types::Selectable,
                    obe::Component::Component<obe::collision::PolygonalCollider>,
                    obe::Component::ComponentBase, obe::Types::Identifiable,
                    obe::Types::Serializable>());
        bindPolygonalCollider["add_tag"] = &obe::collision::PolygonalCollider::add_tag;
        bindPolygonalCollider["clear_tags"] = &obe::collision::PolygonalCollider::clear_tags;
        bindPolygonalCollider["does_collide"] = sol::overload(
            static_cast<obe::collision::CollisionData (obe::collision::PolygonalCollider::*)(
                const obe::transform::UnitVector&) const>(
                &obe::collision::PolygonalCollider::does_collide),
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset) -> bool {
                return self->does_collide(collider, offset);
            },
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset, const bool doAABBfilter) -> bool {
                return self->does_collide(collider, offset, doAABBfilter);
            });
        bindPolygonalCollider["matches_any_tag"]
            = &obe::collision::PolygonalCollider::matches_any_tag;
        bindPolygonalCollider["contains_tag"] = &obe::collision::PolygonalCollider::contains_tag;
        bindPolygonalCollider["dump"] = &obe::collision::PolygonalCollider::dump;
        bindPolygonalCollider["get_all_tags"] = &obe::collision::PolygonalCollider::get_all_tags;
        bindPolygonalCollider["get_distance_before_collision"] = sol::overload(
            static_cast<obe::collision::CollisionData (obe::collision::PolygonalCollider::*)(
                const obe::transform::UnitVector&) const>(
                &obe::collision::PolygonalCollider::get_distance_before_collision),
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset) -> obe::transform::UnitVector {
                return self->get_distance_before_collision(collider, offset);
            },
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset,
                const bool doAABBfilter) -> obe::transform::UnitVector {
                return self->get_distance_before_collision(collider, offset, doAABBfilter);
            });
        bindPolygonalCollider["get_parent_id"] = &obe::collision::PolygonalCollider::get_parent_id;
        bindPolygonalCollider["load"] = &obe::collision::PolygonalCollider::load;
        bindPolygonalCollider["remove_tag"] = &obe::collision::PolygonalCollider::remove_tag;
        bindPolygonalCollider["set_parent_id"] = &obe::collision::PolygonalCollider::set_parent_id;
        bindPolygonalCollider["type"] = &obe::collision::PolygonalCollider::type;
        bindPolygonalCollider["get_bounding_box"]
            = &obe::collision::PolygonalCollider::get_bounding_box;
        bindPolygonalCollider["add_point"] = sol::overload(
            [](obe::collision::PolygonalCollider* self, const obe::transform::UnitVector& position)
                -> void { return self->add_point(position); },
            [](obe::collision::PolygonalCollider* self, const obe::transform::UnitVector& position,
                int pointIndex) -> void { return self->add_point(position, pointIndex); });
        bindPolygonalCollider["move"] = &obe::collision::PolygonalCollider::move;
        bindPolygonalCollider["rotate"] = &obe::collision::PolygonalCollider::rotate;
        bindPolygonalCollider["set_position"] = &obe::collision::PolygonalCollider::set_position;
        bindPolygonalCollider["set_rotation"] = &obe::collision::PolygonalCollider::set_rotation;
        bindPolygonalCollider["set_position_from_centroid"]
            = &obe::collision::PolygonalCollider::set_position_from_centroid;

        PolygonalCollider::Register();
    }
    void LoadClassTrajectory(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::Trajectory> bindTrajectory
            = CollisionNamespace.new_usertype<obe::collision::Trajectory>("Trajectory",
                sol::call_constructor,
                sol::constructors<obe::collision::Trajectory(),
                    obe::collision::Trajectory(obe::transform::Units)>(),
                sol::base_classes, sol::bases<obe::Types::Togglable>());
        bindTrajectory["add_acceleration"] = &obe::collision::Trajectory::add_acceleration;
        bindTrajectory["add_angle"] = &obe::collision::Trajectory::add_angle;
        bindTrajectory["add_check"] = &obe::collision::Trajectory::add_check;
        bindTrajectory["add_speed"] = &obe::collision::Trajectory::add_speed;
        bindTrajectory["get_acceleration"] = &obe::collision::Trajectory::get_acceleration;
        bindTrajectory["get_angle"] = &obe::collision::Trajectory::get_angle;
        bindTrajectory["get_checks"] = &obe::collision::Trajectory::get_checks;
        bindTrajectory["get_on_collide_callback"] = &obe::collision::Trajectory::get_on_collide_callback;
        bindTrajectory["get_speed"] = &obe::collision::Trajectory::get_speed;
        bindTrajectory["is_static"] = &obe::collision::Trajectory::is_static;
        bindTrajectory["get_unit"] = &obe::collision::Trajectory::get_unit;
        bindTrajectory["on_collide"] = &obe::collision::Trajectory::on_collide;
        bindTrajectory["set_acceleration"] = &obe::collision::Trajectory::set_acceleration;
        bindTrajectory["set_angle"] = &obe::collision::Trajectory::set_angle;
        bindTrajectory["set_speed"] = &obe::collision::Trajectory::set_speed;
        bindTrajectory["set_static"] = &obe::collision::Trajectory::set_static;
    }
    void LoadClassTrajectoryNode(sol::state_view state)
    {
        sol::table CollisionNamespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::TrajectoryNode> bindTrajectoryNode
            = CollisionNamespace.new_usertype<obe::collision::TrajectoryNode>("TrajectoryNode",
                sol::call_constructor,
                sol::constructors<obe::collision::TrajectoryNode(obe::scene::SceneNode&)>());
        bindTrajectoryNode["add_trajectory"]
            = sol::overload([](obe::collision::TrajectoryNode* self, const std::string& id)
                                -> obe::collision::Trajectory& { return self->add_trajectory(id); },
                [](obe::collision::TrajectoryNode* self, const std::string& id,
                    obe::transform::Units unit) -> obe::collision::Trajectory& {
                    return self->add_trajectory(id, unit);
                });
        bindTrajectoryNode["get_scene_node"] = &obe::collision::TrajectoryNode::get_scene_node;
        bindTrajectoryNode["get_trajectory"] = &obe::collision::TrajectoryNode::get_trajectory;
        bindTrajectoryNode["remove_trajectory"] = &obe::collision::TrajectoryNode::remove_trajectory;
        bindTrajectoryNode["set_probe"] = &obe::collision::TrajectoryNode::set_probe;
        bindTrajectoryNode["update"] = &obe::collision::TrajectoryNode::update;
    }
};