local function ordered_wrapper(tbl, order)
    return setmetatable(tbl, {
        __pairs = function(tbl)
            local i = 1;
            return function(_, _)
                local real_key = order[i];
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
        return ordered_wrapper(tbl, order)
    end
end

return ordered;