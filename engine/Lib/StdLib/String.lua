local String = {};

String.split = function(input, sep)
    if sep == nil then sep = "%s"; end
    local t = {}; i = 1;
    for str in string.gmatch(input, "([^" .. sep .. "]+)") do
        t[i] = str; i = i + 1;
    end
    return t;
end

String.isNumeric = function(input)
    if tonumber(input) ~= nil then return true;
    else return false;
    end
end

return String;