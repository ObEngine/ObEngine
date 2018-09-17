Core = {}; -- Core Lib
Scenes = {};
LuaUtil = {};
pl = {};
Internal = {};

inspect = require("Lib/StdLib/Inspect");
pl.Date = require("Lib/StdLib/pl/Date");
pl.List = require("Lib/StdLib/pl/List");
pl.String = require("Lib/StdLib/pl/stringx");
pl.Table = require("Lib/StdLib/pl/tablex");
pl.Array2d = require("Lib/StdLib/pl/array2d");
pl.Comprehension = require("Lib/StdLib/pl/comprehension");
C = pl.Comprehension.new();
pl.Func = require("Lib/StdLib/pl/func");
pl.Input = require("Lib/StdLib/pl/input");
pl.Balanced = require("Lib/StdLib/pl/luabalanced");
pl.Map = require("Lib/StdLib/pl/Map");
pl.Operator = require("Lib/StdLib/pl/operator");
pl.Permute = require("Lib/StdLib/pl/permute");
pl.Seq = require("Lib/StdLib/pl/seq");
pl.Sip = require("Lib/StdLib/pl/sip");
pl.Strict = require("Lib/StdLib/pl/strict");
pl.StringIO = require("Lib/StdLib/pl/stringio");
pl.Set = require("Lib/StdLib/pl/Set");
pl.Text = require("Lib/StdLib/pl/text");
pl.Types = require("Lib/StdLib/pl/types");
pl.Utils = require("Lib/StdLib/pl/utils");

pl.String:import();
LuaUtil.Serpent = require("Lib/Internal/Serpent");

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

function Internal.CheckCoordinateTable(t)
    if type(a) == "table" then
        if a[1] and a[2] and type(a[1]) == "number" and type(a[2]) == "number" then
            return true;
        else 
            error("The table should contain two coordinates that are both numbers");
        end
    else
        error("When using {X}%v, {X} should be a table containing 2 coordinates : {10, 50}%v");
    end
end

Internal.ViewPercentageMT = {
    __mod = function(a, b)
        Internal.CheckCoordinateTable(a);
        return obe.UnitVector(a, b, obe.Units.ViewPercentage);
    end
};

Internal.ScenePixelsMT = {
    __pow = function(a, b)
        Internal.CheckCoordinateTable(a);
        return obe.UnitVector(a, b, obe.Units.ScenePixels);
    end
}

scene = {};
setmetatable(Internal.ScenePixelsMT);
view = {};
set