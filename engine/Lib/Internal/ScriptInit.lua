Core = {}; -- Core Lib
Core.ImportedLibs = {} -- List of Imported Lib names
Hook = {}; -- Core Objects
LuaCore = {};

function LuaCore.Exists(path)
    local pathToTest = load("return " .. path);
    noError, noNil = pcall(pathToTest);
    if not noError or noNil == nil then
        return false;
    end
    return true;
end

function Import(lib)
    CPP_Import(This, lib);
end

function GetHook(hook)
    CPP_Hook(This, hook);
end