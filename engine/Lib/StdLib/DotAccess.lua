local function dot_access(tbl, key)
    local current_node = tbl;
    for next_jump in key:gmatch("(%w+)") do
        if type(current_node) == "table" then
            current_node = current_node[next_jump];
        else
            error(("can not access key '%s' in path '%s'"):format(next_jump, key));
        end
    end
    return current_node;
end

return {dot_access = dot_access};
