__ENV_COUNT = 0;
__ENVIRONMENTS = {};

local inspect = require("Lib/StdLib/Inspect");

function CreateNewEnv()
    local ENV = env or {};
    if env == nil then
        ENV["__ENV_ID"] = __ENV_COUNT;
        setmetatable(ENV, {__index=_G});
        __ENVIRONMENTS[__ENV_COUNT] = ENV;
        __ENV_COUNT = __ENV_COUNT + 1;
    end
    return __ENV_COUNT - 1;
end

function ExecuteFileOnEnv(file, envIndex)
    print("Call file : ", file, "with index", envIndex);
    print(inspect(__ENVIRONMENTS[envIndex]));
    assert(loadfile(file, "t", __ENVIRONMENTS[envIndex]))();
    print("CALL RESULT : ", f, err);
    print("Call file : ", file, " is over");
end

function ExecuteStringOnEnv(code, envIndex)
    print("Call string : ", code, "with index", envIndex);
    --print(inspect(__ENVIRONMENTS[envIndex]));
    assert(load(code, nil, "t", __ENVIRONMENTS[envIndex]))();
    print("CALL RESULT : ", f, err);
    print("Call file : ", file, " is over");
end