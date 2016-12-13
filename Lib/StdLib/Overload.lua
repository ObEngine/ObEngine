local function overloaded()
    local fns = {};
    local mt = {};
    
    local function oerror()
        print(debug.traceback());
        return error("Invalid argument types to overloaded function");
    end
    
    function mt:__call(...)
        local arg = {...};
        local default = self.default;
        
        local signature = {};
        for i,arg in ipairs {...} do
            print(i, arg.__name, arg, type(arg));
            if type(arg) == "userdata" then
                if arg.__name then
                    signature[i] = arg.__name;
                    signature[i] = signature[i]:gsub("class", "");
                    signature[i] = signature[i]:gsub(" ", "");
                    signature[i] = signature[i]:gsub("*", "");
                    signature[i] = signature[i]:gsub("::", "__");
                end
            elseif type(arg) == "table" then
                if arg.__name then
                    signature[i] = arg.__name;
                end
            else
                signature[i] = type(arg);
            end
        end
        
        signature = table.concat(signature, ".");
        print("GOT:", signature);
        
        return (fns[signature] or self.default)(...);
    end
    
    function mt:__index(key)
        local signature = {};
        local function __newindex(self, key, value)
            print(key, type(key), value, type(value));
            signature[#signature+1] = key;
            fns[table.concat(signature, ".")] = value;
            print("SIGN:", table.concat(signature, "."));
        end
        local function __index(self, key)
            signature[#signature+1] = key;
            return setmetatable({}, { __index = __index, __newindex = __newindex });
        end
        return __index(self, key);
    end
    
    function mt:__newindex(key, value)
        fns[key] = value;
    end
    
    return setmetatable({ default = oerror }, mt);
end

return overloaded;