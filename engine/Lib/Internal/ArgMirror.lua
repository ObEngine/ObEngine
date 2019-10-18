local Mirror = {};

function Mirror.GetArgs(fun)
    local args = {}
    local hook = debug.gethook()

    local argHook = function( ... )
        local info = debug.getinfo(3)
        if 'pcall' ~= info.name then return end

        for i = 1, math.huge do
            local name, value = debug.getlocal(2, i)
            if '(*temporary)' == name then
                debug.sethook(hook)
                error('')
                return
            end
            table.insert(args,name)
        end
    end

    debug.sethook(argHook, "c")
    pcall(fun)

    return args
end

__nil_table = {
    __NIL = true
};

function Mirror.Unpack(t, i)
    i = i or 1
    if t[i] ~= nil then
        if t[i] == __nil_table then
            return nil, Mirror.Unpack(t, i + 1)
        else
            return t[i], Mirror.Unpack(t, i + 1)
        end
    end
end

return Mirror;