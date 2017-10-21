Core = {}; -- Core Lib
LuaUtil = {};

inspect = require("Lib/StdLib/Inspect");

function LuaUtil.Exists(path)
    local pathToTest = load("return " .. path);
    noError, noNil = pcall(pathToTest);
    if not noError or noNil == nil then
        return false;
    end
    return true;
end

LuaUtil.libList = {};

function LuaUtil.IsLibLoaded(lib)
    for _, v in pairs(LuaUtil.libList) do
        if v == lib then
            return true;
        end
    end
    return false;
end