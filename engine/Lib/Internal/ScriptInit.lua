Core = {}; -- Core Lib
LuaUtil = {};

inspect = require("Lib/StdLib/Inspect");
string = require("Lib/StdLib/string");

function LuaUtil.Exists(path)
    local pathToTest = load("return " .. path);
    noError, noNil = pcall(pathToTest);
    if not noError or noNil == nil then
        return false;
    end
    return true;
end

function GetHook(hook)
    CPP_Hook(This, hook);
end