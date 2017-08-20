GetHook("TriggerDatabase");

Local = {}; -- Local Events
Global = {}; -- External Global Events
Actions = {}; -- Actions Events
Object = {};

Local__Meta = {
    __newindex = function(object, index, value)
        rawset(object, index, value);
        This:useLocalTrigger(index);
    end
}

setmetatable(Local, Local__Meta);

Global__Trigger__Meta = {
    __newindex = function(object, index, value)
        print("Register new Global Trigger", object.triggerGroupId, index);
        This:useExternalTrigger("Global", object.triggerGroupId, index);
        rawset(object, index, value);
    end
};

Global__Meta = {
    __index = function(table, key)
        for _, v in pairs(Hook.TriggerDatabase:GetInstance():getAllTriggersGroupNames("Global")) do
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

LuaCore.Lua_ReqList = {}; -- Require Parameters
LuaCore.FTCP = {}; -- Future Trigger Call Parameters
LuaCore.ObjectInitInjectionTable = {}; -- Used when Object is built from Editor Menu

inspect = require("Lib/StdLib/inspect");

function LuaCore.InjectInitInjectionTable()
    for k, v in pairs(LuaCore.ObjectInitInjectionTable) do
        This:sendInitArg(k, v);
    end
end

function LuaCore.FuncInjector(funcName, triggerRegisterName)
    --print("Injection : ", funcName, triggerRegisterName, triggerStackIndex, inspect(__FTCP__));
    local funcToCall = load("return " .. funcName)();
    if type(funcToCall) == "function" then
        local ArgMirror = require('Lib/Internal/ArgMirror');
        local Lua_Func_ArgList = ArgMirror.GetArgs(funcToCall);
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

function Object.Save()
    return {};
end