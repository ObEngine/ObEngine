---@meta

obe.tiles = {};
---@class obe.tiles.AnimatedTile
obe.tiles._AnimatedTile = {};

--- obe.tiles.AnimatedTile constructor
---
---@param tileset obe.tiles.Tileset #
---@param tile_ids number[] #
---@param sleeps obe.time.TimeUnit[] #
---@return obe.tiles.AnimatedTile
function obe.tiles.AnimatedTile(tileset, tile_ids, sleeps) end


---@param quad sf.Vertex #
---@param tile_info? obe.tiles.TileInfo #
function obe.tiles._AnimatedTile:attach_quad(quad, tile_info) end

---@param quad sf.Vertex #
function obe.tiles._AnimatedTile:detach_quad(quad) end

function obe.tiles._AnimatedTile:start() end

function obe.tiles._AnimatedTile:stop() end

---@return number
function obe.tiles._AnimatedTile:get_id() end

function obe.tiles._AnimatedTile:update() end


---@class obe.tiles.TileLayer : obe.graphics.Renderable
obe.tiles._TileLayer = {};

--- obe.tiles.TileLayer constructor
---
---@param scene obe.tiles.TileScene #
---@param id string #
---@param layer number #
---@param sublayer number #
---@param x number #
---@param y number #
---@param width number #
---@param height number #
---@param data number[] #
---@param visible boolean #
---@return obe.tiles.TileLayer
function obe.tiles.TileLayer(scene, id, layer, sublayer, x, y, width, height, data, visible) end


---@return string
function obe.tiles._TileLayer:get_id() end

function obe.tiles._TileLayer:build() end

--- Draws all elements of the TileLayer on the screen.
---
---@param surface obe.graphics.RenderTarget #
---@param camera obe.scene.Camera #
function obe.tiles._TileLayer:draw(surface, camera) end

---@param x number #
---@param y number #
---@param tile_id number #
function obe.tiles._TileLayer:set_tile(x, y, tile_id) end

---@param x number #
---@param y number #
---@return number
function obe.tiles._TileLayer:get_tile(x, y) end


---@class obe.tiles.TileScene : obe.types.Serializable
obe.tiles._TileScene = {};

--- obe.tiles.TileScene constructor
---
---@param scene obe.scene.Scene #
---@return obe.tiles.TileScene
function obe.tiles.TileScene(scene) end

--- obe.tiles.TileScene constructor
---
---@param p0 obe.tiles.TileScene #
---@return obe.tiles.TileScene
function obe.tiles.TileScene(p0) end


--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.tiles._TileScene:schema() end

--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.tiles._TileScene:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.tiles._TileScene:load(data) end

function obe.tiles._TileScene:update() end

function obe.tiles._TileScene:clear() end

---@return obe.tiles.TileLayer[]
function obe.tiles._TileScene:get_all_layers() end

---@return string[]
function obe.tiles._TileScene:get_layers_ids() end

---@param id string #
---@return obe.tiles.TileLayer
function obe.tiles._TileScene:get_layer(id) end

---@return obe.tiles.AnimatedTiles
function obe.tiles._TileScene:get_animated_tiles() end

---@return obe.tiles.TilesetCollection
function obe.tiles._TileScene:get_tilesets() end

---@return obe.graphics.Renderable[]
function obe.tiles._TileScene:get_renderables() end

---@return obe.collision.ColliderComponent[]
function obe.tiles._TileScene:get_collider_models() end

---@return vili.node[]
function obe.tiles._TileScene:get_game_objects_models() end

---@return number
function obe.tiles._TileScene:get_width() end

---@return number
function obe.tiles._TileScene:get_height() end

---@return number
function obe.tiles._TileScene:get_tile_width() end

---@return number
function obe.tiles._TileScene:get_tile_height() end

---@return boolean
function obe.tiles._TileScene:is_anti_aliased() end

---@return obe.scene.Scene
function obe.tiles._TileScene:get_scene() end


---@class obe.tiles.Tileset : obe.types.Identifiable
obe.tiles._Tileset = {};

--- obe.tiles.Tileset constructor
---
---@param id string #
---@param first_tile_id number #
---@param count number #
---@param image_path string #
---@param columns number #
---@param tile_width number #
---@param tile_height number #
---@param margin? number #
---@param spacing? number #
---@return obe.tiles.Tileset
function obe.tiles.Tileset(id, first_tile_id, count, image_path, columns, tile_width, tile_height, margin, spacing) end


---@return number
function obe.tiles._Tileset:get_first_tile_id() end

---@return number
function obe.tiles._Tileset:get_last_tile_id() end

---@return number
function obe.tiles._Tileset:get_tile_count() end

---@return number
function obe.tiles._Tileset:get_margin() end

---@return number
function obe.tiles._Tileset:get_spacing() end

---@return number
function obe.tiles._Tileset:get_tile_width() end

---@return number
function obe.tiles._Tileset:get_tile_height() end

---@return number
function obe.tiles._Tileset:get_image_width() end

---@return number
function obe.tiles._Tileset:get_image_height() end

---@return string
function obe.tiles._Tileset:get_image_path() end

---@return obe.graphics.Texture
function obe.tiles._Tileset:get_texture() end


---@class obe.tiles.TilesetCollection
obe.tiles._TilesetCollection = {};

--- obe.tiles.TilesetCollection constructor
---
---@return obe.tiles.TilesetCollection
function obe.tiles.TilesetCollection() end

--- obe.tiles.TilesetCollection constructor
---
---@param p0 obe.tiles.TilesetCollection #
---@return obe.tiles.TilesetCollection
function obe.tiles.TilesetCollection(p0) end


---@param first_tile_id number #
---@param id string #
---@param source string #
---@param columns number #
---@param width number #
---@param height number #
---@param count number #
function obe.tiles._TilesetCollection:add_tileset(first_tile_id, id, source, columns, width, height, count) end

---@param id string #
---@return obe.tiles.Tileset
function obe.tiles._TilesetCollection:tileset_from_id(id) end

---@param tile_id number #
---@return obe.tiles.Tileset
function obe.tiles._TilesetCollection:tileset_from_tile_id(tile_id) end

---@return number
function obe.tiles._TilesetCollection:size() end

---@return number[]
function obe.tiles._TilesetCollection:get_tilesets_first_tiles_ids() end

function obe.tiles._TilesetCollection:clear() end


---@class obe.tiles.TextureQuadsIndex
---@field q0 number #
---@field q1 number #
---@field q2 number #
---@field q3 number #
obe.tiles._TextureQuadsIndex = {};


---@param info obe.tiles.TileInfo #
function obe.tiles._TextureQuadsIndex:transform(info) end


---@class obe.tiles.TileInfo
---@field flip_horizontal boolean #
---@field flip_vertical boolean #
---@field flip_diagonal boolean #
---@field tile_id number #
obe.tiles._TileInfo = {};




---@alias obe.tiles.AnimatedTiles obe.tiles.AnimatedTile[]
---@param tile_id number #
---@return obe.tiles.TileInfo
function obe.tiles.get_tile_info(tile_id) end

---@param tile_id number #
---@return number
function obe.tiles.strip_tile_flags(tile_id) end

---@param info obe.tiles.TileInfo #
---@param quads obe.tiles.TextureQuadsIndex #
function obe.tiles.apply_texture_quads_transforms(info, quads) end

return obe.tiles;