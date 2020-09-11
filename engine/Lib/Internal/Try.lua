function try(t)
    local code = t[1];
    local result, err = pcall(code);
    if err ~= nil then
        local exception_type = string.match(err, "Exception %[([%a]+)%] occured");
        if t[exception_type] then
            return t[exception_type](err), err;
        elseif t["_"] then
            return t["_"](err), err;
        end
    end
    return result, err;
end

return try;