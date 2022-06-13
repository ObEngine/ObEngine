#include <Bindings/obe/Scene/Scene.hpp>

#include <Scene/Camera.hpp>
#include <Scene/Scene.hpp>
#include <Scene/SceneNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::scene::Bindings
{
    void LoadClassCamera(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::Camera> bindCamera
            = SceneNamespace.new_usertype<obe::scene::Camera>("Camera", sol::call_constructor,
                sol::constructors<obe::scene::Camera()>(), sol::base_classes,
                sol::bases<obe::Transform::Rect, obe::Transform::Movable>());
        bindCamera["get_position"] = sol::overload(
            [](obe::scene::Camera* self) -> obe::Transform::UnitVector {
                return self->get_position();
            },
            [](obe::scene::Camera* self, const obe::Transform::Referential& ref)
                -> obe::Transform::UnitVector { return self->get_position(ref); });
        bindCamera["get_size"] = &obe::scene::Camera::get_size;
        bindCamera["move"] = &obe::scene::Camera::move;
        bindCamera["scale"] = sol::overload(
            [](obe::scene::Camera* self, double pScale) -> void { return self->scale(pScale); },
            [](obe::scene::Camera* self, double pScale, const obe::Transform::Referential& ref)
                -> void { return self->scale(pScale, ref); });
        bindCamera["set_position"] = sol::overload(
            [](obe::scene::Camera* self, const obe::Transform::UnitVector& position) -> void {
                return self->set_position(position);
            },
            [](obe::scene::Camera* self, const obe::Transform::UnitVector& position,
                const obe::Transform::Referential& ref) -> void {
                return self->set_position(position, ref);
            });
        bindCamera["set_size"] = sol::overload(
            [](obe::scene::Camera* self, double pSize) -> void { return self->set_size(pSize); },
            [](obe::scene::Camera* self, double pSize, const obe::Transform::Referential& ref)
                -> void { return self->set_size(pSize, ref); });
    }
    void LoadClassScene(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::Scene> bindScene = SceneNamespace.new_usertype<obe::scene::Scene>(
            "Scene", sol::call_constructor,
            sol::constructors<obe::scene::Scene(obe::event::EventNamespace&, sol::state_view)>(),
            sol::base_classes, sol::bases<obe::Types::Serializable>());
        bindScene["attach_resource_manager"] = &obe::scene::Scene::attach_resource_manager;
        bindScene["load_from_file"]
            = sol::overload(static_cast<void (obe::scene::Scene::*)(const std::string&)>(
                                &obe::scene::Scene::set_future_load_from_file),
                static_cast<void (obe::scene::Scene::*)(
                    const std::string&, const obe::scene::OnSceneLoadCallback&)>(
                    &obe::scene::Scene::set_future_load_from_file));
        bindScene["clear"] = &obe::scene::Scene::clear;
        bindScene["dump"] = &obe::scene::Scene::dump;
        bindScene["load"] = &obe::scene::Scene::load;
        bindScene["update"] = &obe::scene::Scene::update;
        bindScene["draw"] = &obe::scene::Scene::draw;
        bindScene["get_level_name"] = &obe::scene::Scene::get_level_name;
        bindScene["set_level_name"] = &obe::scene::Scene::set_level_name;
        bindScene["set_update_state"] = &obe::scene::Scene::set_update_state;
        bindScene["create_game_object"] = sol::overload(
            [](obe::scene::Scene* self, const std::string& obj) -> sol::function {
                return obe::scene::scene_create_game_object_proxy(self, obj);
            },
            [](obe::scene::Scene* self, const std::string& obj, const std::string& id)
                -> sol::function { return obe::scene::scene_create_game_object_proxy(self, obj, id); });
        bindScene["get_game_object_amount"] = &obe::scene::Scene::get_game_object_amount;
        bindScene["get_all_game_objects"] = sol::overload(
            [](obe::scene::Scene* self) -> sol::nested<std::vector<sol::table>> {
                return obe::scene::scene_get_all_game_objects_proxy(self);
            },
            [](obe::scene::Scene* self,
                const std::string& objectType) -> sol::nested<std::vector<sol::table>> {
                return obe::scene::scene_get_all_game_objects_proxy(self, objectType);
            });
        bindScene["get_game_object"] = &obe::scene::scene_get_game_object_proxy;
        bindScene["does_game_object_exists"] = &obe::scene::Scene::does_game_object_exists;
        bindScene["remove_game_object"] = &obe::scene::Scene::remove_game_object;
        bindScene["get_camera"] = &obe::scene::Scene::get_camera;
        bindScene["reorganize_layers"] = &obe::scene::Scene::reorganize_layers;
        bindScene["create_sprite"] = sol::overload(
            [](obe::scene::Scene* self) -> obe::graphics::Sprite& { return self->create_sprite(); },
            [](obe::scene::Scene* self, const std::string& id) -> obe::graphics::Sprite& {
                return self->create_sprite(id);
            },
            [](obe::scene::Scene* self, const std::string& id, bool addToSceneRoot)
                -> obe::graphics::Sprite& { return self->create_sprite(id, addToSceneRoot); });
        bindScene["get_sprite_amount"] = &obe::scene::Scene::get_sprite_amount;
        bindScene["get_all_sprites"] = &obe::scene::Scene::get_all_sprites;
        bindScene["get_sprites_by_layer"] = &obe::scene::Scene::get_sprites_by_layer;
        bindScene["get_sprite_by_position"] = &obe::scene::Scene::get_sprite_by_position;
        bindScene["get_sprite"] = &obe::scene::Scene::get_sprite;
        bindScene["does_sprite_exists"] = &obe::scene::Scene::does_sprite_exists;
        bindScene["remove_sprite"] = &obe::scene::Scene::remove_sprite;
        bindScene["create_collider"] = sol::overload(
            [](obe::scene::Scene* self) -> obe::collision::PolygonalCollider& {
                return self->create_collider();
            },
            [](obe::scene::Scene* self, const std::string& id)
                -> obe::collision::PolygonalCollider& { return self->create_collider(id); },
            [](obe::scene::Scene* self, const std::string& id,
                bool addToSceneRoot) -> obe::collision::PolygonalCollider& {
                return self->create_collider(id, addToSceneRoot);
            });
        bindScene["get_collider_amount"] = &obe::scene::Scene::get_collider_amount;
        bindScene["get_all_colliders"] = &obe::scene::Scene::get_all_colliders;
        bindScene["get_collider_point_by_position"] = &obe::scene::Scene::get_collider_point_by_position;
        bindScene["get_collider_by_centroid_position"]
            = &obe::scene::Scene::get_collider_by_centroid_position;
        bindScene["get_collider"] = &obe::scene::Scene::get_collider;
        bindScene["does_collider_exists"] = &obe::scene::Scene::does_collider_exists;
        bindScene["remove_collider"] = &obe::scene::Scene::remove_collider;
        bindScene["get_scene_root_node"] = &obe::scene::Scene::get_scene_root_node;
        bindScene["get_filesystem_path"] = &obe::scene::Scene::get_filesystem_path;
        bindScene["reload"]
            = sol::overload(static_cast<void (obe::scene::Scene::*)()>(&obe::scene::Scene::reload),
                static_cast<void (obe::scene::Scene::*)(const obe::scene::OnSceneLoadCallback&)>(
                    &obe::scene::Scene::reload));
        bindScene["get_level_file"] = &obe::scene::Scene::get_level_file;
        bindScene["get_scene_node_by_position"] = &obe::scene::Scene::get_scene_node_by_position;
        bindScene["has_tiles"] = &obe::scene::Scene::has_tiles;
        bindScene["get_tiles"] = [](obe::scene::Scene* self) -> const obe::tiles::TileScene* {
            return &self->get_tiles();
        };
        bindScene["get_render_options"] = &obe::scene::Scene::get_render_options;
        bindScene["set_render_options"] = &obe::scene::Scene::set_render_options;
        bindScene["get_component"] = &obe::scene::Scene::get_component;
    }
    void LoadClassSceneNode(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::SceneNode> bindSceneNode
            = SceneNamespace.new_usertype<obe::scene::SceneNode>("SceneNode", sol::call_constructor,
                sol::default_constructor, sol::base_classes,
                sol::bases<obe::Transform::Movable, obe::Types::Selectable>());
        bindSceneNode["add_child"] = &obe::scene::SceneNode::add_child;
        bindSceneNode["remove_child"] = &obe::scene::SceneNode::remove_child;
        bindSceneNode["set_position"] = &obe::scene::SceneNode::set_position;
        bindSceneNode["move"] = &obe::scene::SceneNode::move;
        bindSceneNode["set_position_without_children"]
            = &obe::scene::SceneNode::set_position_without_children;
        bindSceneNode["move_without_children"] = &obe::scene::SceneNode::move_without_children;
    }
    void LoadClassSceneRenderOptions(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["scene"].get<sol::table>();
        sol::usertype<obe::scene::SceneRenderOptions> bindSceneRenderOptions
            = SceneNamespace.new_usertype<obe::scene::SceneRenderOptions>(
                "SceneRenderOptions", sol::call_constructor, sol::default_constructor);
        bindSceneRenderOptions["sprites"] = &obe::scene::SceneRenderOptions::sprites;
        bindSceneRenderOptions["collisions"] = &obe::scene::SceneRenderOptions::collisions;
        bindSceneRenderOptions["scene_nodes"] = &obe::scene::SceneRenderOptions::scene_nodes;
    }
};