local Color = require("Lib/Toolkit/ToolkitRoute");

return {
    Functions = {
        function exit()
            continue = false;
            reload = false;
        end
    },
    Routes = {
        Route.Call("exit");
    }
};