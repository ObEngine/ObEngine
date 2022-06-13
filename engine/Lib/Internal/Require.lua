__STD_REQUIRE = require;

local function checkstring(s)
    local t = type(s)
    if t == "string" then
        return s
    elseif t == "number" then
        return tostring(s)
    else
        error("bad argument #1 to 'require' (string expected, got " .. t .. ")", 3)
    end
end

local function split_prefix_module_name(module_name)
    local prefix_index = module_name:find("://");
    if prefix_index ~= nil then
        local prefix = module_name:sub(0, prefix_index - 1);
        local module_name_no_prefix = module_name:sub(prefix_index + 3);
        return prefix, module_name_no_prefix;
    end
    return nil, module_name;
end

local function make_prefix_searcher(prefix)
    return function(module_name)
        local module_prefix, _ = split_prefix_module_name(module_name);
        module_name = module_name:gsub("%.", "/");

        if module_prefix == nil then
            -- Silenting no prefix for Lua modules
            module_name = prefix .. "://" .. module_name;
        end

        module_name = module_name .. '.lua';

        local find_result = obe.system.Path(module_name):find();
        if find_result:success() then
            local loadfile_env = setmetatable(
                {require = make_base_require(module_prefix or prefix)}, {__index = _G}
            );
            local func, err = loadfile(find_result:path(), "bt", loadfile_env);
            if err then
                error(err);
            end
            return func;
        else
            return "\n        no file " .. module_name .. " (default prefix: " .. prefix .. ")";
        end
    end
end

-- Drop in replacement for `require` function
-- Allows to use upvalue system instead of globally replace `require` (unsafe)
function make_base_require(prefix)
    local env_searchers = setmetatable(
        {[#package.searchers] = make_prefix_searcher(prefix)}, {__index = package.searchers}
    );
    local env_package = setmetatable({searchers = env_searchers}, {__index = package});
    local _ENV = setmetatable({package = env_package}, {__index = _G});
    return function(name)
        name = checkstring(name)
        local module = package.loaded[name]
        if module then
            return module
        end

        local msg = {}
        local loader, param
        for _, searcher in ipairs(package.searchers) do
            loader, param = searcher(name)
            if type(loader) == "function" then
                break
            end
            if type(loader) == "string" then
                -- `loader` is actually an error message
                msg[#msg + 1] = loader
            end
            loader = nil
        end
        if loader == nil then
            error("module '" .. name .. "' not found:\n" .. table.concat(msg), 2)
        end
        local res = loader(name, param)
        if res ~= nil then
            module = res
        elseif not package.loaded[name] then
            module = true
        else
            module = package.loaded[name]
        end

        package.loaded[name] = module
        return module
    end
end

require = make_base_require("cwd");
