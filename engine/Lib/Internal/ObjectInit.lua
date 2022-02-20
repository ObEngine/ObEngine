__ENV_ID = __OBJECT_TYPE .. "." .. __OBJECT_ID;
Object = {type = __OBJECT_TYPE, id = __OBJECT_ID};

__INIT_ARG_TABLE = {};

Local = {};

local ArgMirror = require('obe://Lib/Internal/ArgMirror');
function ObjectInit()
    if Local.Init == nil then
        return;
    end
    local Lua_Func_ArgList = ArgMirror.GetArgs(Local.Init);
    local Lua_Func_CallArgs = {};
    for _, i in pairs(Lua_Func_ArgList) do
        if (__INIT_ARG_TABLE[i]) then
            table.insert(Lua_Func_CallArgs, __INIT_ARG_TABLE[i]);
        else
            table.insert(Lua_Func_CallArgs, ArgMirror.__nil_table);
        end
    end
    Local.Init(ArgMirror.Unpack(Lua_Func_CallArgs));
end

local __ENV_EVENTHOOKS = {};

local Events = require('obe://Lib/Internal/Events');

function listen(listen_target, callback, listener_id)
    if listener_id == nil then
        listener_id = __ENV_ID;
    elseif type(listener_id) == "string" then
        listener_id = ("%s.%s"):format(__ENV_ID, listener_id);
    else
        error(("expect listener_id parameter to be a <string> (got <%s>)"):format(type(listener_id)));
    end
    local suffix = #__ENV_EVENTHOOKS;
    while __ENV_EVENTHOOKS[listener_id .. "." .. tostring(suffix)] do
        suffix = suffix + 1;
    end
    listener_id = listener_id .. "." .. tostring(suffix);
    local hook = Events.listen(listen_target, callback, listener_id);
    __ENV_EVENTHOOKS[listener_id] = hook;
    return hook;
end

function unlisten(hook)
    local listener_id = getmetatable(hook).listener_id;
    getmetatable(hook).clean(hook);
    setmetatable(hook, nil);
    __ENV_EVENTHOOKS[listener_id] = nil;
end

local __ENV_SCHEDULERS = {};

function schedule()
    local scheduler = Engine.Events:schedule();
    table.insert(__ENV_SCHEDULERS, scheduler);
    return scheduler;
end

-- Engine Events
Event = listen("Event");
UserEvent = listen("UserEvent");

-- Task Manager
local TaskManager = require("obe://Lib/Internal/Tasks").TaskManager;
__TM = TaskManager({listen = listen, unlisten = unlisten, schedule = schedule});
Task = __TM:make_task_hook();

function ObjectInitFromLua(argtable)
    argtable = argtable or {};
    __INIT_ARG_TABLE = argtable;
    This:initialize();
    return Object;
end

function ObjectDelete()
    __TM:clean();
    for _, hook in pairs(__ENV_EVENTHOOKS) do
        unlisten(hook);
    end
    for _, scheduler in pairs(__ENV_SCHEDULERS) do
        scheduler:stop();
    end
    if Local.Delete then
        Local.Delete();
    end
    collectgarbage("collect");
    collectgarbage("collect");
end
