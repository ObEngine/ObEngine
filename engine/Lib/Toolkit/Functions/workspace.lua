local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

local Functions = {};

function getWorkspaceList()
    local parser = Vili.ViliParser.new();
    parser:parseFile("Workspace/Workspaces.vili");
    local allWorkspaces = {};
    for _, key in pairs(parser:root():getAll(Vili.NodeType.ComplexNode)) do 
        table.insert(allWorkspaces, key);
    end
    return allWorkspaces;
end

Functions.mount = function(workspaceName)
    local parser = Vili.ViliParser.new();
    parser:parseFile("Workspace/Workspaces.vili");
    Color.print({
        { text = "Mounting Workspace <", color = Style.Execute},
        { text = workspaceName, color = Style.Workspace},
        { text = "> ...", color = Style.Execute},
    }, 1);
    if (parser:root():contains(Vili.NodeType.ComplexNode, workspaceName)) then
        Core.Utils.File.copy("Workspace/" .. workspaceName .. "/Mount.vili", "Mount.vili");
        Color.print({
            { text = "Workspace <", color = Style.Success},
            { text = workspaceName, color = Style.Workspace},
            { text = "> has  been successfully mounted !", color = Style.Success},
        }, 2);
        Core.System.MountPaths();
    else
        Color.print({
            { text = "Workspace <", color = Style.Error},
            { text = workspaceName, color = Style.Workspace},
            { text = "> does not exists", color = Style.Error}
        }, 2);
    end
end

Functions.create = function(workspaceName)
    local parser = Vili.ViliParser.new();
    parser:parseFile("Workspace/Workspaces.vili");
    Color.print({
        { text = "Creating Workspace <", color = Style.Execute},
        { text = workspaceName, color = Style.Workspace},
        { text = "> ...", color = Style.Execute},
    }, 1);
    if (parser:root():contains(Vili.NodeType.ComplexNode, workspaceName)) then
        Color.print({
            { text = "Workspace <", color = Style.Error},
            { text = workspaceName, color = Style.Workspace},
            { text = "> already exists", color = Style.Error}
        }, 2);
    else
        os.execute(("mkdir Workspace/" .. workspaceName):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/Maps"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/GameObjects"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/GameScripts"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites/GameObjects"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites/LevelSprites"):gsub("/", Core.Utils.File.separator()));
        parser:root():createComplexNode(workspaceName);
        parser:root():at(workspaceName):createDataNode("path", "Workspace/" .. workspaceName);
        parser:writeFile("Workspace/Workspaces.vili", true);
        local defaultMount = io.open("Workspace/" .. workspaceName .. "/Mount.vili", "w")

        defaultMount:write("Include(Obe);\n\n");
        defaultMount:write("Mount:\n");
        defaultMount:write("    " .. workspaceName .. ":" .. "Workspace(\"" .. workspaceName .. "\", 1)\n");
        defaultMount:write("    Root:Path(\"\", 0)");
        defaultMount:close()

        Color.print({
            { text = "Workspace <", color = Style.Success},
            { text = workspaceName, color = Style.Workspace},
            { text = "> has  been successfully created !", color = Style.Success},
        }, 2);
    end
end

function Functions.list()
    local allWorkspaces = getWorkspaceList();
    Color.print({
        { text = "All Registered Workspaces : ", color = Style.Execute}
    }, 1);
    for _, key in pairs(allWorkspaces) do 
        Color.print({
            { text = "- Workspace : ", color = Style.Default},
            { text = key, color = Style.Workspace}
        }, 2);
    end
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with Workspaces");
        Route.Node("create", {
            Route.Help("Creates a new Workspace");
            Route.Arg("workspaceName", {
                Route.Help("Name of the new Workspace to create");
                Route.Call("create");
            });
        }),
        Route.Node("mount", {
            Route.Help("Mounts a Workspace");
            Route.Arg("workspaceName", {
                Route.Call("mount");
                Route.Help("Name of the Workspace you want to mount");
                Route.Autocomplete(function(start)
                    return getWorkspaceList();
                end)
            });
        }),
        Route.Node("list", {
            Route.Help("Lists all exsiting Workspaces");
            Route.Call("list");
        })
    }
};