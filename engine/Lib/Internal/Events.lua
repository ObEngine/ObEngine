local function EventHook(listener_id, namespace, group, event, callback)
    local lua_listener = obe.event.LuaEventListener(callback);
    Engine.Events:get_namespace(namespace)
                 :get_group(group)
                 :get(event)
                 :add_external_listener(listener_id, lua_listener);
    local hook_mt = {
        __call = function(object, ...)
            object.callback(...);
        end,
        clean = function(object)
            Engine.Events:get_namespace(namespace)
                         :get_group(group)
                         :get(event)
                         :remove_external_listener(listener_id);
        end,
        listener_id = listener_id,
        event_id = ("%s.%s.%s"):format(namespace, group, event)
    };
    return setmetatable({callback = callback}, hook_mt);
end

local function EventGroupHook(listener_id, namespace, group)
    local hook_mt = {
        __newindex = function(object, event, callback)
            if type(callback) == "function" then
                local mt = getmetatable(object);
                Engine.Events:get_namespace(namespace):get_group(group):get(event)
                    :add_external_listener(
                        listener_id, obe.event.LuaEventListener(callback)
                    );
                mt.__storage[event] = setmetatable(
                    {}, {
                        __call = callback,
                        listener_id = listener_id,
                        event_id = ("%s.%s.%s"):format(namespace, group, event)
                    }
                );
            elseif type(callback) == "nil" then
                local mt = getmetatable(object);
                mt.__storage[event] = nil;
                Engine.Events:get_namespace(namespace):get_group(group):get(event)
                    :remove_external_listener(
                        listener_id
                    );
            else
                error(
                    ("unsupported callback for event %s.%s.%s (expects <function> or <nil>)"):format(
                        namespace, group, event
                    )
                );
            end
        end,
        __index = function(object, event)
            local mt = getmetatable(object);
            if mt.__storage[event] then
                return mt.__storage[event];
            else
                if Engine.Events:get_namespace(namespace):get_group(group):contains(event) then
                    return setmetatable(
                        {}, {
                            __call = function()
                                error(
                                    ("Callback for event %s.%s.%s is not implemented"):format(
                                        namespace, group, event
                                    )
                                );
                            end,
                            listener_id = listener_id,
                            event_id = ("%s.%s.%s"):format(namespace, group, event)
                        }
                    );
                else
                    error(("Event %s.%s.%s does not exists"):format(namespace, group, event));
                end
            end
        end,
        clean = function(object)
            local mt = getmetatable(object);
            local group_exists = Engine.Events:get_namespace(namespace):does_group_exists(group);
            for event_name, _ in pairs(mt.__storage) do
                mt.__storage[event_name] = nil;
                if group_exists then
                    Engine.Events:get_namespace(namespace):get_group(group):get(event_name)
                        :remove_external_listener(
                            listener_id
                        );
                end
            end
        end,
        __call = function(object)
            return Engine.Events:get_namespace(namespace):joinGroup(group);
        end,
        __storage = {},
        listener_id = listener_id
    };
    return setmetatable({}, hook_mt);
end

local function EventNamespaceHook(listener_id, namespace)
    local hook_mt = {
        __index = function(object, key)
            local mt = getmetatable(object);
            local groups = Engine.Events:get_namespace(namespace):get_all_groups_names();
            for _, v in pairs(groups) do
                if v == key then
                    if mt.__storage[key] == nil then
                        mt.__storage[key] = EventGroupHook(listener_id, namespace, key);
                    end
                    return mt.__storage[key];
                end
            end
            error("EventGroup " .. key .. " doesn't exists in namespace " .. namespace);
        end,
        clean = function(object)
            local mt = getmetatable(object);
            for event_group_name, group_hook in pairs(mt.__storage) do
                getmetatable(group_hook).clean(group_hook);
            end
        end,
        __call = function(object)
            return Engine.Events:joinNamespace(namespace);
        end,
        __storage = {},
        listener_id = listener_id
    };
    return setmetatable({}, hook_mt);
end

local function listen(listen_target, callback, listener_id)
    local _, dots_in_listen_target = string.gsub(listen_target, "%.", "")
    if dots_in_listen_target == 0 then
        return EventNamespaceHook(listener_id, listen_target);
    elseif dots_in_listen_target == 1 then
        local match = string.gmatch(listen_target, "([^.]+).([^.]+)");
        local event_namespace, event_group = match();
        return EventGroupHook(listener_id, event_namespace, event_group);
    elseif dots_in_listen_target == 2 then
        if type(callback) ~= "function" then
            error("must specify second argument 'callback' to listen of type <function>");
        end
        local match = string.gmatch(listen_target, "([^.]+).([^.]+).([^.]+)");
        local event_namespace, event_group, event_name = match();
        return EventHook(listener_id, event_namespace, event_group, event_name, callback);
    end
end

return {
    EventHook = EventHook,
    EventGroupHook = EventGroupHook,
    EventNamespaceHook = EventNamespaceHook,
    listen = listen
}
