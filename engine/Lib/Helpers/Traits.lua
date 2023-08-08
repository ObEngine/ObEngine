---Creates a new GameObjectHandle
---@param object obe.script.GameObject # reference to GameObject
---@return GameObjectCls
function Trait:new(name)
    local instance = {
        --- Internals

        --- Attributes
        -- trait name
        name = name,

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