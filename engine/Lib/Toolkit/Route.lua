return {
    Node = function(id, children)
        return {
            id = id,
            children = children,
            type = "Node",
        };
    end,
    
    Arg = function(id, children)
        return {
            id = id,
            children = children,
            type = "Argument",
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

    Types = {
        String = "String",
        Int = "Int",
        Any = "Any"
    }
}