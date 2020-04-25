LuaCore.TriggerArgTable = {}; -- Future Trigger Call Parameters

function LuaCore.DefaultTriggerAlias(namespace, group, id)
    return namespace .. "." .. group .. "." .. id;
end

function LuaCore.MakeTriggerGroupSubTable(GameObject, namespace)
    return {
        __alias_function = LuaCore.DefaultTriggerAlias,
        __newindex = function(object, index, value)
            if type(value) == "function" then
                local mt = getmetatable(object);
                local alias = mt.__alias_function(namespace,
                                                  object.triggerGroupId, index);
                GameObject:useTrigger(namespace, object.triggerGroupId, index,
                                      alias);
                mt.__storage[index] = value;
            elseif type(value) == "nil" then
                local mt = getmetatable(object);
                mt.__storage[index] = nil;
                GameObject:removeTrigger(namespace, object.triggerGroupId, index);
            end
        end,
        __index = function(object, index)
            local mt = getmetatable(object);
            if mt.__storage[index] then
                return mt.__storage[index];
            else
                error(
                    namespace .. "." .. object.triggerGroupId .. "." .. index ..
                        " is not defined");
            end
        end,
        __storage = {}
    };
end

function LuaCore.MakeTriggerGroupHook(GameObject, namespace)
    local hook_mt = {
        __index = function(table, key)
            for _, v in pairs(
                            Engine.Triggers:getAllTriggersGroupNames(namespace)) do
                if v == key then
                    if rawget(table, key) == nil then
                        rawset(table, key, {triggerGroupId = key});
                        setmetatable(rawget(table, key),
                                     LuaCore.MakeTriggerGroupSubTable(
                                         GameObject, namespace));
                    end
                    return rawget(table, key);
                end
            end
            error("Trigger " .. key .. " doesn't exists in namespace " ..
                      namespace);
        end
    };
    local hook_table = {};
    setmetatable(hook_table, hook_mt);
    return hook_table;
end

local ArgMirror = require('Lib/Internal/ArgMirror');
function LuaCore.IndexTriggerArgList(env, triggerName, funcToCall)
    env["__TRIGGERS"][triggerName].args = ArgMirror.GetArgs(funcToCall);
end

function LuaCore.FuncInjector(env, funcToCall, triggerRegisterName)
    if type(funcToCall) == "function" then
        if not env["__TRIGGERS"][triggerRegisterName].args then
            LuaCore.IndexTriggerArgList(env, triggerRegisterName, funcToCall);
        end
        local Lua_Func_ArgList = env["__TRIGGERS"][triggerRegisterName].args;
        local Lua_Func_CallArgs = {};
        for _, i in pairs(Lua_Func_ArgList) do
            if (LuaCore.TriggerArgTable[triggerRegisterName][i]) then
                table.insert(Lua_Func_CallArgs,
                             LuaCore.TriggerArgTable[triggerRegisterName][i]);
            else
                table.insert(Lua_Func_CallArgs, __nil_table);
            end
        end
        funcToCall(ArgMirror.Unpack(Lua_Func_CallArgs));
    end
end

function LuaCore.MakeCallback(trigger, callback, callbackName)
    local ArgMirror = require('Lib/Internal/ArgMirror');
    local argTable = "__TRIGGERS[\"%s\"][\"ArgTable\"][\"%s\"]"
    local argStringList = {};

    local argList = ArgMirror.GetArgs(callback);
    for k, v in pairs(argList) do
        table.insert(argStringList, argTable:format(trigger, v));
    end
    local funcCall = callbackName .. "(" .. table.concat(argStringList, ", ") ..
                         ")";

    local func, err = load("return function() " .. funcCall .. " end",
                           callbackName, "t", _ENV);
    if func then
        local ok, callbackGetter = pcall(func);
        if ok then
            return callbackGetter;
        else
            print("MakeCallback Execution error: ", callbackGetter);
        end
    else
        print("MakeCallback Compilation error:", err);
    end
end
