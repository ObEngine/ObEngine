Local = {}; -- Local Events
Global = {}; -- Global Events
Lua_ReqList = {}; -- Require Parameters

function Require(param)
    if (Lua_ReqList[param] ~= nil) then
        return Lua_ReqList[param];
    else
        error("Can't find requirement : " .. param);
    end
end

function Local.InitMirrorInjector()
    local Lua_LocalInit_Unpack = function(t, i)
        i = i or 1
        if t[i] ~= nil then
            return t[i], unpack(t, i + 1)
        end
    end
    local Lua_LocalInit_ArgMirror = require('Lib/StdLib/ArgMirror');
    local Lua_LocalInit_ArgList = Lua_LocalInit_ArgMirror(Local.Init);
    local Lua_LocalInit_CallArgs = {};
    for _, i in pairs(Lua_LocalInit_ArgList) do
        table.insert(Lua_LocalInit_CallArgs, Lua_ReqList[i]);
    end
    Local.Init(unpack(Lua_LocalInit_CallArgs));
end

function IsArgumentInRequireList(paramName)
    if (Lua_ReqList[paramName] ~= nil) then
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