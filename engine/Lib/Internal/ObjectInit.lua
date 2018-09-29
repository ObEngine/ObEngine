Local = {}; -- Local Events
Global = {}; -- External Global Events
Actions = {}; -- Actions Events

Object = {
    type = __OBJECT_TYPE;
    id = __OBJECT_ID;
};

LuaCore = {};
LuaCore.Lua_ReqList = {}; -- Require Parameters
LuaCore.FTCP = {}; -- Future Trigger Call Parameters
LuaCore.ObjectInitInjectionTable = {}; -- Used when Object is built from Editor Menu
LuaCore.TriggerList = {};
LuaCore.InternalMonitors = {};

function ObjectInit(argtable)
    --print("INITIALIZE : ", __OBJECT_TYPE, __OBJECT_ID);
    local argt = argtable or {};
    for k, v in pairs(argt) do
        This:sendInitArg(k, v);
        --print("Pushing Arg", k, v);
    end
    --print("Initialisation done");
    This:initialize();
    return Object;
end

Local__Meta = {
    __newindex = function(object, index, value)
        rawset(object, index, value);
        This:useLocalTrigger(index);
    end
}

setmetatable(Local, Local__Meta);

Global__Trigger__Meta = {
    __newindex = function(object, index, value)
        if type(value) == "function" then
            if object.triggerGroupId == "Keys" then
                LuaCore.InternalMonitors[index] = obe.Input.Monitors.Monitor(index);
            end
            This:useExternalTrigger("Global", object.triggerGroupId, index);
            local mt = getmetatable(object);
            mt.__storage[index] = value;
        elseif type(value) == "nil" then
            if object.triggerGroupId == "Keys" then
                LuaCore.InternalMonitors[index] = nil;
            end
            local mt = getmetatable(object);
            mt.__storage[index] = nil;
            This:removeExternalTrigger("Global", object.triggerGroupId, index);
        end
    end,
    __index = function(object, index)
        local mt = getmetatable(object);
        if mt.__storage[index] then
            return mt.__storage[index];
        else
            error("Global." .. object.triggerGroupId .. "." .. index .. " is not defined");
        end
    end,
    __storage = {}
};

Global__Meta = {
    __index = function(table, key)
        for _, v in pairs(TriggerDatabase:GetInstance():getAllTriggersGroupNames("Global")) do
            if v == key then
                if rawget(table, key) == nil then
                    rawset(table, key, { triggerGroupId = key });
                    setmetatable(rawget(table, key), Global__Trigger__Meta);
                end
                return rawget(table, key);
            end
        end
        error("Global Trigger " .. key .. " doesn't exists !");
    end
};

setmetatable(Global, Global__Meta);

function LuaCore.InjectInitInjectionTable()
    for k, v in pairs(LuaCore.ObjectInitInjectionTable) do
        This:sendInitArg(k, v);
    end
end

local ArgMirror = require('Lib/Internal/ArgMirror');
function LuaCore.IndexTriggerArgList(triggerName, funcToCall)
    LuaCore.TriggerList[triggerName].args = ArgMirror.GetArgs(funcToCall);
end

function LuaCore.FuncInjector(funcToCall, triggerRegisterName)
    if type(funcToCall) == "function" then
        if not LuaCore.TriggerList[triggerRegisterName].args then
            LuaCore.IndexTriggerArgList(triggerRegisterName, funcToCall);
        end
        local Lua_Func_ArgList = LuaCore.TriggerList[triggerRegisterName].args;
        local Lua_Func_CallArgs = {};
        for _, i in pairs(Lua_Func_ArgList) do
            if (LuaCore.FTCP[triggerRegisterName]) then
                table.insert(Lua_Func_CallArgs, LuaCore.FTCP[triggerRegisterName][i]);
            end
        end
        funcToCall(ArgMirror.Unpack(Lua_Func_CallArgs));
    end
end

function IsArgumentInRequireList(paramName)
    if (LuaCore.Lua_ReqList[paramName] ~= nil) then
        return true;
    else
        return false;
    end
end