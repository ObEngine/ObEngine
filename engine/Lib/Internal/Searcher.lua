function custom_searcher(module_name)
    local testxd = testxd or 0;
    print("  Searcher Loading module name", module_name, "test is", testxd)
    module_name = module_name:gsub("%.", "/");
    module_name = module_name .. '.lua';
    if module_name:find("://") == nil then
        -- Silenting no prefix for Lua modules
        module_name = "*://" .. module_name .. ".lua";
    end
    local find_result = obe.System.Path(module_name):find();
    if find_result:success() then
        return loadfile(find_result:path(), "bt", setmetatable({testxd = testxd + 1}, {__index=_G}));
    end
end

table.insert(package.searchers, 1, custom_searcher);

-- local _require = require;

-- TODO: Fix require breaking out of _ENV (https://github.com/pygy/require.lua)
--[[function with_require_from(prefix, module_name)
    local function require_from(module_name)
        if module_name:find("://") == nil then
            return _require(prefix .. "://" .. module_name);
        else
            return _require(module_name);
        end
    end
    local module;
    do
        _ENV = setmetatable({require = require_from}, {__index=_G})
        local sandboxed_require = function()
            return require(module_name);
        end
        module = sandboxed_require();
    end
    return module;
end]]

--[[function with_require_from(prefix, module_name)
    local function require_from(module_name)
        if module_name:find("://") == nil then
            return _require(prefix .. "://" .. module_name);
        else
            return _require(module_name);
        end
    end

    require = require_from
    local module = require(module_name);
    require = _require;
    return module;
end]]
