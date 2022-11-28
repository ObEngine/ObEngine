#include <Bindings/obe/collision/Collision.hpp>

#include <Collision/CapsuleCollider.hpp>
#include <Collision/CircleCollider.hpp>
#include <Collision/Collider.hpp>
#include <Collision/ColliderComponent.hpp>
#include <Collision/CollisionSpace.hpp>
#include <Collision/ComplexPolygonCollider.hpp>
#include <Collision/PolygonCollider.hpp>
#include <Collision/Quadtree.hpp>
#include <Collision/RectangleCollider.hpp>
#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::collision::bindings
{
    void load_enum_collider_type(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        collision_namespace.new_enum<obe::collision::ColliderType>("ColliderType",
            { { "Collider", obe::collision::ColliderType::Collider },
                { "Circle", obe::collision::ColliderType::Circle },
                { "Rectangle", obe::collision::ColliderType::Rectangle },
                { "Capsule", obe::collision::ColliderType::Capsule },
                { "Polygon", obe::collision::ColliderType::Polygon } });
    }
    void load_class_capsule_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::CapsuleCollider> bind_capsule_collider
            = collision_namespace.new_usertype<obe::collision::CapsuleCollider>("CapsuleCollider",
                sol::call_constructor, sol::constructors<obe::collision::CapsuleCollider()>(),
                sol::base_classes, sol::bases<obe::collision::Collider, obe::transform::Movable>());
        bind_capsule_collider["get_collider_type"]
            = &obe::collision::CapsuleCollider::get_collider_type;
        bind_capsule_collider["get_bounding_box"]
            = &obe::collision::CapsuleCollider::get_bounding_box;
        bind_capsule_collider["get_position"] = &obe::collision::CapsuleCollider::get_position;
        bind_capsule_collider["set_position"] = &obe::collision::CapsuleCollider::set_position;
        bind_capsule_collider["move"] = &obe::collision::CapsuleCollider::move;
        bind_capsule_collider["get_radius"] = &obe::collision::CapsuleCollider::get_radius;
        bind_capsule_collider["set_radius"] = &obe::collision::CapsuleCollider::set_radius;
        bind_capsule_collider["Type"] = sol::var(&obe::collision::CapsuleCollider::Type);
    }
    void load_class_circle_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::CircleCollider> bind_circle_collider
            = collision_namespace.new_usertype<obe::collision::CircleCollider>("CircleCollider",
                sol::call_constructor, sol::constructors<obe::collision::CircleCollider()>(),
                sol::base_classes, sol::bases<obe::collision::Collider, obe::transform::Movable>());
        bind_circle_collider["get_collider_type"]
            = &obe::collision::CircleCollider::get_collider_type;
        bind_circle_collider["get_bounding_box"]
            = &obe::collision::CircleCollider::get_bounding_box;
        bind_circle_collider["get_position"] = &obe::collision::CircleCollider::get_position;
        bind_circle_collider["set_position"] = &obe::collision::CircleCollider::set_position;
        bind_circle_collider["move"] = &obe::collision::CircleCollider::move;
        bind_circle_collider["get_radius"] = &obe::collision::CircleCollider::get_radius;
        bind_circle_collider["set_radius"] = &obe::collision::CircleCollider::set_radius;
        bind_circle_collider["Type"] = sol::var(&obe::collision::CircleCollider::Type);
    }
    void load_class_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::Collider> bind_collider
            = collision_namespace.new_usertype<obe::collision::Collider>(
                "Collider", sol::base_classes, sol::bases<obe::transform::Movable>());
        bind_collider["get_collider_type"] = &obe::collision::Collider::get_collider_type;
        bind_collider["set_tag"] = &obe::collision::Collider::set_tag;
        bind_collider["get_tag"] = &obe::collision::Collider::get_tag;
        bind_collider["collides"] = &obe::collision::Collider::collides;
        bind_collider["get_offset_before_collision"] = sol::overload(
            [](obe::collision::Collider* self,
                const obe::collision::Collider& collider) -> obe::transform::UnitVector {
                return self->get_offset_before_collision(collider);
            },
            [](obe::collision::Collider* self, const obe::collision::Collider& collider,
                const obe::transform::UnitVector& self_offset) -> obe::transform::UnitVector {
                return self->get_offset_before_collision(collider, self_offset);
            },
            [](obe::collision::Collider* self, const obe::collision::Collider& collider,
                const obe::transform::UnitVector& self_offset,
                const obe::transform::UnitVector& other_offset) -> obe::transform::UnitVector {
                return self->get_offset_before_collision(collider, self_offset, other_offset);
            });
        bind_collider["get_bounding_box"] = &obe::collision::Collider::get_bounding_box;
        bind_collider["copy"] = &obe::collision::Collider::copy;
    }
    void load_class_collider_component(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::ColliderComponent> bind_collider_component
            = collision_namespace.new_usertype<obe::collision::ColliderComponent>(
                "ColliderComponent", sol::base_classes,
                sol::bases<obe::component::Component<obe::collision::ColliderComponent>,
                    obe::component::ComponentBase, obe::types::Identifiable,
                    obe::types::Serializable, obe::types::UniqueIdentifiable>());
        bind_collider_component["dump"] = &obe::collision::ColliderComponent::dump;
        bind_collider_component["load"] = &obe::collision::ColliderComponent::load;
        bind_collider_component["get_collider_type"]
            = &obe::collision::ColliderComponent::get_collider_type;
        bind_collider_component["type"] = &obe::collision::ColliderComponent::type;
        bind_collider_component["get_capsule_collider"]
            = static_cast<obe::collision::CapsuleCollider* (
                obe::collision::ColliderComponent::*)()>(
                &obe::collision::ColliderComponent::get_inner_collider);
        ;
        bind_collider_component["get_circle_collider"]
            = static_cast<obe::collision::CircleCollider* (obe::collision::ColliderComponent::*)()>(
                &obe::collision::ColliderComponent::get_inner_collider);
        ;
        bind_collider_component["get_polygon_collider"]
            = static_cast<obe::collision::PolygonCollider* (
                obe::collision::ColliderComponent::*)()>(
                &obe::collision::ColliderComponent::get_inner_collider);
        ;
        bind_collider_component["get_rectangle_collider"]
            = static_cast<obe::collision::RectangleCollider* (
                obe::collision::ColliderComponent::*)()>(
                &obe::collision::ColliderComponent::get_inner_collider);
        ;
        bind_collider_component["get_inner_collider"] = sol::overload(
            static_cast<obe::collision::Collider* (obe::collision::ColliderComponent::*)()>(
                &obe::collision::ColliderComponent::get_inner_collider),
            static_cast<const obe::collision::Collider* (obe::collision::ColliderComponent::*)()
                    const>(&obe::collision::ColliderComponent::get_inner_collider));

        obe::collision::ColliderComponent::Register();
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
    void load_class_collision_space(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::CollisionSpace> bind_collision_space
            = collision_namespace.new_usertype<obe::collision::CollisionSpace>("CollisionSpace",
                sol::call_constructor, sol::constructors<obe::collision::CollisionSpace()>());
        bind_collision_space["add_collider"] = &obe::collision::CollisionSpace::add_collider;
        bind_collision_space["get_collider_amount"]
            = &obe::collision::CollisionSpace::get_collider_amount;
        bind_collision_space["get_all_colliders"]
            = &obe::collision::CollisionSpace::get_all_colliders;
        bind_collision_space["remove_collider"] = &obe::collision::CollisionSpace::remove_collider;
        bind_collision_space["collides"] = &obe::collision::CollisionSpace::collides;
        bind_collision_space["get_offset_before_collision"] = sol::overload(
            [](obe::collision::CollisionSpace* self,
                const obe::collision::Collider& collider) -> obe::transform::UnitVector {
                return self->get_offset_before_collision(collider);
            },
            [](obe::collision::CollisionSpace* self, const obe::collision::Collider& collider,
                const obe::transform::UnitVector& offset) -> obe::transform::UnitVector {
                return self->get_offset_before_collision(collider, offset);
            });
        bind_collision_space["add_tag_to_blacklist"]
            = &obe::collision::CollisionSpace::add_tag_to_blacklist;
        bind_collision_space["remove_tag_to_blacklist"]
            = &obe::collision::CollisionSpace::remove_tag_to_blacklist;
        bind_collision_space["clear_blacklist"] = &obe::collision::CollisionSpace::clear_blacklist;
        bind_collision_space["get_blacklist"] = &obe::collision::CollisionSpace::get_blacklist;
    }
    void load_class_complex_polygon_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
    }
    void load_class_polygon_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::PolygonCollider> bind_polygon_collider
            = collision_namespace.new_usertype<obe::collision::PolygonCollider>("PolygonCollider",
                sol::call_constructor,
                sol::constructors<obe::collision::PolygonCollider(),
                    obe::collision::PolygonCollider(const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::collision::Collider, obe::transform::Movable>());
        bind_polygon_collider["get_collider_type"]
            = &obe::collision::PolygonCollider::get_collider_type;
        bind_polygon_collider["get_bounding_box"]
            = &obe::collision::PolygonCollider::get_bounding_box;
        bind_polygon_collider["get_position"] = &obe::collision::PolygonCollider::get_position;
        bind_polygon_collider["set_position"] = &obe::collision::PolygonCollider::set_position;
        bind_polygon_collider["move"] = &obe::collision::PolygonCollider::move;
        bind_polygon_collider["add_point"] = sol::overload(
            [](obe::collision::PolygonCollider* self, const obe::transform::UnitVector& position)
                -> void { return self->add_point(position); },
            [](obe::collision::PolygonCollider* self, const obe::transform::UnitVector& position,
                int point_index) -> void { return self->add_point(position, point_index); });
        bind_polygon_collider["get_points_amount"]
            = &obe::collision::PolygonCollider::get_points_amount;
        bind_polygon_collider["get_polygon"] = &obe::collision::PolygonCollider::get_polygon;
        bind_polygon_collider["set_rotation"] = &obe::collision::PolygonCollider::set_rotation;
        bind_polygon_collider["rotate"] = &obe::collision::PolygonCollider::rotate;
        bind_polygon_collider["get_rotation"] = &obe::collision::PolygonCollider::get_rotation;
        bind_polygon_collider["Type"] = sol::var(&obe::collision::PolygonCollider::Type);
    }
    void load_class_quadtree(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::Quadtree> bind_quadtree
            = collision_namespace.new_usertype<obe::collision::Quadtree>("Quadtree",
                sol::call_constructor,
                sol::constructors<obe::collision::Quadtree(const obe::transform::AABB&)>());
        bind_quadtree["add"] = &obe::collision::Quadtree::add;
        bind_quadtree["remove"] = &obe::collision::Quadtree::remove;
        bind_quadtree["query"] = &obe::collision::Quadtree::query;
        bind_quadtree["find_all_intersections"] = &obe::collision::Quadtree::find_all_intersections;
    }
    void load_class_rectangle_collider(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::RectangleCollider> bind_rectangle_collider
            = collision_namespace.new_usertype<obe::collision::RectangleCollider>(
                "RectangleCollider", sol::call_constructor,
                sol::constructors<obe::collision::RectangleCollider(),
                    obe::collision::RectangleCollider(const obe::transform::UnitVector&),
                    obe::collision::RectangleCollider(
                        const obe::transform::UnitVector&, const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::collision::Collider, obe::transform::Movable>());
        bind_rectangle_collider["get_collider_type"]
            = &obe::collision::RectangleCollider::get_collider_type;
        bind_rectangle_collider["get_bounding_box"]
            = &obe::collision::RectangleCollider::get_bounding_box;
        bind_rectangle_collider["get_position"] = &obe::collision::RectangleCollider::get_position;
        bind_rectangle_collider["set_position"] = &obe::collision::RectangleCollider::set_position;
        bind_rectangle_collider["move"] = &obe::collision::RectangleCollider::move;
        bind_rectangle_collider["get_size"] = &obe::collision::RectangleCollider::get_size;
        bind_rectangle_collider["set_size"] = &obe::collision::RectangleCollider::set_size;
        bind_rectangle_collider["Type"] = sol::var(&obe::collision::RectangleCollider::Type);
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
        bind_trajectory["on_change"] = &obe::collision::Trajectory::on_change;
        bind_trajectory["set_acceleration"] = &obe::collision::Trajectory::set_acceleration;
        bind_trajectory["set_angle"] = &obe::collision::Trajectory::set_angle;
        bind_trajectory["set_speed"] = &obe::collision::Trajectory::set_speed;
        bind_trajectory["set_static"] = &obe::collision::Trajectory::set_static;
        bind_trajectory["get_tag"] = &obe::collision::Trajectory::get_tag;
        bind_trajectory["set_tag"] = &obe::collision::Trajectory::set_tag;
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
    void load_class_collision_rejection_pair(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        sol::usertype<obe::collision::CollisionRejectionPair> bind_collision_rejection_pair
            = collision_namespace.new_usertype<obe::collision::CollisionRejectionPair>(
                "CollisionRejectionPair", sol::call_constructor, sol::default_constructor);
        bind_collision_rejection_pair[sol::meta_function::call]
            = &obe::collision::CollisionRejectionPair::operator();
        bind_collision_rejection_pair["collider1"]
            = &obe::collision::CollisionRejectionPair::collider1;
        bind_collision_rejection_pair["collider2"]
            = &obe::collision::CollisionRejectionPair::collider2;
    }
    void load_function_collider_type_to_c2type(sol::state_view state)
    {
        sol::table collision_namespace = state["obe"]["collision"].get<sol::table>();
        collision_namespace.set_function(
            "collider_type_to_c2type", &obe::collision::collider_type_to_c2type);
    }
};