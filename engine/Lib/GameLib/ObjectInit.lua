Local = {}; -- Local Events
Local__Meta = {
    __newindex = function(object, index, value)
        rawset(object, index, value);
        print("Using Trigger : " .. index);
        This:useLocalTrigger(index);
    end
}
setmetatable(Local, Local__Meta);

Global = {}; -- Global Events
LuaCore = {};
LuaCore.Lua_ReqList = {}; -- Require Parameters

function Require(param)
    if (LuaCore.Lua_ReqList[param] ~= nil) then
        return LuaCore.Lua_ReqList[param];
    else
        error("Can't find requirement : " .. param);
    end
end

function LuaCore.LocalInitMirrorInjector()
    local ArgMirror = require('Lib/StdLib/ArgMirror');
    local Lua_LocalInit_ArgList = ArgMirror.GetArgs(Local.Init);
    local Lua_LocalInit_CallArgs = {};
    for _, i in pairs(Lua_LocalInit_ArgList) do
        table.insert(Lua_LocalInit_CallArgs, LuaCore.Lua_ReqList[i]);
    end
    Local.Init(ArgMirror.Unpack(Lua_LocalInit_CallArgs));
    This:setInitialised(true);
end

function IsArgumentInRequireList(paramName)
    if (LuaCore.Lua_ReqList[paramName] ~= nil) then
        return true;
    else
        return false;
    end
end

-- Local.Init
-- Local.Update
-- Local.Collide
-- Local.Query
-- Local.Click
-- Local.Delete
-- Local.Save

function Local.Save()
    return {};
end