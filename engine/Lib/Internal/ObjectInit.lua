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

__PRIVATE_TRIGGERS = LuaCore.MakeTriggerGroupHook(This, Private);
Local = __PRIVATE_TRIGGERS["Local"];
getmetatable(Local).__alias_function = function(namespace, group, id)
    return "Local." .. id;
end

-- Global Triggers
Event = LuaCore.MakeTriggerGroupHook(This, "Event");

function LuaCore.InjectInitInjectionTable()
    for k, v in pairs(LuaCore.ObjectInitInjectionTable) do
        This:sendInitArg(k, v);
    end
end