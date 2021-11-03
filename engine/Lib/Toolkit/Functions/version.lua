local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");

local function _version_()
    Color.print(
        {
            {text = "ÖbEngine is in version ", color = Style.Default},
            {text = obe.version, color = Style.Version}
        }, 1
    );
end

local function _major_()
    local major_version = string.split(string.sub(obe.version, 2), ".")[1];
    Color.print(
        {
            {text = "ÖbEngine's major version is ", color = Style.Default},
            {text = major_version, color = Style.Version}
        }, 1
    );
end

local function _minor_()
    local minor_version = string.split(string.sub(obe.version, 2), ".")[2];
    Color.print(
        {
            {text = "ÖbEngine's minor version is ", color = Style.Default},
            {text = minor_version, color = Style.Version}
        }, 1
    );
end

local function _patch_()
    local patch_version = string.split(string.sub(obe.version, 2), ".")[3];
    Color.print(
        {
            {text = "ÖbEngine's patch version is ", color = Style.Default},
            {text = patch_version, color = Style.Version}
        }, 1
    );
end

local function _commit_()
    local commit_version = obe.commit;
    Color.print(
        {
            {text = "ÖbEngine's commit version is ", color = Style.Default},
            {text = commit_version, color = Style.Version}
        }, 1
    );
end

local function _branch_()
    local branch_version = obe.branch;
    Color.print(
        {
            {text = "ÖbEngine's branch version is ", color = Style.Default},
            {text = branch_version, color = Style.Version}
        }, 1
    );
end

return {
    Commands.help("Get ÖbEngine's version"),
    Commands.call(_version_),
    major = Commands.command {
        Commands.help("Get ÖbEngine's major version"), Commands.call(_major_)
    },
    minor = Commands.command {
        Commands.help("Get ÖbEngine's minor version"), Commands.call(_minor_)
    },
    patch = Commands.command {
        Commands.help("Get ÖbEngine's patch version"), Commands.call(_patch_)
    },
    commit = Commands.command {
        Commands.help("Get ÖbEngine's commit version"), Commands.call(_commit_)
    },
    branch = Commands.command {
        Commands.help("Get ÖbEngine's branch version"), Commands.call(_branch_)
    }
};
