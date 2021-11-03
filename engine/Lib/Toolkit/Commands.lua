return {
    command = function(children)
        return {
            children = children,
            type = "command",
        };
    end,

    arg = function(children)
        return {
            children = children,
            type = "arg",
            argType = "any"
        };
    end,

    number = function(children)
        return {
            children = children,
            type = "arg",
            argType = "number"
        };
    end,

    string = function(children)
        return {
            children = children,
            type = "arg",
            argType = "string"
        };
    end,

    boolean = function(children)
        return {
            children = children,
            type = "arg",
            argType = "boolean"
        };
    end,

    call = function(func)
        if type(func) ~= "function" then
            error("argument to Route.call must be a function (got " .. tostring(func) .. ")");
        end
        return {
            type = "call",
            ref = func
        };
    end,

    autocomplete = function(func)
        return {
            type = "autocomplete",
            ref = func
        }
    end,

    help = function(helpString)
        return {
            type = "help",
            help = helpString
        }
    end,

    context = function(context)
        return {
            type = "context",
            context = context
        }
    end,
}