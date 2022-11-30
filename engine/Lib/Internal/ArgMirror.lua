local function get_args(func)
    local args = {}

    for i = 1, debug.getinfo(func).nparams, 1 do
        table.insert(args, debug.getlocal(func, i));
    end
    return args;
end

local _nil_table = {__NIL = true};

local function unpack_with_nil(tbl, from_index)
    local i = from_index or 1;
    if tbl[i] ~= nil then
        if tbl[i] == _nil_table then
            return nil, unpack_with_nil(tbl, i + 1);
        else
            return tbl[i], unpack_with_nil(tbl, i + 1);
        end
    end
end

return {
    _nil_table = _nil_table,
    get_args = get_args,
    unpack_with_nil = unpack_with_nil
};
