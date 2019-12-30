Core = {}; -- Core Lib
Scenes = {};
pl = {};
Debug = {};

inspect = require("Lib/Extlibs/Inspect");
pl.Date = require("Lib/Extlibs/pl/Date");
pl.List = require("Lib/Extlibs/pl/List");
pl.String = require("Lib/Extlibs/pl/stringx");
pl.Table = require("Lib/Extlibs/pl/tablex");
pl.Array2d = require("Lib/Extlibs/pl/array2d");
pl.Comprehension = require("Lib/Extlibs/pl/comprehension");
C = pl.Comprehension.new();
pl.Func = require("Lib/Extlibs/pl/func");
pl.Input = require("Lib/Extlibs/pl/input");
pl.Balanced = require("Lib/Extlibs/pl/luabalanced");
pl.Map = require("Lib/Extlibs/pl/Map");
pl.Operator = require("Lib/Extlibs/pl/operator");
pl.Permute = require("Lib/Extlibs/pl/permute");
pl.Seq = require("Lib/Extlibs/pl/seq");
pl.Sip = require("Lib/Extlibs/pl/sip");
pl.Strict = require("Lib/Extlibs/pl/strict");
pl.StringIO = require("Lib/Extlibs/pl/stringio");
pl.Set = require("Lib/Extlibs/pl/Set");
pl.Text = require("Lib/Extlibs/pl/text");
pl.Types = require("Lib/Extlibs/pl/types");
pl.Utils = require("Lib/Extlibs/pl/utils");

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