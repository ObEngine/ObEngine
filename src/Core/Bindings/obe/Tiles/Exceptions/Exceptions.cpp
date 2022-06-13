#include <Bindings/obe/Tiles/Exceptions/Exceptions.hpp>

#include <Tiles/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::tiles::exceptions::Bindings
{
    void LoadClassTilePositionOutsideLayer(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::TilePositionOutsideLayer> bindTilePositionOutsideLayer
            = ExceptionsNamespace.new_usertype<obe::tiles::exceptions::TilePositionOutsideLayer>(
                "TilePositionOutsideLayer", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::TilePositionOutsideLayer(
                    uint32_t, uint32_t, uint32_t, uint32_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::TilePositionOutsideLayer>,
                    obe::BaseException>());
    }
    void LoadClassUnknownTileId(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::UnknownTileId> bindUnknownTileId
            = ExceptionsNamespace.new_usertype<obe::tiles::exceptions::UnknownTileId>(
                "UnknownTileId", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::UnknownTileId(uint32_t, uint32_t,
                    std::map<std::string, std::pair<uint32_t, uint32_t>>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::UnknownTileId>,
                    obe::BaseException>());
    }
    void LoadClassUnknownTileLayer(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::UnknownTileLayer> bindUnknownTileLayer
            = ExceptionsNamespace.new_usertype<obe::tiles::exceptions::UnknownTileLayer>(
                "UnknownTileLayer", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::UnknownTileLayer(
                    const std::string&, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::UnknownTileLayer>,
                    obe::BaseException>());
    }
    void LoadClassUnknownTileset(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["tiles"]["exceptions"].get<sol::table>();
        sol::usertype<obe::tiles::exceptions::UnknownTileset> bindUnknownTileset
            = ExceptionsNamespace.new_usertype<obe::tiles::exceptions::UnknownTileset>(
                "UnknownTileset", sol::call_constructor,
                sol::constructors<obe::tiles::exceptions::UnknownTileset(
                    const std::string&, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::tiles::exceptions::UnknownTileset>,
                    obe::BaseException>());
    }
};