#include <Bindings/obe/collision/Collision.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::collision::bindings
{
    void load_enum_collider_tag_type(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        collision_namespace.new_enum<obe::collision::ColliderTagType>("ColliderTagType",
            { { "Tag", obe::collision::ColliderTagType::Tag },
                { "Accepted", obe::collision::ColliderTagType::Accepted },
                { "Rejected", obe::collision::ColliderTagType::Rejected } });
    }
    void load_class_collision_data(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::CollisionData> bind_collision_data
            = collision_namespace.new_usertype<obe::collision::CollisionData>(
                "CollisionData", sol::call_constructor, sol::default_constructor);
        bind_collision_data["colliders"] = &obe::collision::CollisionData::colliders;
        bind_collision_data["offset"] = &obe::collision::CollisionData::offset;
    }
    void load_class_polygonal_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::PolygonalCollider> bind_polygonal_collider
            = collision_namespace.new_usertype<obe::collision::PolygonalCollider>(
                "PolygonalCollider", sol::base_classes,
                sol::bases<obe::transform::Polygon, obe::transform::UnitBasedObject,
                    obe::transform::Movable, obe::types::Selectable,
                    obe::component::Component<obe::collision::PolygonalCollider>,
                    obe::component::ComponentBase, obe::types::Identifiable,
                    obe::types::Serializable>());
        bind_polygonal_collider["add_tag"] = &obe::collision::PolygonalCollider::add_tag;
        bind_polygonal_collider["clear_tags"] = &obe::collision::PolygonalCollider::clear_tags;
        bind_polygonal_collider["does_collide"] = sol::overload(
            static_cast<obe::collision::CollisionData (obe::collision::PolygonalCollider::*)(
                const obe::transform::UnitVector&) const>(
                &obe::collision::PolygonalCollider::does_collide),
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset) -> bool {
                return self->does_collide(collider, offset);
            },
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset, const bool perform_aabb_filter) -> bool {
                return self->does_collide(collider, offset, perform_aabb_filter);
            });
        bind_polygonal_collider["matches_any_tag"]
            = &obe::collision::PolygonalCollider::matches_any_tag;
        bind_polygonal_collider["contains_tag"] = &obe::collision::PolygonalCollider::contains_tag;
        bind_polygonal_collider["get_all_tags"] = &obe::collision::PolygonalCollider::get_all_tags;
        bind_polygonal_collider["get_distance_before_collision"] = sol::overload(
            static_cast<obe::collision::CollisionData (obe::collision::PolygonalCollider::*)(
                const obe::transform::UnitVector&) const>(
                &obe::collision::PolygonalCollider::get_distance_before_collision),
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset) -> obe::transform::UnitVector {
                return self->get_distance_before_collision(collider, offset);
            },
            [](obe::collision::PolygonalCollider* self, obe::collision::PolygonalCollider& collider,
                const obe::transform::UnitVector& offset,
                const bool perform_aabb_filter) -> obe::transform::UnitVector {
                return self->get_distance_before_collision(collider, offset, perform_aabb_filter);
            });
        bind_polygonal_collider["get_parent_id"]
            = &obe::collision::PolygonalCollider::get_parent_id;
        bind_polygonal_collider["schema"] = &obe::collision::PolygonalCollider::schema;
        bind_polygonal_collider["dump"] = &obe::collision::PolygonalCollider::dump;
        bind_polygonal_collider["load"] = &obe::collision::PolygonalCollider::load;
        bind_polygonal_collider["remove_tag"] = &obe::collision::PolygonalCollider::remove_tag;
        bind_polygonal_collider["set_parent_id"]
            = &obe::collision::PolygonalCollider::set_parent_id;
        bind_polygonal_collider["type"] = &obe::collision::PolygonalCollider::type;
        bind_polygonal_collider["get_bounding_box"]
            = &obe::collision::PolygonalCollider::get_bounding_box;
        bind_polygonal_collider["add_point"] = sol::overload(
            [](obe::collision::PolygonalCollider* self, const obe::transform::UnitVector& position)
                -> void { return self->add_point(position); },
            [](obe::collision::PolygonalCollider* self, const obe::transform::UnitVector& position,
                int point_index) -> void { return self->add_point(position, point_index); });
        bind_polygonal_collider["move"] = &obe::collision::PolygonalCollider::move;
        bind_polygonal_collider["rotate"] = &obe::collision::PolygonalCollider::rotate;
        bind_polygonal_collider["set_position"] = &obe::collision::PolygonalCollider::set_position;
        bind_polygonal_collider["set_rotation"] = &obe::collision::PolygonalCollider::set_rotation;
        bind_polygonal_collider["set_position_from_centroid"]
            = &obe::collision::PolygonalCollider::set_position_from_centroid;

        PolygonalCollider::Register();
    }
    void load_class_trajectory(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::Trajectory> bind_trajectory
            = collision_namespace.new_usertype<obe::collision::Trajectory>("Trajectory",
                sol::call_constructor,
                sol::constructors<obe::collision::Trajectory(),
                    obe::collision::Trajectory(obe::transform::Units)>(),
                sol::base_classes, sol::bases<obe::types::Togglable>());
        bind_trajectory["add_acceleration"] = &obe::collision::Trajectory::add_acceleration;
        bind_trajectory["add_angle"] = &obe::collision::Trajectory::add_angle;
        bind_trajectory["add_check"] = &obe::collision::Trajectory::add_check;
        bind_trajectory["add_speed"] = &obe::collision::Trajectory::add_speed;
        bind_trajectory["get_acceleration"] = &obe::collision::Trajectory::get_acceleration;
        bind_trajectory["get_angle"] = &obe::collision::Trajectory::get_angle;
        bind_trajectory["get_checks"] = &obe::collision::Trajectory::get_checks;
        bind_trajectory["get_on_collide_callback"]
            = &obe::collision::Trajectory::get_on_collide_callback;
        bind_trajectory["get_speed"] = &obe::collision::Trajectory::get_speed;
        bind_trajectory["is_static"] = &obe::collision::Trajectory::is_static;
        bind_trajectory["get_unit"] = &obe::collision::Trajectory::get_unit;
        bind_trajectory["on_collide"] = &obe::collision::Trajectory::on_collide;
        bind_trajectory["set_acceleration"] = &obe::collision::Trajectory::set_acceleration;
        bind_trajectory["set_angle"] = &obe::collision::Trajectory::set_angle;
        bind_trajectory["set_speed"] = &obe::collision::Trajectory::set_speed;
        bind_trajectory["set_static"] = &obe::collision::Trajectory::set_static;
    }
    void load_class_trajectory_node(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::TrajectoryNode> bind_trajectory_node
            = collision_namespace.new_usertype<obe::collision::TrajectoryNode>("TrajectoryNode",
                sol::call_constructor,
                sol::constructors<obe::collision::TrajectoryNode(obe::scene::SceneNode&)>());
        bind_trajectory_node["add_trajectory"]
            = sol::overload([](obe::collision::TrajectoryNode* self, const std::string& id)
                                -> obe::collision::Trajectory& { return self->add_trajectory(id); },
                [](obe::collision::TrajectoryNode* self, const std::string& id,
                    obe::transform::Units unit) -> obe::collision::Trajectory& {
                    return self->add_trajectory(id, unit);
                });
        bind_trajectory_node["get_scene_node"] = &obe::collision::TrajectoryNode::get_scene_node;
        bind_trajectory_node["get_trajectory"] = &obe::collision::TrajectoryNode::get_trajectory;
        bind_trajectory_node["remove_trajectory"]
            = &obe::collision::TrajectoryNode::remove_trajectory;
        bind_trajectory_node["set_probe"] = &obe::collision::TrajectoryNode::set_probe;
        bind_trajectory_node["update"] = &obe::collision::TrajectoryNode::update;
    }
};