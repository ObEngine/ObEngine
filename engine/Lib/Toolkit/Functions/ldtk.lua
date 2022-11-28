local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");
local ordered = require("Lib/StdLib/Ordered");
---@module "Lib.Extlibs.json"
local json = require("extlibs://json");

local Functions = {};

local fs = obe.utils.file;

local function get_level_field_instance_values(field_instances)
    local values = {};
    for _, field_instance in pairs(field_instances) do
        values[field_instance.__identifier] = field_instance.__value;
    end
    return values;
end

local function get_meta_infos(data)
    for _, level in pairs(data.levels) do
        if level.identifier == "Meta" then
            return get_level_field_instance_values(level.fieldInstances or {});
        end
    end
    return {};
end

local ConverterState = class();

function ConverterState:_init(directory)
    self.directory = directory;
    self.tilesets = {};
    self.tilesets_uids = {};
    self.tilesets_order = {};
    self.firstTileIdCounter = 1;
    self.converter_script = nil;
end

function ConverterState:set_converter_script(script_path)
    -- check if script path ends with .lua
    if not string.match(script_path, "%.lua$") then
        error("converter_script extension must be .lua");
    end
    -- remove .lua suffix
    local converter_script_path = obe.system.Path(self.directory):add(script_path):to_string();
    print(("Using converter script: '%s'"):format(converter_script_path));
    self.converter_script = dofile(converter_script_path);
end

function ConverterState:register_tileset(tileset)
    local tilecount = tileset.__cWid * tileset.__cHei;

    local tileset_ext = {};
    if self.converter_script and self.converter_script.on_register_tileset then
        tileset_ext = self.converter_script.on_register_tileset(self, tileset) or {};
    end

    self.tilesets[tileset.identifier] = ordered {
        firstTileId = tileset_ext.firstTileId or self.firstTileIdCounter,
        columns = tileset_ext.columns or tileset.__cWid,
        tilecount = tileset_ext.tilecount or tilecount,
        margin = tileset_ext.margin or tileset.padding,
        spacing = tileset_ext.spacing or tileset.spacing,
        tile = ordered {
            width = (tileset_ext.tile or {}).width or tileset.tileGridSize,
            height = (tileset_ext.tile or {}).height or tileset.tileGridSize
        } {"width", "height"},
        image = ordered {
            width = (tileset_ext.image or {}).width or tileset.pxWid,
            height = (tileset_ext.image or {}).height or tileset.pxHei,
            path = (tileset_ext.image or {}).path or tileset.relPath
        } {"width", "height", "path"},
        animations = tileset_ext.animations or {},
        collisions = tileset_ext.collisions or {}
    } {"firstTileId", "columns", "tilecount", "margin", "spacing", "tile", "image", "animations", "collisions"};
    table.insert(self.tilesets_order, tileset.identifier);
    self.tilesets_uids[tileset.uid] = tileset.identifier;
    self.firstTileIdCounter = self.firstTileIdCounter + tilecount;
end

function ConverterState:get_tile_id(tileset_uid, tile_uid)
    local tileset_name = self.tilesets_uids[tileset_uid];
    local tileset = self.tilesets[tileset_name];
    return tileset.firstTileId + tile_uid;
end

local LayerConverters = {};

function LayerConverters.convert_layer(state, layer, layer_order)
    return LayerConverters[layer.__type](state, layer, layer_order);
end

local function build_empty_tilemap(size)
    local new_tilemap = {};
    for i = 1, size do
        table.insert(new_tilemap, 0);
    end
    return new_tilemap;
end

local BIT_FLIPS = {
    [0] = 0x00000000,
    [1] = 0x80000000,
    [2] = 0x40000000,
    [3] = 0x20000000
}

