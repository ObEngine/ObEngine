Core = {}; -- Core Lib
Core.ImportedLibs = {} -- List of Imported Lib names
Hook = {}; -- Core Objects
Game = {};
Editor = {};

function Import(lib)
    CPP_Import(This, lib);
end

function GetHook(hook)
    CPP_Hook(This, hook);
end

function Game.Start()

end

function Editor.Start()

end