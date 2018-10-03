return {
    Node = function(children)
        return {
            children = children,
            type = "Node",
        };
    end,

    Arg = function(children)
        return {
            children = children,
            type = "Argument",
            argType = "any"
        };
    end,

    NumberArg = function(children)
        return {
            children = children,
            type = "Argument",
            argType = "number"
        };
    end,

    StringArg = function(children)
        return {
            children = children,
            type = "Argument",
            argType = "string"
        };
    end,

    BooleanArg = function(children)
        return {
            children = children,
            type = "Argument",
            argType = "boolean"
        };
    end,

    Call = function(func)
        local calltype;
        if (type(func) == "string") then
            calltype = "Ref";
        elseif (type(func) == "function") then
            calltype = "Direct";
        end
        return {
            type = "Call",
            calltype = calltype,
            ref = func
        };
    end,

    Autocomplete = function(func)
        return {
            type = "Autocomplete",
            ref = func
        }
    end,

    Help = function(helpString)
        return {
            type = "Help",
            help = helpString
        }
    end,
}