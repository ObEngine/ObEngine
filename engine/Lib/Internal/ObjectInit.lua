__ENV_ID = __OBJECT_TYPE .. "." .. __OBJECT_ID;
Object = {
    type = __OBJECT_TYPE;
    id = __OBJECT_ID;
};

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
            table.insert(Lua_Func_CallArgs, __nil_table);
        end
    end
    print("Prepare to call LocalInit");
    if Local.Init then
        print("Calling it");
        Local.Init(ArgMirror.Unpack(Lua_Func_CallArgs));
    end
    print("Dayum")
end

-- Engine Events
Event = LuaCore.EventNamespaceHooks(Object.type .. "." .. Object.id, "Event");

function ObjectInitFromLua(argtable)
    local argt = argtable or {};
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
    getmetatable(Event).__clean(Event);
    for _, scheduler in pairs(__ENV_SCHEDULERS) do
        scheduler:stop();
    end
    if Local.Delete then
        Local.Delete();
    end
end