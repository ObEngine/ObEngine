local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");
local ordered = require("Lib/StdLib/Ordered");
local json = require("extlibs://json");

local Functions = {};

function Functions.import_aseprite_animation(path)
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
    local animation_name = animation_path:last();
    print(("Importing Aseprite animation at path '%s' (%s)"):format(animation_path, animation_name));

    local animation_fd <close> = io.open(animation_path:to_string(), "r");
    if animation_fd == nil then
        Color.print({
            { text = "Could not open aseprite animation at path '", color = Style.Error},
            { text = animation_path:to_string(), color = Style.Argument},
            { text = "'", color = Style.Error},
        });
        return;
    end

    local animation_file_content = animation_fd:read("*a");
    local animation_data = json.decode(animation_file_content);

    local frames = {};
    local frame_indexes = {};
    local frames_metadata = {};
    local frames_metadata_order = {};
    for i, frame_data in pairs(animation_data.frames) do
        table.insert(frames, ordered {
            x = frame_data.frame.x,
            y = frame_data.frame.y,
            width = frame_data.frame.w,
            height = frame_data.frame.h
        } {"x", "y", "width", "height"});
        table.insert(frame_indexes, i - 1);
        if frame_data.meta then
            local frame_key = ("frame_%s"):format(i - 1);
            frames_metadata[frame_key] = frame_data.meta;
            table.insert(frames_metadata_order, frame_key);
        end
    end

    local animation_content = ordered {
        name = animation_name,
        framerate = 1 / (animation_data.frames[1].duration / 1000),
        mode = "OneTime",
        source = {
            spritesheet = ordered {
                image = animation_data.meta.image,
                frames = frames
            } {"image", "frames"}
        },
        frames_metadata = ordered(frames_metadata)(frames_metadata_order),
        groups = {
            main = {
                content = frame_indexes
            }
        },
        code = {
            {command="PlayGroup", group="main"}
        }
    } { "name", "framerate", "mode", "source", "frames_metadata", "groups", "code" };
    local export_filename = ("%s.animation.vili"):format(animation_name);
    print("Parent", animation_path)
    local export_path = animation_path:parent():add(export_filename):to_string();
    print(("Exporting file to '%s'"):format(export_path));
    vili.to_file(export_path, animation_content);
end

return {
    Commands.help("Aseprite import command");
    import = Commands.command {
        path = Commands.arg {
            Commands.call(Functions.import_aseprite_animation);
        }
    }
};