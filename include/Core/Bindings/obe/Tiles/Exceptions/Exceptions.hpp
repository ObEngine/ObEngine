#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Tiles::Exceptions::Bindings
{
    void LoadClassTilePositionOutsideLayer(sol::state_view state);
    void LoadClassUnknownTileset(sol::state_view state);
    void LoadClassUnknownTileId(sol::state_view state);
};