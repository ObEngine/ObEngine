---@meta

---@type obe.engine.Engine
Engine = {};

---@type obe.script.GameObject
This = {};

---@type obe.events._EventTable
Event = {};

---@type table<string, any>
Global = {};

---@type table<string, function>
Task = {};

---@alias _EventHook userdata

---@class GameObjectCls
---@field components table<string, userdata> #GameObject components
local GameObjectHandle = {};

---Listens to an engine Event
---@param listen_target string#ID of the EventNamespace / EventGroup / Event to listen to (eg. "Event.Game.Update")
---@param callback function#Event Callback (only used if the target is an Event)
---@param listener_id string#Optional Event listener id (defaults to __ENV_ID)
---@return _EventHook #Hook to manager EventNamespace / EventGroup / Event
function GameObjectHandle:listen(listen_target, callback, listener_id)
end

---Deletes an existing listener
---@param listener _EventHook #Hook previously returned by "listen" function
function GameObjectHandle:unlisten(listener)
end

---Creates a new CallbackScheduler attached to the current GameObject
---@return obe.event.CallbackScheduler
function GameObjectHandle:schedule()
end

---Returns GameObject storage (contains all public attributes and methods)
---@return table#GameObject storage
function GameObjectHandle:get_storage()
end

---Gets the current GameObject instance
---@return GameObjectCls
function GameObject()
end

return {Engine, This, Event, Global, Task, GameObjectHandle}
