local Route = require("Lib/Toolkit/Route");

local Commands = {};

function Commands.exit()
    print("Exiting Toolkit")
    TOOLKIT_CONTEXTS["interactive"] = false;
end

return {
    Routes = {
        Route.Call(Commands.exit);
        Route.Help("Exits the Toolkit Console");
        Route.Context("interactive")
    }
};