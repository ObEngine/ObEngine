local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");
local ordered = require("Lib/StdLib/Ordered");

local Functions = {};

local fs = obe.utils.file;

local SUPPORTED_IMAGE_FORMATS = {
    bmp = true,
    png = true,
    tga = true,
    jpg = true,
    jpeg = true,
    gif = true,
    psd = true,
    hdr = true,
    pic = true
}

function Functions.bake(path)
    local absolute_path_lookup = obe.system.Path(path):find();
    if not absolute_path_lookup:success() then
        Color.print({
            { text = "Invalid animation path '", color = Style.Error},
            { text = path, color = Style.Argument},
            { text = "'", color = Style.Error},
        });
        return;
    end
    local absolute_path = absolute_path_lookup:path();
    local animation_path = obe.system.Path(absolute_path);
    print(("Creating new animation at path '%s'"):format(animation_path));
    local animation_name = animation_path:last();
    print(("Baking animation '%s'"):format(animation_name));

    local directory_files = fs.get_file_list(absolute_path);

    local images = {};
    for _, filename in pairs(directory_files) do
        local file_extension_parts = filename:split(".");
        local file_extension = file_extension_parts[#file_extension_parts]:lower();
        if SUPPORTED_IMAGE_FORMATS[file_extension] then
            table.insert(images, filename);
        end
    end
    local image_indexes = {};
    for image_index, image_filename in pairs(images) do
        local zero_based_index = image_index - 1;
        print(("  - Found image[%s] '%s'"):format(zero_based_index, image_filename))
        table.insert(image_indexes, zero_based_index);
    end

    local animation_content = ordered {
        name = animation_name,
        framerate = 30,
        mode = "OneTime",
        images = images,
        groups = {
            main = {
                content = image_indexes
            }
        },
        code = {
            {command="PlayGroup", group="main"}
        }
    } { "name", "framerate", "mode", "images", "groups", "code" };
    local export_filename = ("%s.animation.vili"):format(animation_name);
    vili.to_file(animation_path:add(export_filename):to_string(), animation_content);
end

return {
    Commands.help("Animation related commands");
    bake = Commands.command {
        path = Commands.arg {
            Commands.call(Functions.bake);
        }
    }
};