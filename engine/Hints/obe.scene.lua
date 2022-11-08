---@meta

obe.scene = {};
---@class obe.scene.Camera : obe.transform.AABB
obe.scene._Camera = {};

--- obe.scene.Camera constructor
---
---@return obe.scene.Camera
function obe.scene.Camera() end


--- Moves the Camera.
---
---@param position obe.transform.UnitVector #Position to add to the Camera
function obe.scene._Camera:move(position) end

--- Scales the Camera.
---
---@param scale_ number #Factor used to multiply the current size
---@param ref? obe.transform.Referential #Referential used to resize the Camera
function obe.scene._Camera:scale(scale_, ref) end

--- Sets the Position of the Camera.
---
---@param position obe.transform.UnitVector #New Position of the Camera
---@param ref? obe.transform.Referential #Referential used to position the Camera
function obe.scene._Camera:set_position(position, ref) end

--- Sets the size of the Camera.
---
---@param size number #Size of the Camera (1 = Normal Size meaning Screen Height = 2 SceneUnits)
---@param ref? obe.transform.Referential #Referential used to resize the Camera
function obe.scene._Camera:set_size(size, ref) end


---@class obe.scene.Scene : obe.types.Serializable, obe.engine.ResourceManagedObject
obe.scene._Scene = {};

--- Creates a new Scene.
---
---@param events obe.event.EventNamespace #
---@param lua sol.state_view #
---@return obe.scene.Scene
function obe.scene.Scene(events, lua) end


--- Same that load_from_file excepts the map will load at the next update.
---
---@param path string #Path to the Scene file
function obe.scene._Scene:load_from_file(path) end

--- Same that load_from_file excepts the map will load at the next update.
---
---@param path string #Path to the Scene file
---@param callback obe.scene.OnSceneLoadCallback #Lua Function called when new map has been loaded
function obe.scene._Scene:load_from_file(path, callback) end

--- Removes all elements in the Scene.
---
function obe.scene._Scene:clear() end

--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.scene._Scene:schema() end

--- Dumps all elements of the Scene in a vili tree.
---
---@return vili.node
function obe.scene._Scene:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.scene._Scene:load(data) end

---@param data vili.node #
function obe.scene._Scene:set_future_load(data) end

--- Updates all elements in the Scene.
---
function obe.scene._Scene:update() end

--- Draws all elements of the Scene on the screen.
---
---@param surface obe.graphics.RenderTarget #
function obe.scene._Scene:draw(surface) end

--- Get the name of the level.
---
---@return string
function obe.scene._Scene:get_level_name() end

--- Sets the name of the level.
---
---@param new_name string #A std::string containing the new name of the level
function obe.scene._Scene:set_level_name(new_name) end

--- Enables or disables the Scene update.
---
---@param state boolean #true if the Scene should update, false otherwise
function obe.scene._Scene:set_update_state(state) end

--- Creates a new GameObject.
---
---@param object_type string #Type of the GameObject
---@param id? string #Id of the new GameObject (If empty the id will be randomly generated)
---@return obe.script.GameObject
function obe.scene._Scene:create_game_object(object_type, id) end

--- Get how many GameObjects are present in the Scene.
---
---@return number
function obe.scene._Scene:get_game_object_amount() end

--- Get all the GameObjects present in the Scene.
---
---@param object_type? string #
---@return obe.script.GameObject[]
function obe.scene._Scene:get_all_game_objects(object_type) end

--- Get a GameObject by Id (Raises an exception if not found)
---
---@param id string #Id of the GameObject to retrieve
---@return obe.script.GameObject
function obe.scene._Scene:get_game_object(id) end

--- Check if a GameObject exists in the Scene.
---
---@param id string #Id of the GameObject to check the existence
---@return boolean
function obe.scene._Scene:does_game_object_exists(id) end

--- Removes a GameObject from the Scene.
---
---@param id string #Id of the GameObject to remove from the Scene
function obe.scene._Scene:remove_game_object(id) end

--- Gets the Scene Camera.
---
---@return obe.scene.Camera
function obe.scene._Scene:get_camera() end

--- Reorganize all the Sprite (by layer and sublayer)
---
function obe.scene._Scene:reorganize_layers() end

--- Creates a new Sprite.
---
---@param id? string #Id of the new Sprite
---@param add_to_scene_root? boolean #Add the Sprite to the root Scene Node if true
---@return obe.graphics.Sprite
function obe.scene._Scene:create_sprite(id, add_to_scene_root) end

--- Get how many Sprites are present in the Scene.
---
---@return number
function obe.scene._Scene:get_sprite_amount() end

--- Get all the Sprites present in the Scene.
---
---@return obe.graphics.Sprite[]
function obe.scene._Scene:get_all_sprites() end

--- Get all the Sprites present in the Scene in the given layer.
---
---@param layer number #Layer to get all the Sprites from
---@return obe.graphics.Sprite[]
function obe.scene._Scene:get_sprites_by_layer(layer) end

