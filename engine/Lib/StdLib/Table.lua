local Table = {};

function Table.getSize(mtable)
    local size = 0;
    for _, _ in pairs(mtable) do
        size = size + 1;
    end
    return size;
end

function Table.getKeys(mtable)
    local keys = {};
    for k, v in pairs(mtable) do
        table.insert(keys, k);
    end
    return keys;
end

-- Get the table key at a given table index
function Table.getKeyAtIndex(array, index)
    for key, content in pairs(array) do
        if content.index == index then
            return key;
        end
    end
end

return Table;