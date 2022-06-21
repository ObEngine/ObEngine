---@meta

obe.tiles.exceptions = {};
---@class obe.tiles.exceptions.TilePositionOutsideLayer : obe.Exception[obe.tiles.exceptions.TilePositionOutsideLayer]
obe.tiles.exceptions._TilePositionOutsideLayer = {};

--- obe.tiles.exceptions.TilePositionOutsideLayer constructor
---
---@param x number #
---@param y number #
---@param width number #
---@param height number #
---@param info obe.DebugInfo #
---@return obe.tiles.exceptions.TilePositionOutsideLayer
function obe.tiles.exceptions.TilePositionOutsideLayer(x, y, width, height, info) end



---@class obe.tiles.exceptions.UnknownTileId : obe.Exception[obe.tiles.exceptions.UnknownTileId]
obe.tiles.exceptions._UnknownTileId = {};

--- obe.tiles.exceptions.UnknownTileId constructor
---
---@param tile_id number #
---@param max_tile_id number #
---@param tilesets table<string, table<number, number>> #
---@param info obe.DebugInfo #
---@return obe.tiles.exceptions.UnknownTileId
function obe.tiles.exceptions.UnknownTileId(tile_id, max_tile_id, tilesets, info) end



---@class obe.tiles.exceptions.UnknownTileLayer : obe.Exception[obe.tiles.exceptions.UnknownTileLayer]
obe.tiles.exceptions._UnknownTileLayer = {};

--- obe.tiles.exceptions.UnknownTileLayer constructor
---
---@param layer_id string #
---@param layer_ids string[] #
---@param info obe.DebugInfo #
---@return obe.tiles.exceptions.UnknownTileLayer
function obe.tiles.exceptions.UnknownTileLayer(layer_id, layer_ids, info) end



---@class obe.tiles.exceptions.UnknownTileset : obe.Exception[obe.tiles.exceptions.UnknownTileset]
obe.tiles.exceptions._UnknownTileset = {};

--- obe.tiles.exceptions.UnknownTileset constructor
---
---@param tileset_id string #
---@param tilesets_ids string[] #
---@param info obe.DebugInfo #
---@return obe.tiles.exceptions.UnknownTileset
function obe.tiles.exceptions.UnknownTileset(tileset_id, tilesets_ids, info) end



return obe.tiles.exceptions;