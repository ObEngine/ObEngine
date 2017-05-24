local Route = require("Lib/Toolkit/Route");

return {
    Functions = {
        exit = function()
            _term_close();
        end
    },
    Routes = {
        Route.Call("exit");
    }
};