local function convert_tilemap(state, layer, tilemap)
    local first_layer = build_empty_tilemap(layer.__cWid * layer.__cHei);
    local tilemaps_export = {
        first_layer
    };
    for _, tile in pairs(tilemap) do
        local x, y = tile.px[1] / layer.__gridSize, tile.px[2] / layer.__gridSize;
        local tile_value = tile.t + BIT_FLIPS[tile.f];
        local export_idx = y * layer.__cWid + x + 1;
        if export_idx < #first_layer then
            local found_empty_tile = false;
            for _, tilemap_export in pairs(tilemaps_export) do
                if tilemap_export[export_idx] == 0 then
                    tilemap_export[export_idx] = state:get_tile_id(layer.__tilesetDefUid, tile_value);
                    found_empty_tile = true;
                    break;
                end
            end
            if not found_empty_tile then
                table.insert(tilemaps_export, build_empty_tilemap(layer.__cWid * layer.__cHei));
                tilemaps_export[#tilemaps_export][export_idx] = state:get_tile_id(layer.__tilesetDefUid, tile.t);
            end
        else
            print("  WARNING: Tile out of bounds:", x, y, layer.__cWid, layer.__cHei, export_idx, #first_layer);
        end
    end
    return tilemaps_export;
end

function LayerConverters.IntGrid(state, layer, layer_order)
    layer_order = layer_order or 1;

    local exported_layers = {};
    local exported_tilemaps = convert_tilemap(state, layer, layer.autoLayerTiles);
    local layer_names_order = {};
    for tilemap_index, exported_tilemap in pairs(exported_tilemaps) do
        local layer_identifier = layer.__identifier;
        if tilemap_index > 1 then
            layer_identifier = ("%s_%s"):format(layer_identifier, tilemap_index);
        end
        table.insert(layer_names_order, layer_identifier);
        exported_layers[layer_identifier] = ordered {
            x = layer.pxOffsetX,
            y = layer.pxOffsetY,
            width = layer.__cWid,
            height = layer.__cHei,
            layer = layer_order,
            sublayer = tilemap_index,
            visible = layer.visible,
            opacity = 1,
            tileWidth = layer.__gridSize,
            tileHeight = layer.__gridSize,
            tiles = exported_tilemap,
        } {"x", "y", "width", "height", "layer", "sublayer", "visible", "opacity", "tileWidth", "tileHeight", "tiles"};
    end

    return exported_layers, layer_names_order;
end

function LayerConverters.Tiles(state, layer, layer_order)
    layer_order = layer_order or 1;

    local exported_layers = {};
    local exported_tilemaps = convert_tilemap(state, layer, layer.gridTiles);
    local layer_names_order = {};
    for tilemap_index, exported_tilemap in pairs(exported_tilemaps) do
        local layer_identifier = layer.__identifier;
        if tilemap_index > 1 then
            layer_identifier = ("%s_%s"):format(layer_identifier, tilemap_index);
        end
        table.insert(layer_names_order, layer_identifier);
        exported_layers[layer_identifier] = ordered {
            x = layer.pxOffsetX,
            y = layer.pxOffsetY,
            width = layer.__cWid,
            height = layer.__cHei,
            layer = layer_order,
            sublayer = tilemap_index,
            visible = layer.visible,
            opacity = 1,
            tileWidth = layer.__gridSize,
            tileHeight = layer.__gridSize,
            tiles = exported_tilemap,
        } {"x", "y", "width", "height", "layer", "sublayer", "visible", "opacity", "tileWidth", "tileHeight", "tiles"};
    end
    return exported_layers, layer_names_order;
end

function Functions.import(path)
    local absolute_path_lookup = obe.system.Path(path):find();
    if not absolute_path_lookup:success() then
        Color.print({
            { text = "Invalid LDtk map path '", color = Style.Error},
            { text = path, color = Style.Argument},
            { text = "'", color = Style.Error},
        });
        return;
    end
    local absolute_path = absolute_path_lookup:path();
    local tilemap_path = obe.system.Path(absolute_path);
    print(("Converting LDtk map at path '%s'"):format(tilemap_path:to_string()));
    local tilemap_fd <close> = io.open(tilemap_path:to_string(), "r");
    if not tilemap_fd then
        Color.print({
            { text = "Could not open LDtk map at path '", color = Style.Error},
            { text = tilemap_path:to_string(), color = Style.Argument},
            { text = "'", color = Style.Error},
        });
        return;
    end
    local tilemap_file_content = tilemap_fd:read("*a");
    local data = json.decode(tilemap_file_content);

    if type(data) ~= "table" then
        Color.print({
            { text = "Unexpected JSON root node (expected table, got '", color = Style.Error},
            { text = type(data), color = Style.Argument},
            { text = "')", color = Style.Error},
        });
        return;
    end

    local meta = get_meta_infos(data);

    local state = ConverterState(tilemap_path:parent():to_string());

    if meta.converter_script then
        state:set_converter_script(meta.converter_script);
    end

    for _, tileset in pairs(data.defs.tilesets) do
        state:register_tileset(tileset);
    end

    for _, level in pairs(data.levels) do
        if level.identifier ~= "Meta" then
            print(("  - Exporting level '%s'"):format(level.identifier));
            local layers_export = {};
            local layer_names_order = {};
            -- Table used to check if tileset is used in the current level
            local tilesets_usage = {};
            for _, tileset_name in pairs(state.tilesets_order) do
                tilesets_usage[tileset_name] = false;
            end
            local base_layer = nil;
            for layer_idx, layer in pairs(level.layerInstances) do
                if layer.__tilesetDefUid then
                    tilesets_usage[state.tilesets_uids[layer.__tilesetDefUid]] = true;
                    print(("    - Exporting layer '%s' at layer (%s)"):format(layer.__identifier, layer_idx));

                    local exported_sub_layers, sub_layer_names_order = LayerConverters.convert_layer(state, layer, layer_idx);
                    for _, sub_layer_name in pairs(sub_layer_names_order) do
                        table.insert(layer_names_order, sub_layer_name);
                    end
                    for exported_sub_layer_name, exported_sub_layer in pairs(exported_sub_layers) do
                        if base_layer == nil then
                            base_layer = exported_sub_layer;
                        end
                        layers_export[exported_sub_layer_name] = exported_sub_layer;
                    end
                else
                    print(("    - Skipping unused layer '%s'"):format(layer.__identifier));
                end
            end
            local base_layer_dimensions = (base_layer or {tileWidth = 16, tileHeight = 16, width = 10, height = 10});

            local used_tilesets_names = {};
            for _, tileset_name in pairs(state.tilesets_order) do
                if tilesets_usage[tileset_name] then
                    table.insert(used_tilesets_names, tileset_name);
                end
            end
            local export = ordered {
                Meta = ordered {
                    name = level.identifier,
                    background = level.bgColor or "#000000",
                } {"name", "background"},
                View = ordered {
                    size = 1.0,
                    position = ordered {
                        x = 0.0,
                        y = 0.0,
                        unit = "SceneUnits",
                    } {"x", "y", "unit"},
                    referential = "TopLeft"
                } {"size", "position", "referential"},
                Tiles = ordered {
                    tileWidth = base_layer_dimensions.tileWidth,
                    tileHeight = base_layer_dimensions.tileHeight,
                    width = base_layer_dimensions.width,
                    height = base_layer_dimensions.height,

                    layers = ordered(layers_export)(layer_names_order),
                    sources = ordered(state.tilesets)(used_tilesets_names)
                } {"tileWidth", "tileHeight", "width", "height", "layers", "sources"},
            } {"Meta", "View", "Tiles"};
            local dump_options = vili.writer.dump_options();
            dump_options.array.items_per_line.any = base_layer_dimensions.width;
            dump_options.array.max_line_length = 1000;
            local scene_file_path = ("%s.vili"):format(level.identifier);
            print(("    - Writing scene file at path '%s'"):format(scene_file_path));
            vili.to_file(scene_file_path, export, dump_options);
        end
    end
end

return {
    Commands.help("LDtk related commands");
    import = Commands.command {
        path = Commands.arg {
            Commands.call(Functions.import);
        }
    }
};