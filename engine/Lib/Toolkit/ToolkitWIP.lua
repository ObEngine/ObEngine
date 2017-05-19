local Route = require("Route");
local inspect = require("inspect");
string.join = require("Join");

print(inspect(Route.Arg("hello", {

})));

print(inspect(Route.Arg("hello", Route.Types.String, {

})));

a = {
    Functions = {
        hello = function(hello)
            print("Hello ! It is " .. hello);
        end
    },
    Routes = {
        Route.Arg("hello", {
            Route.Call("hello");
            Route.Arg("morning", {}),
            Route.Arg("day", {}),
            Route.Arg("afternoon", {}),
            Route.Arg("night", {})
        }),
        Route.Arg("bye", {
            Route.Arg("name", Route.Types.String, {
                Route.Call(function(name)
                    print("Goodbye " .. name);
                end),
            }, function(name)
                return {"Bob", "Martin"};
            end)
        })
    }
};

function autocomplete(command, query)
    local path = {};
    local currentWord = "";
    for char in query:gmatch(".") do
        if char == " " then
            table.insert(path, currentWord);
            currentWord = "";
        else
            currentWord = currentWord .. char;
        end
    end
    if currentWord ~= "" then start = currentWord end
    local entries = 0;
    local subpath = {};
    for _, content in pairs(path) do
        if entries ~= 0 then
            table.insert(subpath, content);
        end
        entries = entries + 1;
    end
    if entries > 0 then
        local recurseIn = nil;
        for _, content in pairs(command) do
            if (content.type == "Path" or content.type == "Arg") and content.id == path[1] then
                recurseIn = content;
                break;
            end
        end
        if recurseIn then
            return autocomplete(recurseIn.children, string.join(subpath, " "));
        else
            return {};
        end
    else
        local arglist = {};
        for _, arg in pairs(command) do
            if arg.type == "Path" then
                if start ~= nil and string.sub(arg.id, 1, string.len(start)) == start then
                    table.insert(arglist, arg.id);
                elseif start == nil then
                    table.insert(arglist, arg.id);
                end
            elseif arg.type == "Arg" then
                print(arg.autocomplete)
                if arg.autocomplete then
                    local autocompleteResult = arg.autocomplete(start);
                    for _, content in pairs(autocompleteResult) do
                        if start ~= nil and string.sub(content, 1, string.len(start)) == start then
                            table.insert(arglist, content);
                        elseif start == nil then
                            table.insert(arglist, content);
                        end
                    end
                end
            end
        end
        return arglist;
    end
end

print(inspect(autocomplete(a.Routes, "bye ")));