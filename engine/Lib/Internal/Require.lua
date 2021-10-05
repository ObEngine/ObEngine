__STD_REQUIRE = require;

local function checkstring(s)
    local t = type(s)
    if t == "string" then
        return s
    elseif t == "number" then
        return tostring(s)
    else
        error("bad argument #1 to 'require' (string expected, got "..t..")", 3)
    end
end

local package, p_loaded = package, package.loaded;
local error, ipairs, type = error, ipairs, type;
local t_concat = table.concat

-- Drop in replacement for `require` function
-- Allows to use upvalue system instead of globally replace `require` (unsafe)
local function make_base_require()
    return function(name)
        print("BASE REQUIRE", name, require);
        name = checkstring(name)
        local module = p_loaded[name]
        if module then return module end

        local msg = {}
        local loader, param
        for _, searcher in ipairs(package.searchers) do
            loader, param = searcher(name)
            if type(loader) == "function" then break end
            if type(loader) == "string" then
                -- `loader` is actually an error message
                msg[#msg + 1] = loader
            end
            loader = nil
        end
        if loader == nil then
            error("module '" .. name .. "' not found: "..t_concat(msg), 2)
        end
        local res = loader(name, param)
        if res ~= nil then
            module = res
        elseif not p_loaded[name] then
            module = true
        else
        module = p_loaded[name]
        end

        p_loaded[name] = module
        return module
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

local function make_require_from_prefix(prefix)
    print("Building require with prefix", prefix);
    return function(module_name)
        print("Invoking require with prefix", prefix);
        local module_prefix, module_name_no_prefix = split_prefix_module_name(module_name);
        if module_prefix ~= nil and module_prefix ~= prefix then
            print("Found different prefix", prefix, "opening sandbox...");
            local module;
            do
                local require_for_prefix = make_require_from_prefix(module_prefix);
                local _ENV = setmetatable({require = require_for_prefix}, {__index=_G})
                print("Env set, calling subrequire", require);
                module = require(module_name);
            end
            print("ENVIRONMENT DONE")
            return module;
        else
            print("Same prefix, calling base require", prefix .. "://" .. module_name_no_prefix);
            return base_require(prefix .. "://" .. module_name_no_prefix);
        end
    end
end

-- require = make_require_from_prefix("cwd");

--[[function xrequire(module_name)
    local require_bootstrap = false;
    if __ENV_REQUIRE_PREFIX == nil then
        require_bootstrap = true;
    end
    local prefix = __ENV_REQUIRE_PREFIX or "cwd";
    local prefix_index = module_name:find("://");
    local module_name_no_prefix = module_name;
    print("=================================================== REQUIRE", module_name, "on", __ENV_REQUIRE_PREFIX);
    if prefix_index ~= nil then
        module_name_no_prefix = module_name:sub(prefix_index + 3);
        local new_prefix = module_name:sub(0, prefix_index - 1);
        if new_prefix ~= prefix then
            print("  FOUND NEW PREFIX", new_prefix);
            prefix = new_prefix;
            require_bootstrap = true;
        end
    end
    if require_bootstrap then
        print("Use new prefix", prefix);
        do
            print("s1", __ENV_REQUIRE_PREFIX);
            local _ENV = setmetatable({__ENV_REQUIRE_PREFIX = prefix}, {__index=_G})
            print("s2", __ENV_REQUIRE_PREFIX);
            local sandboxed_require = function()
                print("In sandbox", __ENV_REQUIRE_PREFIX, "call", module_name);
                return require(module_name);
            end
            print("s3", __ENV_REQUIRE_PREFIX);
            return sandboxed_require();
        end
    else
        print("Use parent prefix", __ENV_REQUIRE_PREFIX);
        return base_require(__ENV_REQUIRE_PREFIX .. "://" .. module_name_no_prefix);
    end
    local function require_from(module_name)
        if module_name:find("://") == nil then
            print("  NO PREFIX GIVEN, USE PARENT", prefix);
            return base_require(prefix .. "://" .. module_name);
        else
            return base_require(module_name);
        end
    end

end]]