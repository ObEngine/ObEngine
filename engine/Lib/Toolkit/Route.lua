return {
    Arg = function(id, type, children, autocomplete)
    
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
    Types = {
        String = "String",
        Int = "Int",
        Any = "Any"
    }
}