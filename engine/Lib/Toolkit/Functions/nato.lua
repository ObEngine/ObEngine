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
        Route.Arg("mount", Route.Types.Any, {
        })
    }
};