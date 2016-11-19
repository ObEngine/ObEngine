Core = {}; -- Core Lib
Core.ImportedLibs = {} -- List of Imported Lib names
Hook = {}; -- Core Objects

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

function Import(lib)
    CPP_Import(This, lib);
end

function GetHook(hook)
    CPP_Hook(This, hook);
end