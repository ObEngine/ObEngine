Local = {}; -- Local Events

Local__Meta = {
    __newindex = function(object, index, value)
        rawset(object, index, value);
        print("Using Trigger : " .. index);
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
    --print("Start Injection : ", funcName, triggerRegisterName, triggerStackIndex);
    local funcToCall = load("return " .. funcName)();
    --print("Call RunFail")
    --funcToCall(1000, 10001);
    --print(funcToCall, type(funcToCall));
    if type(funcToCall) == "function" then
        --print("Function found, starting injection")
        local ArgMirror = require('Lib/Internal/ArgMirror');
        local Lua_Func_ArgList = ArgMirror.GetArgs(funcToCall);
        --print("ArgList : ", inspect(Lua_Func_ArgList))
        local Lua_Func_CallArgs = {};
        for _, i in pairs(Lua_Func_ArgList) do
            --print(i);
            --[[print("SUBINSPECT", inspect(__FTCP__[triggerRegisterName]))
            print("SUBSUBINSPECT", inspect(__FTCP__[triggerRegisterName][triggerStackIndex]))
            print("ARGFOUDN ? ", inspect(__FTCP__[triggerRegisterName][triggerStackIndex][i]))--]]
            table.insert(Lua_Func_CallArgs, __FTCP__[triggerRegisterName][triggerStackIndex][i]);
        end
        --print("CALLARGS", inspect(Lua_Func_CallArgs))
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
    --print("============> " .. yolo, inspect(__FTCP__));
    return {};
end