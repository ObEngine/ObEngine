return {
    Arg = function(id, type, children, autocomplete)
        local ntype, argtype;
        if children then ntype = "Arg"; argtype = type;
        else ntype = "Path";
        end
        children = children or type;

        return {
            id = id,
            children = children,
            type = ntype,
            argtype = argtype,
            autocomplete = autocomplete
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