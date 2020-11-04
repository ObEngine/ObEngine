#include <Bindings/obe/Tiles/Tiles.hpp>

#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>
#include <Tiles/Tileset.hpp>

#include <Bindings/Config.hpp>

namespace obe::Tiles::Bindings
{
    void LoadClassTileset(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::Tileset> bindTileset = TilesNamespace.new_usertype<
            obe::Tiles::Tileset>("Tileset", sol::call_constructor,
            sol::constructors<obe::Tiles::Tileset(const std::string&, uint32_t, uint32_t,
                                  const std::string&, uint32_t, uint32_t, uint32_t),
                obe::Tiles::Tileset(const std::string&, uint32_t, uint32_t,
                    const std::string&, uint32_t, uint32_t, uint32_t, uint32_t),
                obe::Tiles::Tileset(const std::string&, uint32_t, uint32_t,
                    const std::string&, uint32_t, uint32_t, uint32_t, uint32_t,
                    uint32_t)>(),
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
            = TilesNamespace.new_usertype<obe::Tiles::TilesetCollection>(
                "TilesetCollection", sol::call_constructor,
                sol::constructors<obe::Tiles::TilesetCollection()>());
        bindTilesetCollection["addTileset"] = &obe::Tiles::TilesetCollection::addTileset;
        bindTilesetCollection["tilesetFromId"]
            = &obe::Tiles::TilesetCollection::tilesetFromId;
        bindTilesetCollection["tilesetFromTileId"]
            = &obe::Tiles::TilesetCollection::tilesetFromTileId;
    }
    void LoadClassTileLayer(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TileLayer> bindTileLayer = TilesNamespace.new_usertype<
            obe::Tiles::TileLayer>("TileLayer", sol::call_constructor,
            sol::constructors<obe::Tiles::TileLayer(const obe::Tiles::TilesetCollection&,
                const std::string&, int32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                const std::vector<uint32_t>&)>(),
            sol::base_classes, sol::bases<obe::Graphics::Renderable>());
        bindTileLayer["build"] = &obe::Tiles::TileLayer::build;
        bindTileLayer["draw"] = &obe::Tiles::TileLayer::draw;
        bindTileLayer["setTile"] = &obe::Tiles::TileLayer::setTile;
        bindTileLayer["getTile"] = &obe::Tiles::TileLayer::getTile;
    }
    void LoadClassTileScene(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TileScene> bindTileScene
            = TilesNamespace.new_usertype<obe::Tiles::TileScene>("TileScene",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<obe::Types::Serializable>());
        bindTileScene["dump"] = &obe::Tiles::TileScene::dump;
        bindTileScene["load"] = &obe::Tiles::TileScene::load;
        bindTileScene["getRenderables"] = &obe::Tiles::TileScene::getRenderables;
    }
    void LoadClassTilePosition(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TilePosition> bindTilePosition
            = TilesNamespace.new_usertype<obe::Tiles::TilePosition>(
                "TilePosition", sol::call_constructor, sol::default_constructor);
        bindTilePosition[sol::meta_function::less_than]
            = &obe::Tiles::TilePosition::operator<;
        bindTilePosition["x"] = &obe::Tiles::TilePosition::x;
        bindTilePosition["y"] = &obe::Tiles::TilePosition::y;
    }
    void LoadClassTilePositionHash(sol::state_view state)
    {
        sol::table TilesNamespace = state["obe"]["Tiles"].get<sol::table>();
        sol::usertype<obe::Tiles::TilePositionHash> bindTilePositionHash
            = TilesNamespace.new_usertype<obe::Tiles::TilePositionHash>(
                "TilePositionHash", sol::call_constructor, sol::default_constructor);
        bindTilePositionHash[sol::meta_function::call]
            = &obe::Tiles::TilePositionHash::operator();
    }
};