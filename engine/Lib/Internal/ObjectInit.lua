__ENV_ID = __OBJECT_TYPE .. "." .. __OBJECT_ID;
Object = {type = __OBJECT_TYPE, id = __OBJECT_ID};

__INIT_ARG_TABLE = {};

Local = {};

local ArgMirror = require('obe://Lib/Internal/ArgMirror');
function ObjectInit()
    local Lua_Func_ArgList = ArgMirror.GetArgs(Local.Init);
    local Lua_Func_CallArgs = {};
    for _, i in pairs(Lua_Func_ArgList) do
        if (__INIT_ARG_TABLE[i]) then
            table.insert(Lua_Func_CallArgs, __INIT_ARG_TABLE[i]);
        else
            table.insert(Lua_Func_CallArgs, ArgMirror.__nil_table);
        end
    end
    if Local.Init then Local.Init(ArgMirror.Unpack(Lua_Func_CallArgs)); end
end

local __EVENT_EVENTHOOKS = {};

function listen(namespace)
    local hook = LuaCore.EventNamespaceHooks(__ENV_ID, namespace);
    table.insert(__EVENT_EVENTHOOKS, hook);
    return hook;
end

-- Engine Events
Event = listen("Event");
UserEvent = listen("UserEvent");

function ObjectInitFromLua(argtable)
    argtable = argtable or {};
    __INIT_ARG_TABLE = argtable;
    This:initialize();
    return Object;
end

local __ENV_SCHEDULERS = {};

function Schedule()
    local scheduler = Engine.Events:schedule();
    table.insert(__ENV_SCHEDULERS, scheduler);
    return scheduler;
end

function ObjectDelete()
    for _, eventHook in pairs(__EVENT_EVENTHOOKS) do
        getmetatable(eventHook).__clean(eventHook);
    end
    for _, scheduler in pairs(__ENV_SCHEDULERS) do scheduler:stop(); end
    if Local.Delete then Local.Delete(); end
end
