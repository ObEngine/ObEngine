#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Tiles::Bindings
{
    void LoadClassAnimatedTile(sol::state_view state);
    void LoadClassTileset(sol::state_view state);
    void LoadClassTilesetCollection(sol::state_view state);
    void LoadClassTileLayer(sol::state_view state);
    void LoadClassTileScene(sol::state_view state);
    void LoadClassTextureQuadsIndex(sol::state_view state);
    void LoadClassTileInfo(sol::state_view state);
    void LoadFunctionGetTileInfo(sol::state_view state);
    void LoadFunctionStripTileFlags(sol::state_view state);
    void LoadFunctionApplyTextureQuadsTransforms(sol::state_view state);
};
