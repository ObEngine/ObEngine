return {
    input = function()
        local inp = coroutine.yield();
        return inp;
    end,
    wait = function(t)
        coroutine.yield({"sleep", t});
    end,
    completions = function(t)
        local finalTable = {};
        for k, v in pairs(t) do
            if type(v) == "string" then
                finalTable[k] = v;
            elseif type(v) == "table" then
                finalTable[k] = { completion = v[1], info = v[2] };
            elseif type(v) == "number" or type(v) == "boolean" then
                finalTable[k] = tostring(v);
            end
        end
        return function() return finalTable; end;
    end
};