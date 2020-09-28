function LuaCore.EventGroupHooks(GameObject, namespace)
    return {
        __newindex = function(table, key, value)
            if type(value) == "function" then
                local mt = getmetatable(table);
                local alias = mt.__alias_function(namespace,
                table.triggerGroupId, key);
                GameObject:useTrigger(namespace, table.triggerGroupId, key,
                                      alias);
                mt.__storage[key] = value;
            elseif type(value) == "nil" then
                local mt = getmetatable(table);
                mt.__storage[key] = nil;
                GameObject:removeTrigger(namespace, table.triggerGroupId, key);
            end
        end,
        __index = function(object, index)
            local mt = getmetatable(object);
            if mt.__storage[index] then
                return mt.__storage[index];
            else
                error(
                    namespace .. "." .. object.triggerGroupId .. "." .. index ..
                        " is not defined");
            end
        end,
        __storage = {}
    };
end

function LuaCore.MakeTriggerGroupHook(GameObject, namespace)
    local hook_mt = {
        __index = function(table, key)
            for _, v in pairs(
                            Engine.Triggers:getAllTriggersGroupNames(namespace)) do
                if v == key then
                    if rawget(table, key) == nil then
                        rawset(table, key, {triggerGroupId = key});
                        setmetatable(rawget(table, key),
                                     LuaCore.MakeTriggerGroupSubTable(
                                         GameObject, namespace));
                    end
                    return rawget(table, key);
                end
            end
            error("Trigger " .. key .. " doesn't exists in namespace " ..
                      namespace);
        end
    };
    local hook_table = {};
    setmetatable(hook_table, hook_mt);
    return hook_table;
end