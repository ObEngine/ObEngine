---@meta

obe.script = {};
---@class obe.script.GameObject : obe.types.Identifiable, obe.types.Serializable
---@field deletable boolean #Delete State of the GameObject (false = not deleted)
---@field Animator obe.animation.Animator #Gets the Animator Component of the GameObject (Raises ObEngine.Script.GameObject.NoAnimator if no Animator Component)
---@field Collider obe.collision.PolygonalCollider #Gets the Collider Component of the GameObject (Raises ObEngine.Script.GameObject.NoCollider if no Collider Component)
---@field Sprite obe.graphics.Sprite #Gets the Sprite Component of the GameObject (Raises ObEngine.Script.GameObject.NoSprite if no Sprite Component)
---@field SceneNode obe.scene.SceneNode #Gets the Scene Node of the GameObject (SceneNode that can manipulate the position of all Scene Components)
obe.script._GameObject = {};

--- Creates a new GameObject.
---
---@param lua sol.state_view #
---@param type string #Type of the GameObject
---@param id string #Id of the GameObject you want to create
---@return obe.script.GameObject
function obe.script.GameObject(lua, type, id) end


--- Get the Type of the GameObject.
---
---@return string
function obe.script._GameObject:get_type() end

--- Checks if the GameObject has an Animator Component.
---
---@return boolean
function obe.script._GameObject:does_have_animator() end

--- Checks if the GameObject has a Collider Component.
---
---@return boolean
function obe.script._GameObject:does_have_collider() end

--- Checks if the GameObject has a Sprite Component.
---
---@return boolean
function obe.script._GameObject:does_have_sprite() end

--- Checks if the GameObject has a Script Component.
---
---@return boolean
function obe.script._GameObject:does_have_script_engine() end

--- Is the GameObject updated.
---
---@return boolean
function obe.script._GameObject:get_update_state() end

--- Sets if the GameObject should be otherwise or not.
---
---@param state boolean #Should be equal to true if the GameObject must updates, false otherwise
function obe.script._GameObject:set_update_state(state) end

--- Execute a Lua String in the Lua State of the GameObject.
---
---@param query string #String to execute
function obe.script._GameObject:exec(query) end

---@param data vili.node #
function obe.script._GameObject:init_from_vili(data) end

--- Loads the GameObject through the GameObject Definition File.
---
---@param scene obe.scene.Scene #Scene reference to create components
---@param obj vili.node #Vili Node containing the GameObject components
---@param resources? obe.engine.ResourceManager #pointer to the ResourceManager
function obe.script._GameObject:load_game_object(scene, obj, resources) end

--- Updates the GameObject.
---
function obe.script._GameObject:update() end

--- Deletes the GameObject.
---
function obe.script._GameObject:destroy() end

--- Access the exposition table of the GameObject.
---
---@return table
function obe.script._GameObject:access() end

--- Gets a reference to the Lua function used to build the GameObject (GameObject:init proxy)
---
---@return function
function obe.script._GameObject:get_constructor() end

--- Calls the GameObject constructor
---
function obe.script._GameObject:initialize() end

--- Configures the permanent parameter of the GameObject.
---
---@param permanent boolean #Should be true if the GameObject should be permanent, false otherwise
function obe.script._GameObject:set_permanent(permanent) end

--- Gets if the GameObject is permanent (Will stay after loading another map)
---
---@return boolean
function obe.script._GameObject:is_permanent() end

---@return sol.environment
function obe.script._GameObject:get_outer_environment() end

---@param state boolean #
function obe.script._GameObject:set_state(state) end

--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.script._GameObject:schema() end

--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.script._GameObject:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.script._GameObject:load(data) end

---@param path string #
---@param env obe.script.EnvironmentTarget #
function obe.script._GameObject:load_source(path, env) end


---@class obe.script.GameObjectDatabase
obe.script._GameObjectDatabase = {};


--- Gets the Requires ComplexNode of the GameObject.
---
---@param type string #Type of the GameObject to get the Requirements
---@return vili.node
function obe.script._GameObjectDatabase:get_requirements_for_game_object(type) end

--- Gets the ObjectDefinition ComplexNode of the GameObject.
---
---@param type string #Type of the GameObject to get the GameObject Definition File
---@return vili.node
function obe.script._GameObjectDatabase:get_definition_for_game_object(type) end

--- Clears the GameObjectDatabase (cache reload)
---
function obe.script._GameObjectDatabase:clear() end


---@class obe.script.LuaState : sol.state
obe.script._LuaState = {};


---@param config vili.node #
function obe.script._LuaState:load_config(config) end


---@param status sol.call_status #
---@return string
function obe.script.sol_call_status_to_string(status) end

---@param callback function #
---@param args Args &&... #
---@return ReturnType
function obe.script.safe_lua_call(callback, args) end


--- 
---
---@class obe.script.EnvironmentTarget
obe.script.EnvironmentTarget = {
    Outer = 0,
    Inner = 1,
};
return obe.script;