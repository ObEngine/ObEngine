Local = {}; -- Local Events
Global = {}; -- Global Events
Core = {}; -- Core Lib
Core.ImportedLibs = {} -- List of Imported Lib names
Hook = {}; -- Core Objects
This = {}; -- The Game Object
Lua_ReqList = {}; -- Require Parameters

-- All Core Events Group
KeyPress = {}

local protected = {};
function protect(key, value)
    if _G[key] then
        protected[key] = _G[key];
        _G[key] = nil;
    else
        protected[key] = value;
    end
end

local meta = {
    __index = protected,
    __newindex = function(tbl, key, value);
        if protected[key] then
            error("attempting to overwrite constant " .. tostring(key) .. " to " .. tostring(value), 2);
        end
        rawset(tbl, key, value);
    end
}

setmetatable(_G, meta)

function UseLocalTrigger(trName)
    CPP_UseLocalTrigger(Key, trName);
end

function UseGlobalTrigger(trName)
    CPP_UseGlobalTrigger(Key, trName);
end

function UseCustomTrigger(trNsp, trGrp, trName, useAs)
    CPP_UseCustomTrigger(Key, trNsp, trGrp, trName, useAs);
end

function Import(lib)
    CPP_Import(Key, lib);
end

function GetHook(hook)
    CPP_Hook(Key, hook);
end

function Require(param)
    if (Lua_ReqList[param] ~= nil) then
        return Lua_ReqList[param];
    else
        error("can't find requirement : " .. param);
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