local DEFAULT_OBENGINE_PORT = 53000;

local function make_config_defaults(config)
    config.address = config.address or "127.0.0.1";
    if config.call_local == nil then
        config.call_local = true;
    end
    config.spec = config.spec or vili.from_lua({});
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
        if config.call_local and event_hook.callback then
            return event_hook.callback(message);
        end
    end
end

local function event_receive_wrapper(event_hook, message)
    local as_lua_data = vili.to_lua(message.data);
    return event_hook.callback(as_lua_data, message);
end

local function make_event_handler(game_object, network_event_manager)
    game_object:listen(
        "Event.Game.Update",
        function(evt)
            network_event_manager:handle_events();
        end,
        ("networkeventlistener.%s"):format(network_event_manager:get_event_namespace():get_name())
    );
end

local function make_network_event_manager(game_object, config)
    config = make_config_defaults(config or {});
    game_object.components.NetworkManager = obe.network.NetworkEventManager(Engine.Events, config.namespace, config.spec);
    make_event_handler(game_object, game_object.components.NetworkManager);
    return game_object.components.NetworkManager;
end

local function make_network_event_namespace_hook(game_object, config)
    local event_namespace_hook = game_object:listen(config.namespace);
    local event_emit_wrapper = make_event_emit_wrapper(game_object.components.NetworkManager, config);
    getmetatable(event_namespace_hook):configure {
        event_groups = {
            ["*"] = {
                events = {
                    ["*"] = {
                        event_emit_wrapper = event_emit_wrapper,
                        event_receive_wrapper = event_receive_wrapper,
                        allow_for_empty_calls = true
                    }
                }
            }
        }
    };
    return event_namespace_hook;
end

local function host(game_object, config)
    local network_event_manager = make_network_event_manager(game_object, config);
    network_event_manager:host(config.port);
    return make_network_event_namespace_hook(game_object, config);
end

local function connect(game_object, config)
    local network_event_manager = make_network_event_manager(game_object, config);
    network_event_manager:connect(config.address, config.port);
    return make_network_event_namespace_hook(game_object, config);
end

return {
    host = host,
    connect = connect
}