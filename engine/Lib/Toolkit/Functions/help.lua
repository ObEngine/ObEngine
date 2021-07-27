local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");

local function _help_()
    Color.print({
        { text = "Available commands : ", color = Style.Execute}
    }, 1);
    for commandName, command in pairs(ToolkitFunctions) do
        local commandHelp = "";
        for khelp, vhelp in pairs(command) do
            if vhelp.type == "Help" then
                commandHelp = vhelp.help;
                break;
            end
        end
        Color.print({
            { text = "> ", color = Style.Default},
            { text = commandName, color = Style.Command},
            { text = " : ", color = Style.Default},
            { text = commandHelp, color = Style.Help}
        }, 2);
    end
end

return {
    Commands.call(_help_);
    Commands.help("Displays the help of all commands");
};