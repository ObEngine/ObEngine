local Route = require("Lib/Toolkit/Route");

local Commands = {};

function Commands.interactive()
    print("Entering interactive mode")
    TOOLKIT_CONTEXTS["interactive"] = true;
end

return {
    Routes = {
        Route.Call(Commands.interactive);
        Route.Help("Enters interactive mode");
        Route.Context("terminal")
    }
};