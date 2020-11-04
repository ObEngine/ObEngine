#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Tiles::Bindings
{
    void LoadClassTileset(sol::state_view state);
    void LoadClassTilesetCollection(sol::state_view state);
    void LoadClassTileLayer(sol::state_view state);
    void LoadClassTileScene(sol::state_view state);
    void LoadClassTilePosition(sol::state_view state);
    void LoadClassTilePositionHash(sol::state_view state);
};