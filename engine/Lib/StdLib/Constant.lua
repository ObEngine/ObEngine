const_protected = {};
local function const(key, value)
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

return const;