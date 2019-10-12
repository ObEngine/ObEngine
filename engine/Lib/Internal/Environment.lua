__ENV_COUNT = 0; -- Remove local for weird bug
__ENVIRONMENTS = {};

function LuaCore.CreateNewEnv(env)
    local ENV = env or {};
    if env == nil then
        ENV["__ENV_ID"] = __ENV_COUNT;
        ENV["__TRIGGERS"] = {};
        setmetatable(ENV, {__index=_G});
        __ENVIRONMENTS[__ENV_COUNT] = ENV;
        __ENV_COUNT = __ENV_COUNT + 1;
    end
    return __ENV_COUNT - 1;
end

function LuaCore.ExecuteFileOnEnv(file, envIndex)
    assert(loadfile(file, "t", __ENVIRONMENTS[envIndex]))();
    --print("CALL RESULT : ", f, err);
    --print("Call file : ", file, " is over");
end

function LuaCore.ExecuteStringOnEnv(code, envIndex)
    assert(load(code, nil, "t", __ENVIRONMENTS[envIndex]))();
end

function LuaCore.EnvFuncInjector(env, triggerName)
    _ENV = __ENVIRONMENTS[env];
    local func = _ENV["__TRIGGERS"][triggerName].callback;
    if type(func) == "string" then
        _ENV["__TRIGGERS"][triggerName].callback = assert(load("return " .. func, nil, "t", _ENV))();
        func = _ENV["__TRIGGERS"][triggerName].callback;
    end
    LuaCore.FuncInjector(_ENV, func, triggerName);
    _ENV = _G;
end