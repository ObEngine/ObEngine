local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");
local TI = require("Lib/Toolkit/Input");

function getWorkloadNames()
    return {"Alpha", "Altimeter", "Beta", "Bechamel"};
end

function suggestNums()
    return { "100", "222", "3033", "3040" };
end

function suggestStrs()
    return { "Bob", "1Bison", "1terpolation", "30calite" };
end

return {
    Functions = {
        create = function(workloadName, create)
            print("fn called", create);
            Color.print("Workload created " .. workloadName);
        end,
        create_num = function(workloadNameNumber, create)
            print("fn called", create);
            Color.print("Workload created " .. workloadNameNumber);
        end,
        mount = function(workloadName)
            Color.print("Workload mounted" .. workloadName);
        end,
        mourn = function(workloadName)
            Color.print("Workload mourned" .. workloadName);
            Color.print("Tell me your name");
            Color.print("Oh.. Your name is " .. TI.input());
        end
    },
    Routes = {
        Route.Help("Commands to work with Workloads");
        create = Route.Node {
            Route.Help("Creates a new Workload");
            workloadNameNumber = Route.NumberArg {
                Route.Help("Name of the new Workload to create (number edition)");
                Route.Call("create_num");
                Route.Autocomplete(suggestNums);
            };
            workloadName = Route.StringArg {
                Route.Help("Name of the new Workload to create (string edition)");
                Route.Call("create");
                Route.Autocomplete(suggestStrs);
            };
        };
        mount = Route.Node {
            Route.Help("Mounts a Workload");
            workloadName = Route.Arg {
                Route.Call("mount");
                Route.Help("Name of the Workload you want to mount");
                Route.Autocomplete(getWorkloadNames);
            };
        };
        mourn = Route.Node {
            Route.Help("Indexes an existing Workload");
            workloadName = Route.Arg {
                Route.Call("mourn");
                Route.Help("Name of the Workload you want to mourn");
                Route.Autocomplete(getWorkloadNames);
            };
        }
    }
};