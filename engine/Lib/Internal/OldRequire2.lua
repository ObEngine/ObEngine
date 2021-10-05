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

local function make_require_from_prefix(prefix, inherit_context)
    local _ENV = setmetatable({require = inherit_context or require}, {__index=_G});
    print("0] BUILD REQUIRE @=", require, "ic=", inherit_context);

    local function custom_searcher(module_name)
        if module_name == "obe://Lib/Extlibs/pl/List" then
            dbg();
        end
        print("  Searcher Loading module name", module_name, "require=", require)
        module_name = module_name:gsub("%.", "/");
        module_name = module_name .. '.lua';
        if module_name:find("://") == nil then
            -- Silenting no prefix for Lua modules
            module_name = "*://" .. module_name .. ".lua";
        end
        local find_result = obe.System.Path(module_name):find();
        if find_result:success() then
            return loadfile(find_result:path(), "bt", _ENV);
        end
    end

    local function inner_require(module_name)
        local _ENV = setmetatable({require = inherit_context or inner_require}, {__index=_G})
        local module_prefix, module_name_no_prefix = split_prefix_module_name(module_name);
        print("1] INNER REQUIRE INFO mp=", module_prefix, "p=", prefix, "@=", require);
        if module_prefix ~= nil and module_prefix ~= prefix then
            print("  2] BUILD NEW REQUIRE mp=", module_prefix, "p=", prefix, "@=", require);
            local require_for_prefix = make_require_from_prefix(module_prefix, inner_require);
            debug.setupvalue(require_for_prefix, 2, require_for_prefix);
            return require_for_prefix(module_name);
        else
            print("  2] BASE_REQUIRE mp=", module_prefix, "p=", prefix, "@=", require);
            local module_name = (module_prefix or prefix or "cwd") .. "://" .. module_name_no_prefix;
            module_name = checkstring(module_name)
            local module = p_loaded[module_name]
            if module then return module end

            local msg = {}
            local loader, param
            print("    3] Just before custom searcher require=", require);
            loader, param = custom_searcher(module_name);
            print("    3] Just after custom searcher require=", require);
            if type(loader) ~= "function" then
                msg[#msg + 1] = loader;
                for _, searcher in ipairs(package.searchers) do
                    loader, param = searcher(module_name)
                    if type(loader) == "function" then break end
                    if type(loader) == "string" then
                        -- `loader` is actually an error message
                        msg[#msg + 1] = loader
                    end
                    loader = nil
                end
            end

            if loader == nil then
                error("module '" .. module_name .. "' not found: "..t_concat(msg), 2)
            end
            local res = loader(module_name, param)
            if res ~= nil then
                module = res
            elseif not p_loaded[module_name] then
                module = true
            else
            module = p_loaded[module_name]
            end

            p_loaded[module_name] = module
            return module
        end
    end
    return inner_require
end

require = make_require_from_prefix("cwd");
print("ROOT REQUIRE IS", require);

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