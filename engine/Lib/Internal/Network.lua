local DEFAULT_OBENGINE_PORT = 53000;

local function make_config_defaults(config)
    config.address = config.address or "127.0.0.1";
    if config.call_local == nil then
        config.call_local = true;
    end
    config.events = config.events or {};
    config.namespace = config.namespace or "Network";
    config.port = config.port or DEFAULT_OBENGINE_PORT;
    config.reliable = config.reliable or true;

    return config;
end

local function make_event_emit_wrapper(network_manager, config)
    return function(event_hook, message)
        local event_hook_mt = getmetatable(event_hook);
        local serialized_msg = vili.from_lua(message);
        network_manager:emit(event_hook_mt.event_group, event_hook_mt.event_name, serialized_msg);
        if config.call_local then
            return event_hook.callback(message);
        end
    end
end

local function event_receive_wrapper(event_hook, message)
    local as_lua_data = vili.to_lua(message);
    return event_hook.callback(as_lua_data);
end

local function host(game_object, config)
    config = make_config_defaults(config or {});
    game_object.components.NetworkManager = obe.network.NetworkEventManager(Engine.Events, config.namespace);
    game_object.components.NetworkManager:host(config.port);
    return game_object:listen(config.namespace);
end

local function connect(game_object, config)
    config = make_config_defaults(config or {});
    game_object.components.NetworkManager = obe.network.NetworkEventManager(Engine.Events, config.namespace);
    game_object.components.NetworkManager:connect(config.address, config.port);
    local event_namespace_hook = game_object:listen(config.namespace);
    local event_emit_wrapper = make_event_emit_wrapper(game_object.components.NetworkManager, config);
    event_namespace_hook:set_event_emit_wrapper(event_emit_wrapper);
    event_namespace_hook:set_event_receive_wrapper(event_receive_wrapper);
    return event_namespace_hook;
end

return {
    host = host,
    connect = connect
}