return function(list, delimiter)
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