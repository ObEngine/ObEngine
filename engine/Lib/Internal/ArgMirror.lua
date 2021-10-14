local Mirror = {};

function Mirror.GetArgs(func)
    local args = {}

    for i = 1, debug.getinfo(func).nparams, 1 do
        table.insert(args, debug.getlocal(func, i));
    end
    return args;
end

Mirror.__nil_table = {__NIL = true};

function Mirror.Unpack(t, i)
    i = i or 1
    if t[i] ~= nil then
        if t[i] == Mirror.__nil_table then
            return nil, Mirror.Unpack(t, i + 1)
        else
            return t[i], Mirror.Unpack(t, i + 1)
        end
    end
end

return Mirror;
