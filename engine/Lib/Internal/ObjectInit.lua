Local = {}; -- Local Events

Local__Meta = {
    __newindex = function(object, index, value)
        rawset(object, index, value);
        This:useLocalTrigger(index);
    end
}

setmetatable(Local, Local__Meta);

Global = {}; -- Global Events
LuaCore = {};
LuaCore.Lua_ReqList = {}; -- Require Parameters
__FTCP__ = {}; -- Future Trigger Call Parameters

function Require(param)
    if (LuaCore.Lua_ReqList[param] ~= nil) then
        return LuaCore.Lua_ReqList[param];
    else
        error("Can't find requirement : " .. param);
    end
end

inspect = require("Lib/StdLib/inspect");


function LuaCore.FuncInjector(funcName, triggerRegisterName, triggerStackIndex)
    print("Injection : ", funcName, triggerRegisterName, triggerStackIndex, inspect(__FTCP__));
    local funcToCall = load("return " .. funcName)();
    if type(funcToCall) == "function" then
        local ArgMirror = require('Lib/Internal/ArgMirror');
        local Lua_Func_ArgList = ArgMirror.GetArgs(funcToCall);
        local Lua_Func_CallArgs = {};
        for _, i in pairs(Lua_Func_ArgList) do
            if (__FTCP__[triggerRegisterName][triggerStackIndex]) then
                table.insert(Lua_Func_CallArgs, __FTCP__[triggerRegisterName][triggerStackIndex][i]);
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

-- Local.Init
-- Local.Update
-- Local.Collide
-- Local.Query
-- Local.Click
-- Local.Delete
-- Local.Save

function Local.Save(yolo)
    return {};
end