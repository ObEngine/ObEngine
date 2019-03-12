local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

function getLogLevels()
    local logLevels = {
        "0 (trace)",
        "1 (debug)",
        "2 (info)",
        "3 (warn)",
        "4 (err)",
        "5 (critical)",
        "6 (off)"
    };
    return logLevels;

end
return {
    Functions = {
        logLevel = function(level)
            local logLevels = getLogLevels();
            local level_num = tonumber(level);
            if level_num ~= nil and level_num >= 0 and level_num <= 6 then
                obe.Debug.setLevel(level_num);
                Color.print({
                    { text = "Log level set to ", color = Style.Default},
                    { text = logLevels[level_num+1], color = Style.Argument},
                }, 1);
            else
                Color.print({
                    {text = "Invalid argument ", color = Style.Error},
                    {text = level, color = Style.Argument}
                }, 2);
            end
        end        
    },
    Routes = {
        Route.Help("Change log level of ÖbEngine");
        level = Route.Arg {
            Route.Help("Log level");
            Route.Call("logLevel");
            Route.Autocomplete(getLogLevels);
        };
    }
};