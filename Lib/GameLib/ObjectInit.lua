Local = {}; -- Local Events
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

function LuaCore.Lua_LocalInit_Unpack(t, i)
    i = i or 1
    if t[i] ~= nil then
        return t[i], LuaCore.Lua_LocalInit_Unpack(t, i + 1)
    end
end

function LuaCore.LocalInitMirrorInjector()
    local Lua_LocalInit_ArgMirror = require('Lib/StdLib/ArgMirror');
    local Lua_LocalInit_ArgList = Lua_LocalInit_ArgMirror(Local.Init);
    local Lua_LocalInit_CallArgs = {};
    for _, i in pairs(Lua_LocalInit_ArgList) do
        table.insert(Lua_LocalInit_CallArgs, LuaCore.Lua_ReqList[i]);
    end
    Local.Init(LuaCore.Lua_LocalInit_Unpack(Lua_LocalInit_CallArgs));
    This:setInitialised(true);
end

function IsArgumentInRequireList(paramName)
    if (LuaCore.Lua_ReqList[paramName] ~= nil) then
        return true;
    else
        return false;
    end
end

function Local.Init()
end
function Local.Update()
end
function Local.Collide()
end
function Local.Click()
end
function Local.Delete()
end
function Local.Save()
    return {};
end