--- Get the first found Sprite with the BoundingRect including the given position.
---
---@param position obe.transform.UnitVector #Position to check
---@param layer number #Layer where to check
---@return obe.graphics.Sprite
function obe.scene._Scene:get_sprite_by_position(position, layer) end

--- Get a Sprite by Id (Raises an exception if not found)
---
---@param id string #Id of the Sprite to get
---@return obe.graphics.Sprite
function obe.scene._Scene:get_sprite(id) end

--- Check if a Sprite exists in the Scene.
---
---@param id string #Id of the Sprite to check the existence
---@return boolean
function obe.scene._Scene:does_sprite_exists(id) end

--- Removes the Sprite with the given Id.
---
---@param id string #Id of the Sprite to remove
function obe.scene._Scene:remove_sprite(id) end

--- Creates a new Collider.
---
---@param id? string #Id of the new Collider
---@param add_to_scene_root? boolean #Add the Collider to the root Scene Node if true
---@return obe.collision.ColliderComponent
function obe.scene._Scene:create_collider(id, add_to_scene_root) end

--- Get how many Colliders are present in the Scene.
---
---@return number
function obe.scene._Scene:get_collider_amount() end

--- Get all the pointers of the Colliders in the Scene.
---
---@return obe.collision.ColliderComponent[]
function obe.scene._Scene:get_all_colliders() end

--- Get the Collider with the given Id (Raises an exception if not found)
---
---@param id string #Id of the Collider to retrieve
---@return obe.collision.ColliderComponent
function obe.scene._Scene:get_collider(id) end

--- Check the existence of the Collider with given Id in the Scene.
---
---@param id string #Id of the Collider to check the existence
---@return boolean
function obe.scene._Scene:does_collider_exists(id) end

--- Removes the Collider with the given Id from the Scene.
---
---@param id string #Id of the Collider to remove
function obe.scene._Scene:remove_collider(id) end

---@return obe.collision.CollisionSpace
function obe.scene._Scene:get_collision_space() end

---@return obe.scene.SceneNode
function obe.scene._Scene:get_scene_root_node() end

--- Folder where was the map loaded with load_from_file method.
---
---@return string
function obe.scene._Scene:get_filesystem_path() end

--- Reloads the Scene from the level file.
---
function obe.scene._Scene:reload() end

--- Reloads the Scene from the level file.
---
---@param callback obe.scene.OnSceneLoadCallback #Lua Function called when the map has been reloaded
function obe.scene._Scene:reload(callback) end

--- Name of the last loaded map file with load_from_file method.
---
---@return string
function obe.scene._Scene:get_level_file() end

---@param position obe.transform.UnitVector #
---@return obe.scene.SceneNode
function obe.scene._Scene:get_scene_node_by_position(position) end

---@return boolean
function obe.scene._Scene:has_tiles() end

---@return obe.tiles.TileScene
function obe.scene._Scene:get_tiles() end

---@return obe.scene.SceneRenderOptions
function obe.scene._Scene:get_render_options() end

---@param options obe.scene.SceneRenderOptions #
function obe.scene._Scene:set_render_options(options) end

---@param id string #
---@return obe.component.ComponentBase
function obe.scene._Scene:get_component(id) end


---@class obe.scene.SceneNode : obe.transform.Movable
obe.scene._SceneNode = {};


--- Adds a child to the SceneNode.
---
---@param child obe.transform.Movable #Pointer to the new SceneNode child
function obe.scene._SceneNode:add_child(child) end

--- Removes a child from the SceneNode.
---
---@param child obe.transform.Movable #Reference to the SceneNode child to remove
function obe.scene._SceneNode:remove_child(child) end

--- Set the position of the SceneNode and all of its children using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the SceneNode and all of its children
function obe.scene._SceneNode:set_position(position) end

--- Moves the SceneNode (Adds the given position to the current one) and all of its children.
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.scene._SceneNode:move(position) end

--- Set the position of the SceneNode using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the SceneNode
function obe.scene._SceneNode:set_position_without_children(position) end

--- Moves the SceneNode (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.scene._SceneNode:move_without_children(position) end


---@class obe.scene.SceneRenderOptions
---@field sprites boolean #
---@field collisions boolean #
---@field scene_nodes boolean #
obe.scene._SceneRenderOptions = {};




---@alias obe.scene.OnSceneLoadCallback function
---@param self obe.scene.Scene #
---@param id string #
---@return table
function obe.scene.scene_get_game_object_proxy(self, id) end

---@param self obe.scene.Scene #
---@param object_type string #
---@param id? string #
---@return function
function obe.scene.scene_create_game_object_proxy(self, object_type, id) end

---@param self obe.scene.Scene #
---@param object_type? string #
---@return table[]
function obe.scene.scene_get_all_game_objects_proxy(self, object_type) end

return obe.scene;