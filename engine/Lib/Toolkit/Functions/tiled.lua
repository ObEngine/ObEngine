local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");
local ordered = require("Lib/StdLib/Ordered");

local Functions = {};

local fs = obe.utils.file;

function Functions.import(path)
    local absolute_path_lookup = obe.system.Path(path):find();
    if not absolute_path_lookup:success() then
        Color.print({
            { text = "Invalid Tiled map path '", color = Style.Error},
            { text = path, color = Style.Argument},
            { text = "'", color = Style.Error},
        });
        return;
    end
    local absolute_path = absolute_path_lookup:path();
    local tilemap_path = obe.system.Path(absolute_path);

end

return {
    Commands.help("Tiled related commands");
    import = Commands.command {
        path = Commands.arg {
            Commands.call(Functions.import);
        }
    }
};