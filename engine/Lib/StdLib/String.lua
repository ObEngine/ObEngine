local String = {};

String.split = function(input, sep)
    if sep == nil then sep = "%s"; end
    local t = {}; local i = 1;
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

String.join = function(list, delimiter)
   local len = #list;
   if len == 0 then
      return "";
   end
   local string = list[1];
   for i = 2, len do 
      string = string .. delimiter .. list[i];
   end
   return string;
end

return String;