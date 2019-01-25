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

-- Local Triggers
Local = {};
Local__Meta = {
    __newindex = function(object, index, value)
        rawset(object, index, value);
        This:useLocalTrigger(index);
    end
}
setmetatable(Local, Local__Meta);

-- Global Triggers
Global = LuaCore.MakeTriggerGroupHook(This, "Global");

function LuaCore.InjectInitInjectionTable()
    for k, v in pairs(LuaCore.ObjectInitInjectionTable) do
        This:sendInitArg(k, v);
    end
end