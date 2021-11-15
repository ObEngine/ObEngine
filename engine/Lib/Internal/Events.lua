function LuaCore.EventGroupHooks(id, namespace)
    return {
        __newindex = function(object, key, value)
            if type(value) == "function" then
                local mt = getmetatable(object);
                Engine.Events
                    :getNamespace(namespace)
                    :getGroup(object.id)
                    :get(key)
                    :addExternalListener(id, obe.Event.LuaEventListener(value));
                mt.__storage[key] = value;
            elseif type(value) == "nil" then
                local mt = getmetatable(object);
                mt.__storage[key] = nil;
                Engine.Events
                    :getNamespace(namespace)
                    :getGroup(object.id)
                    :get(key)
                    :removeExternalListener(id);
            end
        end,
        __index = function(object, key)
            local mt = getmetatable(object);
            if mt.__storage[key] then
                return mt.__storage[key];
            else
                error(
                    namespace .. "." .. object.id .. "." .. key ..
                        " is not defined");
            end
        end,
        __clean = function(object)
            local mt = getmetatable(object);
            local groupExists = Engine.Events
                :getNamespace(namespace)
                :doesGroupExists(object.id);
            for key, _ in pairs(mt.__storage) do
                mt.__storage[key] = nil;
                if groupExists then
                    Engine.Events
                        :getNamespace(namespace)
                        :getGroup(object.id)
                        :get(key)
                        :removeExternalListener(id);
                end
            end
        end,
        __call = function(object)
            return Engine.Events:getNamespace(namespace):joinGroup(object.id);
        end,
        __storage = {}
    };
end

function LuaCore.EventNamespaceHooks(id, namespace)
    local hook_mt = {
        __index = function(object, key)
            local groups = Engine.Events:getNamespace(namespace):getAllGroupsNames();
            for _, v in pairs(groups) do
                if v == key then
                    if rawget(object, key) == nil then
                        rawset(object, key, {id = key});
                        setmetatable(rawget(object, key), LuaCore.EventGroupHooks(id, namespace));
                    end
                    return rawget(object, key);
                end
            end
            error("EventGroup " .. key .. " doesn't exists in namespace " ..
                      namespace);
        end,
        __clean = function(object)
            for k, _ in pairs(object) do
                getmetatable(object[k]).__clean(object[k]);
            end
        end,
        __call = function(object)
            return Engine.Events:joinNamespace(namespace);
        end
    };
    return setmetatable({}, hook_mt);
end