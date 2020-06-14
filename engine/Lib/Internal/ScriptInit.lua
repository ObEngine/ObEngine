Core = {}; -- Core Lib
Scenes = {};
pl = {};
Debug = {};

inspect = require("Lib/Extlibs/Inspect");
dbg = require("Lib/Extlibs/debugger");
pl.List = require("Lib/Extlibs/pl/List");
pl.String = require("Lib/Extlibs/pl/stringx");

pl.String:import();

function LuaCore.Exists(path)
    local pathToTest = load("return " .. path);
    local noError, noNil = pcall(pathToTest);
    if not noError or noNil == nil then
        return false;
    end
    return true;
end

LuaCore.libList = {};

function LuaCore.IsLibLoaded(lib)
    for _, v in pairs(LuaCore.libList) do
        if v == lib then
            return true;
        end
    end
    return false;
end

