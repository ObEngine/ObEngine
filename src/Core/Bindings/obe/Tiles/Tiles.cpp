#include <Bindings/obe/Tiles/Tiles.hpp>

#include <Scene/Scene.hpp>
#include <Tiles/Animation.hpp>
#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>
#include <Tiles/Tile.hpp>
#include <Tiles/Tileset.hpp>

#include <Bindings/Config.hpp>

namespace obe::tiles::Bindings
{
    void LoadClassAnimatedTile(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::AnimatedTile> bindAnimatedTile
            = TilesNamespace.new_usertype<obe::tiles::AnimatedTile>("AnimatedTile",
                sol::call_constructor,
                sol::constructors<obe::tiles::AnimatedTile(const obe::tiles::Tileset&,
                    std::vector<uint32_t>, std::vector<obe::time::TimeUnit>)>());
        bindAnimatedTile["attach_quad"]
            = sol::overload([](obe::tiles::AnimatedTile* self,
                                sf::Vertex* quad) -> void { return self->attach_quad(quad); },
                [](obe::tiles::AnimatedTile* self, sf::Vertex* quad, obe::tiles::TileInfo tileInfo)
                    -> void { return self->attach_quad(quad, tileInfo); });
        bindAnimatedTile["detach_quad"] = &obe::tiles::AnimatedTile::detach_quad;
        bindAnimatedTile["start"] = &obe::tiles::AnimatedTile::start;
        bindAnimatedTile["stop"] = &obe::tiles::AnimatedTile::stop;
        bindAnimatedTile["get_id"] = &obe::tiles::AnimatedTile::get_id;
        bindAnimatedTile["update"] = &obe::tiles::AnimatedTile::update;
    }
    void LoadClassTileLayer(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TileLayer> bindTileLayer
            = TilesNamespace.new_usertype<obe::tiles::TileLayer>("TileLayer", sol::call_constructor,
                sol::constructors<obe::tiles::TileLayer(const obe::tiles::TileScene&,
                    const std::string&, int32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                    std::vector<uint32_t>)>(),
                sol::base_classes, sol::bases<obe::graphics::Renderable>());
        bindTileLayer["get_id"] = &obe::tiles::TileLayer::get_id;
        bindTileLayer["build"] = &obe::tiles::TileLayer::build;
        bindTileLayer["draw"] = &obe::tiles::TileLayer::draw;
        bindTileLayer["set_tile"] = &obe::tiles::TileLayer::set_tile;
        bindTileLayer["get_tile"] = &obe::tiles::TileLayer::get_tile;
    }
    void LoadClassTileScene(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TileScene> bindTileScene
            = TilesNamespace.new_usertype<obe::tiles::TileScene>("TileScene", sol::call_constructor,
                sol::constructors<obe::tiles::TileScene(obe::scene::Scene&)>(), sol::base_classes,
                sol::bases<obe::Types::Serializable>());
        bindTileScene["dump"] = &obe::tiles::TileScene::dump;
        bindTileScene["load"] = &obe::tiles::TileScene::load;
        bindTileScene["update"] = &obe::tiles::TileScene::update;
        bindTileScene["clear"] = &obe::tiles::TileScene::clear;
        bindTileScene["get_all_layers"] = &obe::tiles::TileScene::get_all_layers;
        bindTileScene["get_layers_ids"] = &obe::tiles::TileScene::get_layers_ids;
        bindTileScene["get_layer"] = &obe::tiles::TileScene::get_layer;
        bindTileScene["get_animated_tiles"] = &obe::tiles::TileScene::get_animated_tiles;
        bindTileScene["get_tilesets"]
            = [](obe::tiles::TileScene* self) -> const obe::tiles::TilesetCollection* {
            return &self->get_tilesets();
        };
        bindTileScene["get_renderables"] = &obe::tiles::TileScene::get_renderables;
        bindTileScene["get_collider_models"] = &obe::tiles::TileScene::get_collider_models;
        bindTileScene["get_game_objects_models"] = &obe::tiles::TileScene::get_game_objects_models;
        bindTileScene["get_width"] = &obe::tiles::TileScene::get_width;
        bindTileScene["get_height"] = &obe::tiles::TileScene::get_height;
        bindTileScene["get_tile_width"] = &obe::tiles::TileScene::get_tile_width;
        bindTileScene["get_tile_height"] = &obe::tiles::TileScene::get_tile_height;
        bindTileScene["is_anti_aliased"] = &obe::tiles::TileScene::is_anti_aliased;
        bindTileScene["get_scene"] = &obe::tiles::TileScene::get_scene;
    }
    void LoadClassTileset(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::Tileset> bindTileset
            = TilesNamespace.new_usertype<obe::tiles::Tileset>("Tileset", sol::call_constructor,
                sol::constructors<obe::tiles::Tileset(const std::string&, uint32_t, uint32_t,
                                      const std::string&, uint32_t, uint32_t, uint32_t),
                    obe::tiles::Tileset(const std::string&, uint32_t, uint32_t, const std::string&,
                        uint32_t, uint32_t, uint32_t, uint32_t),
                    obe::tiles::Tileset(const std::string&, uint32_t, uint32_t, const std::string&,
                        uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindTileset["get_first_tile_id"] = &obe::tiles::Tileset::get_first_tile_id;
        bindTileset["get_last_tile_id"] = &obe::tiles::Tileset::get_last_tile_id;
        bindTileset["get_tile_count"] = &obe::tiles::Tileset::get_tile_count;
        bindTileset["get_margin"] = &obe::tiles::Tileset::get_margin;
        bindTileset["get_spacing"] = &obe::tiles::Tileset::get_spacing;
        bindTileset["get_tile_width"] = &obe::tiles::Tileset::get_tile_width;
        bindTileset["get_tile_height"] = &obe::tiles::Tileset::get_tile_height;
        bindTileset["get_image_width"] = &obe::tiles::Tileset::get_image_width;
        bindTileset["get_image_height"] = &obe::tiles::Tileset::get_image_height;
        bindTileset["get_image_path"] = &obe::tiles::Tileset::get_image_path;
        bindTileset["get_texture"] = &obe::tiles::Tileset::get_texture;
    }
    void LoadClassTilesetCollection(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TilesetCollection> bindTilesetCollection
            = TilesNamespace.new_usertype<obe::tiles::TilesetCollection>("TilesetCollection",
                sol::call_constructor, sol::constructors<obe::tiles::TilesetCollection()>());
        bindTilesetCollection["add_tileset"] = &obe::tiles::TilesetCollection::add_tileset;
        bindTilesetCollection["tileset_from_id"] = &obe::tiles::TilesetCollection::tileset_from_id;
        bindTilesetCollection["tileset_from_tile_id"]
            = &obe::tiles::TilesetCollection::tileset_from_tile_id;
        bindTilesetCollection["size"] = &obe::tiles::TilesetCollection::size;
        bindTilesetCollection["get_tilesets_first_tiles_ids"]
            = &obe::tiles::TilesetCollection::get_tilesets_first_tiles_ids;
        bindTilesetCollection["clear"] = &obe::tiles::TilesetCollection::clear;
    }
    void LoadClassTextureQuadsIndex(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TextureQuadsIndex> bindTextureQuadsIndex
            = TilesNamespace.new_usertype<obe::tiles::TextureQuadsIndex>(
                "TextureQuadsIndex", sol::call_constructor, sol::default_constructor);
        bindTextureQuadsIndex["transform"] = &obe::tiles::TextureQuadsIndex::transform;
        bindTextureQuadsIndex["q0"] = &obe::tiles::TextureQuadsIndex::q0;
        bindTextureQuadsIndex["q1"] = &obe::tiles::TextureQuadsIndex::q1;
        bindTextureQuadsIndex["q2"] = &obe::tiles::TextureQuadsIndex::q2;
        bindTextureQuadsIndex["q3"] = &obe::tiles::TextureQuadsIndex::q3;
    }
    void LoadClassTileInfo(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        sol::usertype<obe::tiles::TileInfo> bindTileInfo
            = TilesNamespace.new_usertype<obe::tiles::TileInfo>(
                "TileInfo", sol::call_constructor, sol::default_constructor);
        bindTileInfo["flip_horizontal"] = &obe::tiles::TileInfo::flip_horizontal;
        bindTileInfo["flip_vertical"] = &obe::tiles::TileInfo::flip_vertical;
        bindTileInfo["flip_diagonal"] = &obe::tiles::TileInfo::flip_diagonal;
        bindTileInfo["tile_id"] = &obe::tiles::TileInfo::tile_id;
    }
    void LoadFunctionGetTileInfo(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        TilesNamespace.set_function("get_tile_info", &obe::tiles::get_tile_info);
    }
    void LoadFunctionStripTileFlags(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        TilesNamespace.set_function("strip_tile_flags", &obe::tiles::strip_tile_flags);
    }
    void LoadFunctionApplyTextureQuadsTransforms(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["tiles"].get<sol::table>();
        TilesNamespace.set_function(
            "apply_texture_quads_transforms", &obe::tiles::apply_texture_quads_transforms);
    }
};