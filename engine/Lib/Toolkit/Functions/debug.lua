local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

function getDebugLevels()
    local debugLevels = {
        "0 (trace)",
        "1 (debug)",
        "2 (info)",
        "3 (warn)",
        "4 (err)",
        "5 (critical)",
        "6 (off)"
    };
    return debugLevels;

end
return {
    Functions = {
        debug = function(level)
            local debugLevels = getDebugLevels();
            local level_num = tonumber(level);
            if level_num ~= nil and level_num >= 0 and level_num <= 6 then
                obe.Debug.setLevel(level_num);
                Color.print({
                    { text = "Debug level set to ", color = Style.Default},
                    { text = debugLevels[level_num+1], color = Style.Argument},
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
        Route.Help("Change debug level of ÖbEngine");
        level = Route.Arg {
            Route.Help("Debug level");
            Route.Call("debug");
            Route.Autocomplete(getDebugLevels);
        };
    }
};