#include <Bindings/obe/Tiles/Exceptions/Exceptions.hpp>

#include <Tiles/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Tiles::Exceptions::Bindings
{
    void LoadClassTilePositionOutsideLayer(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Tiles"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Tiles::Exceptions::TilePositionOutsideLayer>
            bindTilePositionOutsideLayer
            = ExceptionsNamespace
                  .new_usertype<obe::Tiles::Exceptions::TilePositionOutsideLayer>(
                      "TilePositionOutsideLayer", sol::call_constructor,
                      sol::constructors<obe::Tiles::Exceptions::TilePositionOutsideLayer(
                          uint32_t, uint32_t, uint32_t, uint32_t, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownTileset(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Tiles"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Tiles::Exceptions::UnknownTileset> bindUnknownTileset
            = ExceptionsNamespace.new_usertype<obe::Tiles::Exceptions::UnknownTileset>(
                "UnknownTileset", sol::call_constructor,
                sol::constructors<obe::Tiles::Exceptions::UnknownTileset(
                    const std::string&, const std::vector<std::string>&,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownTileId(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Tiles"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Tiles::Exceptions::UnknownTileId> bindUnknownTileId
            = ExceptionsNamespace.new_usertype<obe::Tiles::Exceptions::UnknownTileId>(
                "UnknownTileId", sol::call_constructor,
                sol::constructors<obe::Tiles::Exceptions::UnknownTileId(uint32_t,
                    uint32_t, std::map<std::string, std::pair<uint32_t, uint32_t>>,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};