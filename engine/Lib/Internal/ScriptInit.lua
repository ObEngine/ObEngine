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

function count_all(f)
	local seen = {}
	local count_table
	count_table = function(t)
		if seen[t] then return end
		f(t)
		seen[t] = true
        for k,v in pairs(t) do
            print("Found", k, v, getmetatable(v));
			if type(v) == "table" then
				count_table(v)
			elseif type(v) == "userdata" then
				f(v)
			end
		end
	end
	count_table(_G)
end

function type_name(o)
    return tostring(o);
end

function type_count()
	local counts = {}
	local enumerate = function (o)
		local t = type_name(o)
		counts[t] = (counts[t] or 0) + 1
	end
	count_all(enumerate)
	return counts
end

print(inspect(type_count()));
-- dbg();