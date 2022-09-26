local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");

local function getLogLevels()
    return {
        "0 (trace)",
        "1 (debug)",
        "2 (info)",
        "3 (warn)",
        "4 (err)",
        "5 (critical)",
        "6 (off)"
    };
end

local function _loglevel_(level)
    local log_levels = getLogLevels();
    local level_num = tonumber(level);
    if level_num ~= nil and level_num >= 0 and level_num <= 6 then
        obe.debug.setLevel(level_num);
        Color.print({
            { text = "Log level set to ", color = Style.Default},
            { text = log_levels[level_num+1], color = Style.Argument},
        }, 1);
    else
        Color.print({
            {text = "Invalid argument ", color = Style.Error},
            {text = level, color = Style.Argument}
        }, 2);
    end
end

return {
    Commands.help("Change log level of ÖbEngine");
    level = Commands.arg {
        Commands.help("Log level");
        Commands.call(_loglevel_);
        Commands.autocomplete(getLogLevels);
    };
};