local function EventHook(listener_id, namespace, group, event, callback)
    local hook_mt = {
        __call = function(object, ...)
            local mt = getmetatable(object);
            if mt.event_emit_wrapper then
                return mt.event_emit_wrapper(object, ...);
            end
            return object.callback(...);
        end,
        clean = function(self)
            Engine.Events:get_namespace(namespace)
                         :get_group(group)
                         :get(event)
                         :remove_external_listener(self.listener_id);
        end,
        set_event_emit_wrapper = function(self, wrapper)
            self.event_emit_wrapper = wrapper;
        end,
        set_event_receive_wrapper = function(self, wrapper)
            self.event_receive_wrapper = wrapper;
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
        clean = function(self)
            local group_exists = Engine.Events:get_namespace(namespace):does_group_exists(group);
            for event_name, event_hook in pairs(self._storage) do
                if group_exists then
                    getmetatable(event_hook):clean();
                end
                self._storage[event_name] = nil;
            end
        end,
        set_event_emit_wrapper = function(self, wrapper)
            self.event_emit_wrapper = wrapper;
            for event_group_name, event_hook in pairs(self._storage) do
                getmetatable(event_hook):set_event_emit_wrapper(self.event_emit_wrapper);
            end
        end,
        set_event_receive_wrapper = function(self, wrapper)
            self.event_receive_wrapper = wrapper;
            for event_name, event_hook in pairs(self._storage) do
                getmetatable(event_hook):set_event_receive_wrapper(self.event_receive_wrapper);
            end
        end,
        __call = function(object)
            return Engine.Events:get_namespace(namespace):join_group(group);
        end,
        _storage = {},
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
                    if mt._storage[key] == nil then
                        mt._storage[key] = EventGroupHook(listener_id, namespace, key);
                    end
                    getmetatable(mt._storage[key]):set_event_emit_wrapper(mt.event_emit_wrapper);
                    getmetatable(mt._storage[key]):set_event_receive_wrapper(mt.event_receive_wrapper);
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
        set_event_emit_wrapper = function(self, wrapper)
            self.event_emit_wrapper = wrapper;
            for event_group_name, event_group_hook in pairs(self._storage) do
                getmetatable(event_group_hook):set_event_emit_wrapper(self.event_emit_wrapper);
            end
        end,
        set_event_receive_wrapper = function(self, wrapper)
            self.event_receive_wrapper = wrapper;
            for event_group_name, event_group_hook in pairs(self._storage) do
                getmetatable(event_group_hook):set_event_receive_wrapper(self.event_receive_wrapper);
            end
        end,
        __call = function(object)
            return Engine.Events:join_namespace(namespace);
        end,
        _storage = {},
        listener_id = listener_id,
        event_emit_wrapper = nil,
        event_receive_wrapper = nil
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
