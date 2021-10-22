#include <Bindings/obe/Tiles/Tiles.hpp>

#include <Scene/Scene.hpp>
#include <Tiles/Animation.hpp>
#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>
#include <Tiles/Tile.hpp>
#include <Tiles/Tileset.hpp>

#include <Bindings/Config.hpp>

namespace obe::Tiles::Bindings
{
    void LoadClassAnimatedTile(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::AnimatedTile> bindAnimatedTile
            = TilesNamespace.new_usertype<obe::Tiles::AnimatedTile>("AnimatedTile",
                sol::call_constructor,
                sol::constructors<obe::Tiles::AnimatedTile(const obe::Tiles::Tileset&,
                    std::vector<uint32_t>, std::vector<obe::Time::TimeUnit>)>());
        bindAnimatedTile["attachQuad"]
            = sol::overload([](obe::Tiles::AnimatedTile* self,
                                sf::Vertex* quad) -> void { return self->attachQuad(quad); },
                [](obe::Tiles::AnimatedTile* self, sf::Vertex* quad, obe::Tiles::TileInfo tileInfo)
                    -> void { return self->attachQuad(quad, tileInfo); });
        bindAnimatedTile["dettachQuad"] = &obe::Tiles::AnimatedTile::dettachQuad;
        bindAnimatedTile["start"] = &obe::Tiles::AnimatedTile::start;
        bindAnimatedTile["stop"] = &obe::Tiles::AnimatedTile::stop;
        bindAnimatedTile["getId"] = &obe::Tiles::AnimatedTile::getId;
        bindAnimatedTile["update"] = &obe::Tiles::AnimatedTile::update;
    }
    void LoadClassTileLayer(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TileLayer> bindTileLayer
            = TilesNamespace.new_usertype<obe::Tiles::TileLayer>("TileLayer", sol::call_constructor,
                sol::constructors<obe::Tiles::TileLayer(const obe::Tiles::TileScene&,
                    const std::string&, int32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                    std::vector<uint32_t>)>(),
                sol::base_classes, sol::bases<obe::Graphics::Renderable>());
        bindTileLayer["getId"] = &obe::Tiles::TileLayer::getId;
        bindTileLayer["build"] = &obe::Tiles::TileLayer::build;
        bindTileLayer["draw"] = &obe::Tiles::TileLayer::draw;
        bindTileLayer["setTile"] = &obe::Tiles::TileLayer::setTile;
        bindTileLayer["getTile"] = &obe::Tiles::TileLayer::getTile;
    }
    void LoadClassTileScene(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TileScene> bindTileScene
            = TilesNamespace.new_usertype<obe::Tiles::TileScene>("TileScene", sol::call_constructor,
                sol::constructors<obe::Tiles::TileScene(obe::Scene::Scene&)>(), sol::base_classes,
                sol::bases<obe::Types::Serializable>());
        bindTileScene["dump"] = &obe::Tiles::TileScene::dump;
        bindTileScene["load"] = &obe::Tiles::TileScene::load;
        bindTileScene["update"] = &obe::Tiles::TileScene::update;
        bindTileScene["clear"] = &obe::Tiles::TileScene::clear;
        bindTileScene["getAllLayers"] = &obe::Tiles::TileScene::getAllLayers;
        bindTileScene["getLayersIds"] = &obe::Tiles::TileScene::getLayersIds;
        bindTileScene["getLayer"] = &obe::Tiles::TileScene::getLayer;
        bindTileScene["getAnimatedTiles"] = &obe::Tiles::TileScene::getAnimatedTiles;
        bindTileScene["getTilesets"]
            = [](obe::Tiles::TileScene* self) { return &self->getTilesets(); };
        bindTileScene["getRenderables"] = &obe::Tiles::TileScene::getRenderables;
        bindTileScene["getColliderModels"] = &obe::Tiles::TileScene::getColliderModels;
        bindTileScene["getGameObjectsModels"] = &obe::Tiles::TileScene::getGameObjectsModels;
        bindTileScene["getWidth"] = &obe::Tiles::TileScene::getWidth;
        bindTileScene["getHeight"] = &obe::Tiles::TileScene::getHeight;
        bindTileScene["getTileWidth"] = &obe::Tiles::TileScene::getTileWidth;
        bindTileScene["getTileHeight"] = &obe::Tiles::TileScene::getTileHeight;
        bindTileScene["isSmooth"] = &obe::Tiles::TileScene::isSmooth;
        bindTileScene["getScene"] = &obe::Tiles::TileScene::getScene;
    }
    void LoadClassTileset(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::Tileset> bindTileset
            = TilesNamespace.new_usertype<obe::Tiles::Tileset>("Tileset", sol::call_constructor,
                sol::constructors<obe::Tiles::Tileset(const std::string&, uint32_t, uint32_t,
                                      const std::string&, uint32_t, uint32_t, uint32_t),
                    obe::Tiles::Tileset(const std::string&, uint32_t, uint32_t, const std::string&,
                        uint32_t, uint32_t, uint32_t, uint32_t),
                    obe::Tiles::Tileset(const std::string&, uint32_t, uint32_t, const std::string&,
                        uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindTileset["getFirstTileId"] = &obe::Tiles::Tileset::getFirstTileId;
        bindTileset["getLastTileId"] = &obe::Tiles::Tileset::getLastTileId;
        bindTileset["getTileCount"] = &obe::Tiles::Tileset::getTileCount;
        bindTileset["getMargin"] = &obe::Tiles::Tileset::getMargin;
        bindTileset["getSpacing"] = &obe::Tiles::Tileset::getSpacing;
        bindTileset["getTileWidth"] = &obe::Tiles::Tileset::getTileWidth;
        bindTileset["getTileHeight"] = &obe::Tiles::Tileset::getTileHeight;
        bindTileset["getImageWidth"] = &obe::Tiles::Tileset::getImageWidth;
        bindTileset["getImageHeight"] = &obe::Tiles::Tileset::getImageHeight;
        bindTileset["getImagePath"] = &obe::Tiles::Tileset::getImagePath;
        bindTileset["getTexture"] = &obe::Tiles::Tileset::getTexture;
    }
    void LoadClassTilesetCollection(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TilesetCollection> bindTilesetCollection
            = TilesNamespace.new_usertype<obe::Tiles::TilesetCollection>("TilesetCollection",
                sol::call_constructor, sol::constructors<obe::Tiles::TilesetCollection()>());
        bindTilesetCollection["addTileset"] = &obe::Tiles::TilesetCollection::addTileset;
        bindTilesetCollection["tilesetFromId"] = &obe::Tiles::TilesetCollection::tilesetFromId;
        bindTilesetCollection["tilesetFromTileId"]
            = &obe::Tiles::TilesetCollection::tilesetFromTileId;
        bindTilesetCollection["size"] = &obe::Tiles::TilesetCollection::size;
        bindTilesetCollection["getTilesetsFirstTilesIds"]
            = &obe::Tiles::TilesetCollection::getTilesetsFirstTilesIds;
        bindTilesetCollection["clear"] = &obe::Tiles::TilesetCollection::clear;
    }
    void LoadClassTextureQuadsIndex(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TextureQuadsIndex> bindTextureQuadsIndex
            = TilesNamespace.new_usertype<obe::Tiles::TextureQuadsIndex>(
                "TextureQuadsIndex", sol::call_constructor, sol::default_constructor);
        bindTextureQuadsIndex["transform"] = &obe::Tiles::TextureQuadsIndex::transform;
        bindTextureQuadsIndex["q0"] = &obe::Tiles::TextureQuadsIndex::q0;
        bindTextureQuadsIndex["q1"] = &obe::Tiles::TextureQuadsIndex::q1;
        bindTextureQuadsIndex["q2"] = &obe::Tiles::TextureQuadsIndex::q2;
        bindTextureQuadsIndex["q3"] = &obe::Tiles::TextureQuadsIndex::q3;
    }
    void LoadClassTileInfo(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TileInfo> bindTileInfo
            = TilesNamespace.new_usertype<obe::Tiles::TileInfo>(
                "TileInfo", sol::call_constructor, sol::default_constructor);
        bindTileInfo["flippedHorizontally"] = &obe::Tiles::TileInfo::flippedHorizontally;
        bindTileInfo["flippedVertically"] = &obe::Tiles::TileInfo::flippedVertically;
        bindTileInfo["flippedDiagonally"] = &obe::Tiles::TileInfo::flippedDiagonally;
        bindTileInfo["tileId"] = &obe::Tiles::TileInfo::tileId;
    }
    void LoadFunctionGetTileInfo(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        TilesNamespace.set_function("getTileInfo", obe::Tiles::getTileInfo);
    }
    void LoadFunctionStripTileFlags(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        TilesNamespace.set_function("stripTileFlags", obe::Tiles::stripTileFlags);
    }
    void LoadFunctionApplyTextureQuadsTransforms(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        TilesNamespace.set_function(
            "applyTextureQuadsTransforms", obe::Tiles::applyTextureQuadsTransforms);
    }
};