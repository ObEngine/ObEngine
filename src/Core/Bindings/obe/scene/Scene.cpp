#include <Bindings/obe/scene/Scene.hpp>

#include <Scene/Camera.hpp>
#include <Scene/Scene.hpp>
#include <Scene/SceneNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::scene::bindings
{
    void load_class_camera(sol::state_view state)
    {
        sol::table scene_namespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::Camera> bind_camera
            = scene_namespace.new_usertype<obe::scene::Camera>("Camera", sol::call_constructor,
                sol::constructors<obe::scene::Camera()>(), sol::base_classes,
                sol::bases<obe::transform::AABB, obe::transform::Movable>());
        bind_camera["move"] = &obe::scene::Camera::move;
        bind_camera["scale"] = sol::overload(
            [](obe::scene::Camera* self, double scale_) -> void { return self->scale(scale_); },
            [](obe::scene::Camera* self, double scale_, const obe::transform::Referential& ref)
                -> void { return self->scale(scale_, ref); });
        bind_camera["set_position"] = sol::overload(
            [](obe::scene::Camera* self, const obe::transform::Vector2& position) -> void {
                return self->set_position(position);
            },
            [](obe::scene::Camera* self, const obe::transform::Vector2& position,
                const obe::transform::Referential& ref) -> void {
                return self->set_position(position, ref);
            });
        bind_camera["set_size"] = sol::overload(
            [](obe::scene::Camera* self, double size) -> void { return self->set_size(size); },
            [](obe::scene::Camera* self, double size, const obe::transform::Referential& ref)
                -> void { return self->set_size(size, ref); });
    }
    void load_class_scene(sol::state_view state)
    {
        sol::table scene_namespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::Scene> bind_scene
            = scene_namespace.new_usertype<obe::scene::Scene>("Scene", sol::call_constructor,
                sol::constructors<obe::scene::Scene(
                    obe::event::EventNamespace&, sol::state_view)>(),
                sol::base_classes,
                sol::bases<obe::types::Serializable, obe::engine::ResourceManagedObject>());
        bind_scene["load_from_file"]
            = sol::overload(static_cast<void (obe::scene::Scene::*)(const std::string&)>(
                                &obe::scene::Scene::set_future_load_from_file),
                static_cast<void (obe::scene::Scene::*)(
                    const std::string&, const obe::scene::OnSceneLoadCallback&)>(
                    &obe::scene::Scene::set_future_load_from_file));
        bind_scene["clear"] = &obe::scene::Scene::clear;
        bind_scene["schema"] = &obe::scene::Scene::schema;
        bind_scene["dump"] = &obe::scene::Scene::dump;
        bind_scene["load"] = &obe::scene::Scene::load;
        bind_scene["set_future_load"] = &obe::scene::Scene::set_future_load;
        bind_scene["update"] = &obe::scene::Scene::update;
        bind_scene["draw"] = &obe::scene::Scene::draw;
        bind_scene["get_level_name"] = &obe::scene::Scene::get_level_name;
        bind_scene["set_level_name"] = &obe::scene::Scene::set_level_name;
        bind_scene["set_update_state"] = &obe::scene::Scene::set_update_state;
        bind_scene["create_game_object"] = sol::overload(
            [](obe::scene::Scene* self, const std::string& object_type) -> sol::function {
                return obe::scene::scene_create_game_object_proxy(self, object_type);
            },
            [](obe::scene::Scene* self, const std::string& object_type,
                const std::string& id) -> sol::function {
                return obe::scene::scene_create_game_object_proxy(self, object_type, id);
            });
        bind_scene["get_game_object_amount"] = &obe::scene::Scene::get_game_object_amount;
        bind_scene["get_all_game_objects"] = sol::overload(
            [](const obe::scene::Scene* self) -> sol::nested<std::vector<sol::table>> {
                return obe::scene::scene_get_all_game_objects_proxy(self);
            },
            [](const obe::scene::Scene* self,
                const std::string& object_type) -> sol::nested<std::vector<sol::table>> {
                return obe::scene::scene_get_all_game_objects_proxy(self, object_type);
            });
        bind_scene["get_game_object"] = &obe::scene::scene_get_game_object_proxy;
        bind_scene["does_game_object_exists"] = &obe::scene::Scene::does_game_object_exists;
        bind_scene["remove_game_object"] = &obe::scene::Scene::remove_game_object;
        bind_scene["get_camera"] = &obe::scene::Scene::get_camera;
        bind_scene["reorganize_layers"] = &obe::scene::Scene::reorganize_layers;
        bind_scene["create_sprite"] = sol::overload(
            [](obe::scene::Scene* self) -> obe::graphics::Sprite& { return self->create_sprite(); },
            [](obe::scene::Scene* self, const std::string& id) -> obe::graphics::Sprite& {
                return self->create_sprite(id);
            },
            [](obe::scene::Scene* self, const std::string& id, bool add_to_scene_root)
                -> obe::graphics::Sprite& { return self->create_sprite(id, add_to_scene_root); });
        bind_scene["get_sprite_amount"] = &obe::scene::Scene::get_sprite_amount;
        bind_scene["get_all_sprites"] = &obe::scene::Scene::get_all_sprites;
        bind_scene["get_sprites_by_layer"] = &obe::scene::Scene::get_sprites_by_layer;
        bind_scene["get_sprite_by_position"] = &obe::scene::Scene::get_sprite_by_position;
        bind_scene["get_sprite"] = &obe::scene::Scene::get_sprite;
        bind_scene["does_sprite_exists"] = &obe::scene::Scene::does_sprite_exists;
        bind_scene["remove_sprite"] = &obe::scene::Scene::remove_sprite;
        bind_scene["create_collider"] = sol::overload(
            [](obe::scene::Scene* self) -> obe::collision::ColliderComponent& {
                return self->create_collider();
            },
            [](obe::scene::Scene* self, const std::string& id)
                -> obe::collision::ColliderComponent& { return self->create_collider(id); },
            [](obe::scene::Scene* self, const std::string& id,
                bool add_to_scene_root) -> obe::collision::ColliderComponent& {
                return self->create_collider(id, add_to_scene_root);
            });
        bind_scene["get_collider_amount"] = &obe::scene::Scene::get_collider_amount;
        bind_scene["get_all_colliders"] = &obe::scene::Scene::get_all_colliders;
        bind_scene["get_collider"] = &obe::scene::Scene::get_collider;
        bind_scene["does_collider_exists"] = &obe::scene::Scene::does_collider_exists;
        bind_scene["remove_collider"] = &obe::scene::Scene::remove_collider;
        bind_scene["get_collision_space"] = &obe::scene::Scene::get_collision_space;
        bind_scene["get_scene_root_node"] = &obe::scene::Scene::get_scene_root_node;
        bind_scene["get_filesystem_path"] = &obe::scene::Scene::get_filesystem_path;
        bind_scene["reload"]
            = sol::overload(static_cast<void (obe::scene::Scene::*)()>(&obe::scene::Scene::reload),
                static_cast<void (obe::scene::Scene::*)(const obe::scene::OnSceneLoadCallback&)>(
                    &obe::scene::Scene::reload));
        bind_scene["get_level_file"] = &obe::scene::Scene::get_level_file;
        bind_scene["get_scene_node_by_position"] = &obe::scene::Scene::get_scene_node_by_position;
        bind_scene["has_tiles"] = &obe::scene::Scene::has_tiles;
        bind_scene["get_tiles"] = [](obe::scene::Scene* self) -> const obe::tiles::TileScene* {
            return &self->get_tiles();
        };
        bind_scene["get_render_options"] = &obe::scene::Scene::get_render_options;
        bind_scene["set_render_options"] = &obe::scene::Scene::set_render_options;
        bind_scene["get_component"] = &obe::scene::Scene::get_component;
    }
    void load_class_scene_node(sol::state_view state)
    {
        sol::table scene_namespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::SceneNode> bind_scene_node
            = scene_namespace.new_usertype<obe::scene::SceneNode>("SceneNode",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<obe::transform::Movable>());
        bind_scene_node["add_child"] = &obe::scene::SceneNode::add_child;
        bind_scene_node["remove_child"] = &obe::scene::SceneNode::remove_child;
        bind_scene_node["set_position"] = &obe::scene::SceneNode::set_position;
        bind_scene_node["move"] = &obe::scene::SceneNode::move;
        bind_scene_node["set_position_without_children"]
            = &obe::scene::SceneNode::set_position_without_children;
        bind_scene_node["move_without_children"] = &obe::scene::SceneNode::move_without_children;
    }
    void load_class_scene_render_options(sol::state_view state)
    {
        sol::table scene_namespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::SceneRenderOptions> bind_scene_render_options
            = scene_namespace.new_usertype<obe::scene::SceneRenderOptions>(
                "SceneRenderOptions", sol::call_constructor, sol::default_constructor);
        bind_scene_render_options["sprites"] = &obe::scene::SceneRenderOptions::sprites;
        bind_scene_render_options["collisions"] = &obe::scene::SceneRenderOptions::collisions;
        bind_scene_render_options["scene_nodes"] = &obe::scene::SceneRenderOptions::scene_nodes;
    }
};