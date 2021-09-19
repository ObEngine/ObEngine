local function custom_searcher(module_name)
    module_name = module_name:gsub("%.", "/");
    module_name = module_name .. '.lua';
    if module_name:find("://") == nil then
        -- Silenting no prefix for Lua modules
        module_name = "*://" .. module_name .. ".lua";
    end
    local find_result = obe.System.Path(module_name):find();
    if find_result:success() then
        return loadfile(find_result:path());
    end
end

table.insert(package.searchers, 1, custom_searcher);

local _require = require;

local function require_from_obe(module_name)
    if module_name:find("://") == nil then
        return _require("obe://" .. module_name);
    else
        return _require(module_name);
    end
end

function with_require_from_obe(func)
    require = require_from_obe;
    func();
    require = _require;
end
