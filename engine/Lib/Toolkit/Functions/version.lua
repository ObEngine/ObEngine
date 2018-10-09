local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

return {
    Functions = {
        version = function()
            Color.print({
                { text = "ÖbEngine is in version ", color = Style.Default},
                { text = obe.version, color = Style.Workspace},
            }, 1);
        end,
        major = function()
            local major_version = string.split(string.sub(obe.version, 2),".")[1];
            Color.print({
                { text = "ÖbEngine's major version is ", color = Style.Default},
                { text = major_version, color = Style.Workspace},
            }, 1);
        end,
        minor = function()
            local minor_version = string.split(string.sub(obe.version, 2),".")[2];
            Color.print({
                { text = "ÖbEngine's minor version is ", color = Style.Default},
                { text = minor_version, color = Style.Workspace},
            }, 1);
        end,
        patch = function()
            local patch_version = string.split(string.sub(obe.version, 2),".")[3];
            Color.print({
                { text = "ÖbEngine's patch version is ", color = Style.Default},
                { text = patch_version, color = Style.Workspace},
            }, 1);
        end,
        commit = function()
            local commit_version = obe.commit;
            Color.print({
                { text = "ÖbEngine's commit version is ", color = Style.Default},
                { text = commit_version, color = Style.Workspace},
            }, 1);
        end,
        branch = function()
            local branch_version = obe.branch;
            Color.print({
                { text = "ÖbEngine's branch version is ", color = Style.Default},
                { text = branch_version, color = Style.Workspace},
            }, 1);
        end
    },
    Routes = {
        Route.Help("Get ÖbEngine's version");
        Route.Call("version");
        major = Route.Node {
            Route.Help("Get ÖbEngine's major version");
            Route.Call("major");
        },
        minor = Route.Node {
            Route.Help("Get ÖbEngine's minor version");
            Route.Call("minor");
        },
        patch = Route.Node {
            Route.Help("Get ÖbEngine's patch version");
            Route.Call("patch");
        },
        commit = Route.Node {
            Route.Help("Get ÖbEngine's commit version");
            Route.Call("commit");
        },
        branch = Route.Node {
            Route.Help("Get ÖbEngine's branch version");
            Route.Call("branch");
        }
    }
};