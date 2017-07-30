local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");

function help()
    Color.print({ text = "Available commands : ", color = {0, 255, 0}}, 1);
    for k, v in pairs(ToolkitFunctions) do
        Color.print({ text = "> " .. k, color = {0, 255, 255}}, 2);
    end
end

return {
    Functions = {
        help = help
    },
    Routes = {
        Route.Call("help");
        Route.Help("Well, it.. helps you ?");
        Route.Arg("command", Route.Types.Any, {
            Route.Help("Gets the help for a specific command");
        });
    }
};