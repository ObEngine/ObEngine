local function ordered_wrapper(tbl, order)
    local skip_nil = true;
    if order.skip_nil ~= nil then
        skip_nil = order.skip_nil;
    end
    return setmetatable(tbl, {
        __pairs = function(tbl)
            local i = 1;
            return function(_, _)
                local real_key = order[i];
                -- skip null values
                if skip_nil then
                    while tbl[real_key] == nil do
                        i = i + 1;
                        real_key = order[i];
                        if real_key == nil then
                            return nil;
                        end
                    end
                end
                i = i + 1;
                if real_key ~= nil then
                    return real_key, tbl[real_key];
                else
                    return nil;
                end
            end, tbl, nil
        end
    })
end

---creates a table with predictable iteration order
---@param tbl table#input table
---@return function#partial function expecting order table as a parameter
local function ordered(tbl)
    return function(order)
        return ordered_wrapper(tbl, order);
    end
end

return ordered;