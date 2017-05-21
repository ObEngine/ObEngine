local Route = require("Lib/Toolkit/Route");

return {
    Functions = {
        exit = function()
            continue = false;
            reload = false;
        end
    },
    Routes = {
        Route.Call("exit");
    }
};