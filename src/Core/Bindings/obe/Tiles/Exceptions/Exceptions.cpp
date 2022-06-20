#include <Bindings/obe/tiles/exceptions/Exceptions.hpp>

#include <Tiles/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::tiles::exceptions::bindings
{
    void load_class_tile_position_outside_layer(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::TilePositionOutsideLayer>
            bind_tile_position_outside_layer
            = exceptions_namespace.new_usertype<obe::tiles::exceptions::TilePositionOutsideLayer>(
                "TilePositionOutsideLayer", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::TilePositionOutsideLayer(
                    uint32_t, uint32_t, uint32_t, uint32_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::TilePositionOutsideLayer>,
                    obe::BaseException>());
    }
    void load_class_unknown_tile_id(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::UnknownTileId> bind_unknown_tile_id
            = exceptions_namespace.new_usertype<obe::tiles::exceptions::UnknownTileId>(
                "UnknownTileId", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::UnknownTileId(uint32_t, uint32_t,
                    std::map<std::string, std::pair<uint32_t, uint32_t>>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::UnknownTileId>,
                    obe::BaseException>());
    }
    void load_class_unknown_tile_layer(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::UnknownTileLayer> bind_unknown_tile_layer
            = exceptions_namespace.new_usertype<obe::tiles::exceptions::UnknownTileLayer>(
                "UnknownTileLayer", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::UnknownTileLayer(
                    const std::string&, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::UnknownTileLayer>,
                    obe::BaseException>());
    }
    void load_class_unknown_tileset(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::UnknownTileset> bind_unknown_tileset
            = exceptions_namespace.new_usertype<obe::tiles::exceptions::UnknownTileset>(
                "UnknownTileset", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::UnknownTileset(
                    const std::string&, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::UnknownTileset>,
                    obe::BaseException>());
    }
};