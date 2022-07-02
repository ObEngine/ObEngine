#include <Bindings/obe/tiles/Tiles.hpp>

#include <Scene/Scene.hpp>
#include <Tiles/Animation.hpp>
#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>
#include <Tiles/Tile.hpp>
#include <Tiles/Tileset.hpp>

#include <Bindings/Config.hpp>

namespace obe::tiles::bindings
{
    void load_class_animated_tile(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::AnimatedTile> bind_animated_tile
            = tiles_namespace.new_usertype<obe::tiles::AnimatedTile>("AnimatedTile",
                sol::call_constructor,
                sol::constructors<obe::tiles::AnimatedTile(const obe::tiles::Tileset&,
                    std::vector<uint32_t>, std::vector<obe::time::TimeUnit>)>());
        bind_animated_tile["attach_quad"]
            = sol::overload([](obe::tiles::AnimatedTile* self,
                                sf::Vertex* quad) -> void { return self->attach_quad(quad); },
                [](obe::tiles::AnimatedTile* self, sf::Vertex* quad, obe::tiles::TileInfo tile_info)
                    -> void { return self->attach_quad(quad, tile_info); });
        bind_animated_tile["detach_quad"] = &obe::tiles::AnimatedTile::detach_quad;
        bind_animated_tile["start"] = &obe::tiles::AnimatedTile::start;
        bind_animated_tile["stop"] = &obe::tiles::AnimatedTile::stop;
        bind_animated_tile["get_id"] = &obe::tiles::AnimatedTile::get_id;
        bind_animated_tile["update"] = &obe::tiles::AnimatedTile::update;
    }
    void load_class_tile_layer(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TileLayer> bind_tile_layer
            = tiles_namespace.new_usertype<obe::tiles::TileLayer>("TileLayer",
                sol::call_constructor,
                sol::constructors<obe::tiles::TileLayer(const obe::tiles::TileScene&,
                    const std::string&, int32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                    std::vector<uint32_t>)>(),
                sol::base_classes, sol::bases<obe::graphics::Renderable>());
        bind_tile_layer["get_id"] = &obe::tiles::TileLayer::get_id;
        bind_tile_layer["build"] = &obe::tiles::TileLayer::build;
        bind_tile_layer["draw"] = &obe::tiles::TileLayer::draw;
        bind_tile_layer["set_tile"] = &obe::tiles::TileLayer::set_tile;
        bind_tile_layer["get_tile"] = &obe::tiles::TileLayer::get_tile;
    }
    void load_class_tile_scene(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TileScene> bind_tile_scene
            = tiles_namespace.new_usertype<obe::tiles::TileScene>("TileScene",
                sol::call_constructor,
                sol::constructors<obe::tiles::TileScene(obe::scene::Scene&)>(), sol::base_classes,
                sol::bases<obe::types::Serializable>());
        bind_tile_scene["schema"] = &obe::tiles::TileScene::schema;
        bind_tile_scene["dump"] = &obe::tiles::TileScene::dump;
        bind_tile_scene["load"] = &obe::tiles::TileScene::load;
        bind_tile_scene["update"] = &obe::tiles::TileScene::update;
        bind_tile_scene["clear"] = &obe::tiles::TileScene::clear;
        bind_tile_scene["get_all_layers"] = &obe::tiles::TileScene::get_all_layers;
        bind_tile_scene["get_layers_ids"] = &obe::tiles::TileScene::get_layers_ids;
        bind_tile_scene["get_layer"] = &obe::tiles::TileScene::get_layer;
        bind_tile_scene["get_animated_tiles"] = &obe::tiles::TileScene::get_animated_tiles;
        bind_tile_scene["get_tilesets"]
            = [](obe::tiles::TileScene* self) -> const obe::tiles::TilesetCollection* {
            return &self->get_tilesets();
        };
        bind_tile_scene["get_renderables"] = &obe::tiles::TileScene::get_renderables;
        bind_tile_scene["get_collider_models"] = &obe::tiles::TileScene::get_collider_models;
        bind_tile_scene["get_game_objects_models"]
            = &obe::tiles::TileScene::get_game_objects_models;
        bind_tile_scene["get_width"] = &obe::tiles::TileScene::get_width;
        bind_tile_scene["get_height"] = &obe::tiles::TileScene::get_height;
        bind_tile_scene["get_tile_width"] = &obe::tiles::TileScene::get_tile_width;
        bind_tile_scene["get_tile_height"] = &obe::tiles::TileScene::get_tile_height;
        bind_tile_scene["is_anti_aliased"] = &obe::tiles::TileScene::is_anti_aliased;
        bind_tile_scene["get_scene"] = &obe::tiles::TileScene::get_scene;
    }
    void load_class_tileset(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::Tileset> bind_tileset
            = tiles_namespace.new_usertype<obe::tiles::Tileset>("Tileset", sol::call_constructor,
                sol::constructors<obe::tiles::Tileset(const std::string&, uint32_t, uint32_t,
                                      const std::string&, uint32_t, uint32_t, uint32_t),
                    obe::tiles::Tileset(const std::string&, uint32_t, uint32_t, const std::string&,
                        uint32_t, uint32_t, uint32_t, uint32_t),
                    obe::tiles::Tileset(const std::string&, uint32_t, uint32_t, const std::string&,
                        uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)>(),
                sol::base_classes, sol::bases<obe::types::Identifiable>());
        bind_tileset["get_first_tile_id"] = &obe::tiles::Tileset::get_first_tile_id;
        bind_tileset["get_last_tile_id"] = &obe::tiles::Tileset::get_last_tile_id;
        bind_tileset["get_tile_count"] = &obe::tiles::Tileset::get_tile_count;
        bind_tileset["get_margin"] = &obe::tiles::Tileset::get_margin;
        bind_tileset["get_spacing"] = &obe::tiles::Tileset::get_spacing;
        bind_tileset["get_tile_width"] = &obe::tiles::Tileset::get_tile_width;
        bind_tileset["get_tile_height"] = &obe::tiles::Tileset::get_tile_height;
        bind_tileset["get_image_width"] = &obe::tiles::Tileset::get_image_width;
        bind_tileset["get_image_height"] = &obe::tiles::Tileset::get_image_height;
        bind_tileset["get_image_path"] = &obe::tiles::Tileset::get_image_path;
        bind_tileset["get_texture"] = &obe::tiles::Tileset::get_texture;
    }
    void load_class_tileset_collection(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TilesetCollection> bind_tileset_collection
            = tiles_namespace.new_usertype<obe::tiles::TilesetCollection>("TilesetCollection",
                sol::call_constructor, sol::constructors<obe::tiles::TilesetCollection()>());
        bind_tileset_collection["add_tileset"] = &obe::tiles::TilesetCollection::add_tileset;
        bind_tileset_collection["tileset_from_id"]
            = &obe::tiles::TilesetCollection::tileset_from_id;
        bind_tileset_collection["tileset_from_tile_id"]
            = &obe::tiles::TilesetCollection::tileset_from_tile_id;
        bind_tileset_collection["size"] = &obe::tiles::TilesetCollection::size;
        bind_tileset_collection["get_tilesets_first_tiles_ids"]
            = &obe::tiles::TilesetCollection::get_tilesets_first_tiles_ids;
        bind_tileset_collection["clear"] = &obe::tiles::TilesetCollection::clear;
    }
    void load_class_texture_quads_index(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TextureQuadsIndex> bind_texture_quads_index
            = tiles_namespace.new_usertype<obe::tiles::TextureQuadsIndex>(
                "TextureQuadsIndex", sol::call_constructor, sol::default_constructor);
        bind_texture_quads_index["transform"] = &obe::tiles::TextureQuadsIndex::transform;
        bind_texture_quads_index["q0"] = &obe::tiles::TextureQuadsIndex::q0;
        bind_texture_quads_index["q1"] = &obe::tiles::TextureQuadsIndex::q1;
        bind_texture_quads_index["q2"] = &obe::tiles::TextureQuadsIndex::q2;
        bind_texture_quads_index["q3"] = &obe::tiles::TextureQuadsIndex::q3;
    }
    void load_class_tile_info(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TileInfo> bind_tile_info
            = tiles_namespace.new_usertype<obe::tiles::TileInfo>(
                "TileInfo", sol::call_constructor, sol::default_constructor);
        bind_tile_info["flip_horizontal"] = &obe::tiles::TileInfo::flip_horizontal;
        bind_tile_info["flip_vertical"] = &obe::tiles::TileInfo::flip_vertical;
        bind_tile_info["flip_diagonal"] = &obe::tiles::TileInfo::flip_diagonal;
        bind_tile_info["tile_id"] = &obe::tiles::TileInfo::tile_id;
    }
    void load_function_get_tile_info(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        tiles_namespace.set_function("get_tile_info", &obe::tiles::get_tile_info);
    }
    void load_function_strip_tile_flags(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        tiles_namespace.set_function("strip_tile_flags", &obe::tiles::strip_tile_flags);
    }
    void load_function_apply_texture_quads_transforms(sol::state_view state)
    {
        sol::table tiles_namespace = state["obe"]["tiles"].get<sol::table>();
        tiles_namespace.set_function(
            "apply_texture_quads_transforms", &obe::tiles::apply_texture_quads_transforms);
    }
};