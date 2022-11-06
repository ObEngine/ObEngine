local function merge_tables(t1, t2)
    local t3 = {};
    for k, v in pairs(t1) do t3[k] = v end
    for k, v in pairs(t2) do t3[k] = v end
    return t3;
end

local function EventHook(listener_id, namespace, group, event, callback)
    local hook_mt = {
        __call = function(object, ...)
            local mt = getmetatable(object);
            if mt.event_emit_wrapper then
                return mt.event_emit_wrapper(object, ...);
            end
            return object.callback(...);
        end,
        __index = function(object, flags)
            assert(type(flags) == "table", "event flags must be a table");
            return function(...)
                object(..., flags);
            end
        end,
        clean = function(self)
            Engine.Events:get_namespace(namespace)
                         :get_group(group)
                         :get(event)
                         :remove_external_listener(self.listener_id);
        end,
        configure = function(self, config)
            self.event_emit_wrapper = config.event_emit_wrapper;
            self.event_receive_wrapper = config.event_receive_wrapper;
        end,
        event_namespace = namespace,
        event_group = group,
        event_name = event,
        listener_id = listener_id,
        event_id = ("%s.%s.%s"):format(namespace, group, event),
        event_emit_wrapper = nil,
        event_receive_wrapper = nil
    };
    local event_hook = setmetatable({callback = callback}, hook_mt);
    local receive_wrapper_caller = function(...)
        if hook_mt.event_receive_wrapper then
            return hook_mt.event_receive_wrapper(event_hook, ...);
        end
        return callback(...);
    end
    local lua_listener = obe.event.LuaEventListener(receive_wrapper_caller);
    Engine.Events:get_namespace(namespace)
        :get_group(group)
        :get(event)
        :add_external_listener(listener_id, lua_listener);
    return event_hook;
end

local function EventGroupHook(listener_id, namespace, group)
    local hook_mt = {
        __newindex = function(object, event, callback)
            if type(callback) == "function" then
                local mt = getmetatable(object);
                mt._storage[event] = EventHook(listener_id, namespace, group, event, callback);
                local event_config = merge_tables(mt.config.events["*"] or {}, mt.config.events[event] or {});
                getmetatable(mt._storage[event]):configure(event_config);
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
            if mt._storage[event] then
                return mt._storage[event];
            else
                if Engine.Events:get_namespace(namespace):get_group(group):contains(event) then
                    local event_mock = {callback=false};
                    setmetatable(event_mock, { -- TODO: merge mock and real EventHook
                            __call = function(self, ...)
                                local event_config = merge_tables(mt.config.events["*"] or {}, mt.config.events[event] or {});
                                if not event_config.allow_for_empty_calls then
                                    error(
                                        ("Callback for event %s.%s.%s is not implemented"):format(
                                            namespace, group, event
                                        )
                                    );
                                else
                                    if event_config.event_emit_wrapper then
                                        event_config.event_emit_wrapper(self, ...);
                                    end
                                end
                            end,
                            __index = function(object, flags)
                                assert(type(flags) == "table", "event flags must be a table");
                                return function(...)
                                    object(..., flags);
                                end
                            end,
                            event_namespace = namespace,
                            event_group = group,
                            event_name = event,
                            listener_id = listener_id,
                            event_id = ("%s.%s.%s"):format(namespace, group, event),
                        }
                    );
                    return event_mock;
                else
                    error(("Event %s.%s.%s does not exists"):format(namespace, group, event));
                end
            end
        end,
        clean = function(self)
            local group_exists = Engine.Events:get_namespace(namespace):does_group_exists(group);
            for event_name, event_hook in pairs(self._storage) do
                if group_exists then
                    getmetatable(event_hook):clean();
                end
                self._storage[event_name] = nil;
            end
        end,
        configure = function(self, config)
            self.config = config;
            self.config.events = self.config.events or {};
            for event_name, event_hook in pairs(self._storage) do
                local event_config = merge_tables(config.events["*"] or {}, config.events[event_name] or {});
                getmetatable(event_hook):configure(event_config);
            end
        end,
        __call = function(object)
            return Engine.Events:get_namespace(namespace):join_group(group);
        end,
        _storage = {},
        config = {
            events = {}
        },
        listener_id = listener_id,
        allow_for_empty_calls = false
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
                    if mt._storage[key] == nil then
                        mt._storage[key] = EventGroupHook(listener_id, namespace, key);
                    end
                    local event_group_config = merge_tables(mt.config.event_groups["*"] or {}, mt.config.event_groups[key] or {});
                    getmetatable(mt._storage[key]):configure(event_group_config);
                    return mt._storage[key];
                end
            end
            error("EventGroup " .. key .. " doesn't exists in namespace " .. namespace);
        end,
        clean = function(self)
            for event_group_name, group_hook in pairs(self._storage) do
                getmetatable(group_hook):clean();
            end
        end,
        configure = function(self, config)
            self.config = config;
            self.config.event_groups = self.config.event_groups or {};
            for event_group_name, event_group_hook in pairs(self._storage) do
                local event_group_config = merge_tables(config.event_groups["*"] or {}, config.event_groups[event_group_name] or {});
                getmetatable(event_group_hook):configure(event_group_config);
            end
        end,
        __call = function(object)
            return Engine.Events:join_namespace(namespace);
        end,
        _storage = {},
        config = {
            event_groups = {}
        },
        listener_id = listener_id,
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
