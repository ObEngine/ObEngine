local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local inspect = require("Lib/StdLib/Inspect");

function help()
    Color.print({
        { text = "Available commands : ", color = {140, 210, 80}}
    }, 1);
    for k, v in pairs(ToolkitFunctions) do
        local commandHelp = "";
        for khelp, vhelp in pairs(v.Routes) do
            if vhelp.type == "Help" then
                commandHelp = vhelp.help;
                break;
            end
        end
        Color.print({
            { text = "> ", color = {255, 255, 255}},
            { text = k, color = {255, 192, 0}},
            { text = " : ", color = {255, 255, 255}},
            { text = commandHelp, color = {230, 125, 50}}
        }, 2);
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