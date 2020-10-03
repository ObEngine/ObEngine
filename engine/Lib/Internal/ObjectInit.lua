__ENV_ID = __OBJECT_TYPE .. "." .. __OBJECT_ID;
Object = {
    type = __OBJECT_TYPE;
    id = __OBJECT_ID;
};

__INIT_ARG_TABLE = {};

Local = {};

local ArgMirror = require('Lib/Internal/ArgMirror');
function __CALL_INIT()
    local Lua_Func_ArgList = ArgMirror.GetArgs(Local.Init);
    local Lua_Func_CallArgs = {};
    for _, i in pairs(Lua_Func_ArgList) do
        if (__INIT_ARG_TABLE[i]) then
            table.insert(Lua_Func_CallArgs, __INIT_ARG_TABLE[i]);
        else
            table.insert(Lua_Func_CallArgs, __nil_table);
        end
    end
    Local.Init(ArgMirror.Unpack(Lua_Func_CallArgs));
end

-- Engine Events
Event = LuaCore.EventNamespaceHooks(Object.type .. "." .. Object.id, "Event");

function ObjectInit(argtable)
    local argt = argtable or {};
    __INIT_ARG_TABLE = argtable;
    This:initialize();
    return Object;
end

function ObjectDelete()
    getmetatable(Event).__clean(Event);
end