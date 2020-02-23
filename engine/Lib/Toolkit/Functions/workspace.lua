local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

local Functions = {};

function getWorkspaceList()
    local parser = Vili.ViliParser.new();
    parser:parseFile("Workspace/Workspaces.vili");
    local allWorkspaces = {};
    for _, key in pairs(parser:root():getAll(Vili.NodeType.ComplexNode)) do 
        table.insert(allWorkspaces, key:getId());
    end
    return allWorkspaces;
end

function getNonIndexedWorkspaces()
    local allWorkspaces = obe.Path("Workspace"):DirectoryListLoader();
    local allIndexedWorkspaces = getWorkspaceList();
    local returnWorkspaces = {};
    for _, key in pairs(allWorkspaces) do
        if not obe.Array.contains(key, allIndexedWorkspaces) then
            table.insert(returnWorkspaces, key);
        end
    end
    return returnWorkspaces;
end

Functions.mount = function(workspaceName)
    local parser = Vili.ViliParser.new();
    parser:parseFile("Workspace/Workspaces.vili");
    Color.print({
        { text = "Mounting Workspace '", color = Style.Execute},
        { text = workspaceName, color = Style.Workspace},
        { text = "' ...", color = Style.Execute},
    }, 1);
    if (parser:root():contains(Vili.NodeType.ComplexNode, workspaceName)) then
        obe.Filesystem.copy("Workspace/" .. workspaceName .. "/Mount.vili", "Mount.vili");
        Color.print({
            { text = "Workspace '", color = Style.Success},
            { text = workspaceName, color = Style.Workspace},
            { text = "' has  been successfully mounted !", color = Style.Success},
        }, 2);
        obe.MountPaths();
    else
        Color.print({
            { text = "Workspace '", color = Style.Error},
            { text = workspaceName, color = Style.Workspace},
            { text = "' does not exists", color = Style.Error}
        }, 2);
    end
end

Functions.create = function(workspaceName)
    local parser = Vili.ViliParser.new();
    parser:parseFile("Workspace/Workspaces.vili");
    Color.print({
        { text = "Creating Workspace '", color = Style.Execute},
        { text = workspaceName, color = Style.Workspace},
        { text = "' ...", color = Style.Execute},
    }, 1);
    if (parser:root():contains(Vili.NodeType.ComplexNode, workspaceName)) then
        Color.print({
            { text = "Workspace '", color = Style.Error},
            { text = workspaceName, color = Style.Workspace},
            { text = "' already exists", color = Style.Error}
        }, 2);
    else
        os.execute(("mkdir Workspace/" .. workspaceName):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data"):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/Maps"):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/GameObjects"):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Data/GameScripts"):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites"):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites/GameObjects"):gsub("/", obe.Filesystem.separator()));
        os.execute(("mkdir Workspace/" .. workspaceName .. "/Sprites/Scenes"):gsub("/", obe.Filesystem.separator()));
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
            { text = "Workspace '", color = Style.Success},
            { text = workspaceName, color = Style.Workspace},
            { text = "' has  been successfully created !", color = Style.Success},
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

function Functions.index(workspaceName)
    if obe.Array.contains(workspaceName, getNonIndexedWorkspaces()) then
        local parser = Vili.ViliParser.new();
        parser:parseFile("Workspace/Workspaces.vili");
        parser:root():createComplexNode(workspaceName);
        parser:root():at(workspaceName):createDataNode("path", "Workspace/" .. workspaceName);
        parser:writeFile("Workspace/Workspaces.vili");
        Color.print({
            { text = "Workspace '", color = Style.Success},
            { text = workspaceName, color = Style.Workspace},
            { text = "' has  been successfully indexed !", color = Style.Success},
        }, 2);
    else
        Color.print({
            { text = "Workspace '", color = Style.Error},
            { text = workspaceName, color = Style.Workspace},
            { text = "' is already indexed", color = Style.Error}
        }, 2);
    end
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with Workspaces");
        create = Route.Node {
            Route.Help("Creates a new Workspace");
            workspaceName = Route.Arg {
                Route.Help("Name of the new Workspace to create");
                Route.Call("create");
            };
        },
        mount = Route.Node {
            Route.Help("Mounts a Workspace");
            workspaceName = Route.Arg {
                Route.Call("mount");
                Route.Help("Name of the Workspace you want to mount");
                Route.Autocomplete(getWorkspaceList);
            };
        };
        index = Route.Node {
            Route.Help("Indexes an existing Workspace");
            workspaceName = Route.Arg {
                Route.Call("index");
                Route.Help("Name of the Workspace you want to index");
                Route.Autocomplete(getNonIndexedWorkspaces);
            };
        };
        list = Route.Node {
            Route.Help("Lists all existing Workspaces");
            Route.Call("list");
        };
    }
};