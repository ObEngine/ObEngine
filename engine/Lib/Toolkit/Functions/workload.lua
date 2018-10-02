local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");

function getWorkloadNames()
    return {"Alpha", "Altimeter", "Beta", "Bechamel"};
end

return {
    Functions = {
        create = function(workloadName, create)
            print("fn called", create);
            Color.print("Workload created " .. workloadName);
        end,
        mount = function(workloadName)
            Color.print("Workload mounted" .. workloadName);
        end,
        mourn = function(workloadName)
            Color.print("Workload mourned" .. workloadName);
        end
    },
    Routes = {
        Route.Help("Commands to work with Workloads");
        Route.Node("create", {
            Route.Help("Creates a new Workload");
            Route.Arg("workloadName", "number", {
                Route.Help("Name of the new Workload to create (number edition)");
                Route.Call("create");
            });
            Route.Arg("workloadName", "string", {
                Route.Help("Name of the new Workload to create (string edition)");
                Route.Call("create");
            });
        }),
        Route.Node("mount", {
            Route.Help("Mounts a Workload");
            Route.Arg("workloadName", {
                Route.Call("mount");
                Route.Help("Name of the Workload you want to mount");
                Route.Autocomplete(function(start)
                    return getWorkloadNames();
                end)
            });
        }),
        Route.Node("mourn", {
            Route.Help("Indexes an existing Workload");
            Route.Arg("workloadName", {
                Route.Call("mourn");
                Route.Help("Name of the Workload you want to index");
                Route.Autocomplete(function(start)
                    return getWorkloadNames();
                end)
            });
        })
    }
};