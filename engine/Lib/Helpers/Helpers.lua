local function load_features(features)
    -- Internal
    if feature["logger"] then
        require("intlibs://Logger");
    end
    if features["ordered"] then
        ordered = require("intlibs://Ordered");
    end
    if features["try"] then
        try = require("intlibs://Try");
    end
    -- Extlibs
    if features["class"] then
        class = require("extlibs://pl.class")
    end
    if features["debugger"] then
        dbg = require("extlibs://debugger");
    end
    if features["inspect"] then
        inspect = require("extlibs://Inspect");
    end
    if features["stringx"] then
        local stringx = require("extlibs://pl.stringx");
        stringx:import();
    end
end

return {
    load_features = load_features
}