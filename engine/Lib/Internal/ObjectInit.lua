local GameObjectHandle = require("obe://Lib/Internal/GameObject");
---@ Lib.Internal.Network
local Network = require("obe://Lib/Internal/Network");

local __GAME_OBJECT = GameObjectHandle:new(This);

---@return GameObjectCls
function GameObject()
    return __GAME_OBJECT;
end

-- Engine Events
Event = __GAME_OBJECT:listen("Event");
UserEvent = __GAME_OBJECT:listen("UserEvent");

-- Task hooks
Task = __GAME_OBJECT._task_manager:make_task_hook();

-- Wrappers
function __WRAP_CALL_INIT(...)
    return __GAME_OBJECT:call_init(...);
end

function __WRAP_GET_STORAGE(...)
    return __GAME_OBJECT:get_storage(...);
end

function __WRAP_CALL_DESTROY(...)
    return __GAME_OBJECT:call_destroy(...);
end

-- Network
function host(config)
    return Network.host(__GAME_OBJECT, config);
end

function connect(config)
    return Network.connect(__GAME_OBJECT, config);
end