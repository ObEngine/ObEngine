local function custom_searcher( module_name )
    module_name = module_name .. '.lua';
    local path = obe.System.Path(module_name):find():path();
    if path ~= "" then
        return loadfile(path);
    end
end

table.insert(package.searchers, 1, custom_searcher);