local Commands = require("obe://Lib/Toolkit/Commands");
local dot_access = require("obe://Lib/StdLib/DotAccess").dot_access;
---@module "Lib.Extlibs.json"
local json = require("extlibs://json");
local Color = require("Lib/StdLib/ConsoleColor");
local Style = require("Lib/Toolkit/Stylesheet");

local function _parse_(filename)
    print(vili.dump(vili.from_file(filename)));
end

local function _parse_and_get_(filename, getter)
    local data = vili.from_file(filename);
    print(vili.dump(dot_access(data, getter)));
end

local function _edit_(filename, getter, newvalue)
    local data = vili.from_file(filename);
    local parent_getter = "";
    local sub_getter = getter;
    local tbl = data;
    if getter:find("%.") then
        parent_getter, sub_getter = getter:sub(1, getter:rfind(".") - 1),
            getter:sub(getter:rfind(".") + 1);
        tbl = dot_access(data, parent_getter);
    end
    local vilified_newvalue = vili.parser.from_string("data: " .. newvalue).data;
    local luaified_newvalue = vili.to_lua(vilified_newvalue);
    tbl[sub_getter] = luaified_newvalue;
    vili.to_file(filename, data);
end

local function _from_json_(json_filepath)
    local json_fd <close> = io.open(json_filepath, "r");
    if not json_fd then
        Color.print({
            { text = "Could not open json file at path '", color = Style.Error},
            { text = json_filepath, color = Style.Argument},
            { text = "'", color = Style.Error},
        });
        return
    end
    local json_content = json_fd:read("*a");
    local data = json.decode(json_content);
    local vili_content = vili.to_string(data);
    print(vili_content);
end

local function _to_json_(vili_filepath)
    local content = vili.from_file(vili_filepath);
    local json_content = json.encode(content);
    print(json_content);
end

return {
    parse = Commands.command {
        Commands.help "Parses a vili document",
        filename = Commands.arg {
            Commands.help "Path to the vili document to parse",
            Commands.call(_parse_),
            getter = Commands.arg {
                Commands.help "Identifier of the vili element to retrieve inside the document",
                Commands.call(_parse_and_get_)
            }
        }
    },
    edit = Commands.command {
        Commands.help "Edit a vili document",
        filename = Commands.arg {
            Commands.help "Path to the vili document to edit",
            getter = Commands.arg {
                Commands.help "Identifier of the vili element to edit inside the document",
                newvalue = Commands.arg {
                    Commands.help "New value of the element",
                    Commands.call(_edit_)
                }
            }
        }
    },
    from_json = Commands.command {
        Commands.help "Converts a JSON file to a Vili file",
        json_filepath = Commands.arg {
            Commands.help "Path to the JSON file to convert",
            Commands.call(_from_json_)
        }
    },
    to_json = Commands.command {
        Commands.help "Converts a Vili file to a JSON file",
        vili_filepath = Commands.arg {
            Commands.help "Path to the Vili file to convert",
            Commands.call(_to_json_)
        }
    }
};
