Object = {
    type = __OBJECT_TYPE;
    id = __OBJECT_ID;
};

LuaCore.ObjectInitInjectionTable = {}; -- Used when Object is built from Editor Menu

function ObjectInit(argtable)
    local argt = argtable or {};
    for k, v in pairs(argt) do
        This:sendInitArg(k, v);
    end
    This:initialize();
    return Object;
end

__PRIVATE_TRIGGERS = LuaCore.MakeTriggerGroupHook(This, Private, function(namespace, group, id)
    if group == "Local" then
        return "Local." .. id;
    else
        return LuaCore.DefaultTriggerAlias(namespace, group, id);
    end
end);
Local = __PRIVATE_TRIGGERS["Local"];

-- Global Triggers
Global = LuaCore.MakeTriggerGroupHook(This, "Global");

function LuaCore.InjectInitInjectionTable()
    for k, v in pairs(LuaCore.ObjectInitInjectionTable) do
        This:sendInitArg(k, v);
    end
end