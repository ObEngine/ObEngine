local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");

local Functions = {};

Functions.mount = function(workspaceName)
    local parser = Core.Vili.DataParser.new();
    parser:parseFile("Workspace/Workspaces.vili", true);
    if (parser:root():contains(Core.Vili.AttributeType.ComplexAttribute, workspaceName)) then
        Core.Filesystem.copy("Workspace/" .. workspaceName .. "/Mount.vili", "Mount.vili");
        Color.print({ text = "Workspace '" .. workspaceName .. "' has  been successfully mounted !", color = {0, 255, 0}}, 1);
        Core.Path.MountPaths();
    else
        Color.print({ text = "Workspace '" .. workspaceName .. "' does not exists", color = {255, 0, 0}}, 1);
    end
end

Functions.create = function(workspaceName)
    local parser = Core.Vili.DataParser.new();
    parser:parseFile("Workspace/Workspaces.vili", true);
    os.execute(("mkdir Workspace/" .. workspaceName):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Data"):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/Maps"):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/GameObjects"):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/GameScripts"):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites"):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites/GameObjects"):gsub("/", Core.Filesystem.separator()));
    os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites/LevelSprites"):gsub("/", Core.Filesystem.separator()));
    parser:root():createComplexAttribute(workspaceName);
    parser:root():at(workspaceName):createBaseAttribute("path", "Workspace/" .. workspaceName);
    parser:writeFile("Workspace/Workspaces.vili", true);
    local defaultMount = io.open("Workspace/" .. workspaceName .. "/Mount.vili", "w")

    defaultMount:write("Include(Obe);\n\n");
    defaultMount:write("Mount:\n");
    defaultMount:write("    " .. workspaceName .. ":" .. "Workspace(\"" .. workspaceName .. "\", 1)\n");
    defaultMount:write("    Root:Path(\"\", 0)");
    defaultMount:close()

    Color.print({ text = "Workspace '" .. workspaceName .. "' has been successfully created", color = {0, 255, 0}}, 1);
end

function Functions.list()
    local parser = Core.Vili.DataParser.new();
    parser:parseFile("Workspace/Workspaces.vili", false);
    for _, key in pairs(parser:root():getAll(Core.Vili.AttributeType.ComplexAttribute)) do 
        Color.print({ text = "- Workspace : " .. key, color = {0, 255, 255}}, 2);
    end
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with Workspaces");
        Route.Arg("create", {
            Route.Help("Creates a new Workspace");
            Route.Arg("workspaceName", Route.Types.Any, {
                Route.Call("create");
            });
        }),
        Route.Arg("mount", {
            Route.Help("Mounts a Workspace");
            Route.Arg("workspaceName", Route.Types.Any, {
                Route.Call("mount");
            });
        }),
        Route.Arg("list", {
            Route.Help("Lists all exsiting Workspaces");
            Route.Call("list");
        })
    }
};