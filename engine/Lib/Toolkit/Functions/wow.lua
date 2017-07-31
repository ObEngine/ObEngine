local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");

local Functions = {};

Functions.mount = function(workspaceName)
end

Functions.create = function(workspaceName)
end

function Functions.list()
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with Workspaces");
        Route.Arg("create", {
            Route.Help("Creates a new Workspace");
            Route.Arg("lol", {
                Route.Call(function()
                    print("LOL CALLED");
                end);
            }),
            Route.Arg("mdr", {
                
            })
            --[[Route.Arg("workspaceName", Route.Types.Any, {
                --Route.Call("create");
                
            });]]--
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