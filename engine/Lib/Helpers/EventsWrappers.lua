local function input_state_changed_event_receive_wrapper(event_hook, event)
    event_hook.callback {
        state = event.state,
        previous_state = event.previous_state,
        input_source = cast(event.input_source)
    }
end

local function wrap_events(event_namespace_hook)
    getmetatable(event_namespace_hook):configure {
        event_groups = {
            ["Keys"] = {
                events = {
                    ["*"] = {
                        event_receive_wrapper = input_state_changed_event_receive_wrapper,
                    }
                }
            }
        }
    };
end

return {
    wrap_events = wrap_events
}