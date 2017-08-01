local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

function help()
    Color.print({
        { text = "Available commands : ", color = Style.Execute}
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
            { text = "> ", color = Style.Default},
            { text = k, color = Style.Command},
            { text = " : ", color = Style.Default},
            { text = commandHelp, color = Style.Help}
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
    }
};