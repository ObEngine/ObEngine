local ArgMirror = require('obe://Lib/Internal/ArgMirror');
local Events = require('obe://Lib/Internal/Events');
local TaskManager = require("obe://Lib/Internal/Tasks").TaskManager;

local ComponentsMT = {
    __index = function(tbl, key)
        local obj = tbl._object;
        local component_dispatcher = {
            Animator = function()
                return obj.Animator;
            end,
            Collider = function()
                return obj.Collider;
            end,
            SceneNode = function()
                return obj.SceneNode;
            end,
            Sprite = function()
                return obj.Sprite;
            end,
        };
        if component_dispatcher[key] == nil then
            error(("could not find component '%s'"):format(key));
        end
        return component_dispatcher[key]();
    end
};

local function make_storage(handle)
    return setmetatable({}, {
        __index = handle
    });
end

---@class GameObjectCls
local GameObjectHandle = {};

GameObjectHandle.__index = GameObjectHandle;

function GameObjectHandle:listen(listen_target, callback, listener_id)
    if listener_id == nil then
        listener_id = self._full_id;
    elseif type(listener_id) == "string" then
        listener_id = ("%s.%s"):format(self._full_id, listener_id);
    else
        error(("expect listener_id parameter to be a <string> (got <%s>)"):format(type(listener_id)));
    end
    local suffix = #self._events_listeners;
    while self._events_listeners[listener_id .. "." .. tostring(suffix)] do
        suffix = suffix + 1;
    end
    listener_id = listener_id .. "." .. tostring(suffix);
    local listener = Events.listen(listen_target, callback, listener_id);
    self._events_listeners[listener_id] = listener;
    return listener;
end

function GameObjectHandle:unlisten(listener)
    local listener_id = getmetatable(listener).listener_id;
    getmetatable(listener):clean();
    setmetatable(listener, nil);
    self._events_listeners[listener_id] = nil;
end

function GameObjectHandle:schedule()
    local scheduler = Engine.Events:schedule();
    table.insert(self._schedulers, scheduler);
    return scheduler;
end

function GameObjectHandle:_initialize_traits()
    for _, trait in pairs(self._traits) do
        if trait._requires_initialisation and not trait._initialized then
            error(
                ("GameObject '%s' of type '%s' must initialize trait '%s' (with self:super.%s(...))"):format(
                    self.id,
                    self.type,
                    trait.name,
                    trait.name
                )
            );
        end
    end
end

function GameObjectHandle:call_init(arg_table)
    if self._initialized then
        return;
    end
    if arg_table then
        self._constructor_arg_values = arg_table;
    end
    if self.init == nil then
        return;
    end
    local arg_list = ArgMirror.get_args(self.init);
    if arg_list[1] == "self" then
        table.remove(arg_list, 1); -- remove self from arglist
    end
    local args_to_be_unpacked = {};
    for _, arg_name in pairs(arg_list) do
        local arg_value = self._constructor_arg_values[arg_name];
        if arg_value ~= nil then
            table.insert(args_to_be_unpacked, arg_value);
        else
            table.insert(args_to_be_unpacked, ArgMirror._nil_table);
        end
    end
    self._initialized = true;
    self:init(ArgMirror.unpack_with_nil(args_to_be_unpacked));
    self:_initialize_traits();
    return self._storage;
end

function GameObjectHandle:get_storage()
    return self._storage;
end

function GameObjectHandle:call_destroy()
    self._task_manager:clean();
    for _, listener in pairs(self._events_listeners) do
        self:unlisten(listener);
    end
    for _, scheduler in pairs(self._schedulers) do
        scheduler:stop();
    end
    if self.destroy then
        self:destroy();
    end
    collectgarbage("collect");
    collectgarbage("collect");
end

function GameObjectHandle:__newindex(key, value)
    self._storage[key] = value;
end

function GameObjectHandle:__index(key)
    local value_from_storage = rawget(self._storage, key);
    if value_from_storage == nil then
        return GameObjectHandle[key];
    else
        return value_from_storage;
    end
end

---Creates a new GameObjectHandle
---@param object obe.script.GameObject # reference to GameObject
---@return GameObjectCls
function GameObjectHandle:new(object)
    local instance = {
        --- Internals
        -- Used to store event hooks
        _events_listeners = {},
        -- ID used for all event listeners
        _full_id = ("%s.%s"):format(object:get_type(), object:get_id()),
        -- Flag to detect whether the GameObject is already initialized or not
        _initialized = false,
        -- Used to store constructor arguments
        _constructor_arg_values = {},
        -- Reference to object
        _object = object,
        -- Used to store all schedulers
        _schedulers = {},
        -- All the object traits
        _traits = {},

        --- Attributes
        components = setmetatable({_object=object}, ComponentsMT),
        id = object:get_id(),
        type = object:get_type(),

        --- Methods
        -- placeholder for init function
        init = function()

        end,
        -- placeholder for destroy function
        destroy = function()

        end,
    };

    instance._task_manager = TaskManager {
        listen = function(...) return instance:listen(...); end,
        unlisten = function(...) return instance:unlisten(...) end,
        schedule = function(...) return instance:schedule(...) end,
    };
    instance._storage = make_storage(instance);

    return setmetatable(instance, self);
end

return GameObjectHandle;