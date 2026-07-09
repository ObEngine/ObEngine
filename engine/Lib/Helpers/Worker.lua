function obe.script.Worker(callable, config)
    local worker_state = obe.script.LuaState();
    local worker_config = config or {
        bindings = {"*"},
        features = {
            logger = false,
            ordered = true,
            try = true,
            class = true,
            debugger = false,
            inspect = false,
            stringx = true
        }
    }
    worker_state
end