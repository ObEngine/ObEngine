local tablex = require("extlibs://pl.tablex");

local function set_reactive_value(tbl, key, value)
    local schema = getmetatable(tbl);
    if type(key) == "number" and not schema.setters[key] and schema.setters.__number then
        schema.setters.__number(tbl.ref, key, value);
    else
        if schema.setters[key] then
            schema.setters[key](tbl.ref, value);
        else
            error(("Can't find CanvasElement attribute '%s'"):format(key));
        end
    end
end

local function get_reactive_value(tbl, key)
    local schema = getmetatable(tbl);
    if schema.getters[key] == nil then
        error(("Can't find CanvasElement attribute '%s'"):format(key));
    end
    if type(schema.getters[key]) == "function" then
        return schema.getters[key](tbl.ref);
    elseif type(key) == "number" and not schema.getters[key] and schema.getters.__number then
        schema.getters.__number(tbl.ref)
    elseif type(schema.getters[key]) == "table" then
        if rawget(tbl, key) == nil then
            rawset(tbl, key, schema.getters[key](tbl.ref));
        end
        return rawget(tbl, key);
    end
end

local function call_reactive(tbl, values, usecache)
    values = values or {};
    local mt = getmetatable(tbl);
    if usecache then
        for k, v in pairs(values) do
            mt.__cache[k] = v;
        end
    else
        if #mt.priority > 0 then
            for k, v in pairs(mt.priority) do
                if values[v] then
                    set_reactive_value(tbl, v, values[v]);
                    values[v] = nil;
                end
            end
        end
        for k, v in pairs(values) do
            set_reactive_value(tbl, k, v);
        end
    end
    return tbl;
end

local function gather_reactive_bases(schema)
    local all_schemas = {};
    local bases = schema.bases or {};

    for _, schema_base in pairs(bases) do
        local schema_base_bases = gather_reactive_bases(schema_base);
        table.insert(schema_base_bases, schema_base);
        for _, schema_base_base in pairs(schema_base_bases) do
            if not tablex.find(all_schemas, schema_base_base) then
                table.insert(all_schemas, schema_base_base);
            end
        end
    end

    table.insert(all_schemas, schema);
    return all_schemas;
end

local function make_reactive(main_schema, schema_type)
    schema_type = schema_type or main_schema.type;
    local getters = {};
    local setters = {};
    local priority = {};

    local all_schemas = gather_reactive_bases(main_schema);

    for _, schema in pairs(all_schemas) do
        if schema.priority then
            for _, priority_name in pairs(schema.priority) do
                if not tablex.find(priority, priority_name) then
                    table.insert(priority, priority_name);
                end
            end
        end
        for getter_name, getter_value in pairs(schema.getters) do
            if type(getter_value) == "table" then
                getters[getter_name] = make_reactive(getter_value, ("%s.%s"):format(schema_type, getter_name));
            else
                getters[getter_name] = getter_value;
            end
            getters[getter_name] = getter_value;
        end
        for setter_name, setter_value in pairs(schema.setters) do
            if type(setter_value) == "table" then
                setters[setter_name] = make_reactive(setter_value, ("%s.%s"):format(schema_type, setter_name));
            else
                setters[setter_name] = setter_value;
            end
        end
    end

    local mt = setmetatable({
        type = schema_type,
        bases = main_schema.bases,
        getters = getters,
        setters = setters,
        priority = priority,

        __index = get_reactive_value,
        __newindex = set_reactive_value,
        __call = call_reactive,
    }, {
        __call = function(t, internal_shape)
            return setmetatable({ref = internal_shape}, t);
        end
    });

    return mt;
end

return {
    make_reactive = make_reactive
}