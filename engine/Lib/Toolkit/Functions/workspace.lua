local Color = require("Lib/StdLib/ConsoleColor");

function workspace(argtable)
    local action = argtable.action;
    local wsname = argtable.wsname;
    local parser = Core.Vili.DataParser.new();
    local Types = Core.Vili.AttributeType;
    parser:parseFile("Workspace/Workspaces.vili", true);
    if action == "use" and wsname ~= nil then
        if (parser:root():contains(Types.ComplexAttribute, wsname)) then
            Core.Utils.File.copy("Workspace/" .. wsname .. "/Mount.vili", "Mount.vili");
            Color.print({
                {color = "lightgreen", text = "Current workspace has been successfully switched to "},
                {color = "lightcyan", text = wsname .. "\n"}
            }, 2);
        else
            Color.print({
                {color = "lightred", text = "Workspace "},
                {color = "lightcyan", text = wsname},
                {color = "lightred", text = " doesn't exists\n"}
            }, 2);
        end
    elseif action == "desc" and wsname ~= nil then
        if (parser:root():contains(Types.ComplexAttribute, wsname)) then
            Color.print({
                {color = "lightcyan", text = wsname},
                {color = "white", text = "'s description : "},
                {color = "darkgrey", text = parser:root():at(wsname):getBaseAttribute("description"):get_string() .. "\n"}
            }, 2);
        else
            Color.print({
                {color = "lightred", text = "Workspace "},
                {color = "lightcyan", text = wsname},
                {color = "lightred", text = " doesn't exists\n"}
            }, 2);
        end
    elseif action == "create" and wsname ~= nil then
        os.execute(("mkdir Workspace/" .. wsname):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Data"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Data/Maps"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Data/GameObjects"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Data/GameScripts"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Sprites"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Sprites/GameObjects"):gsub("/", Core.Utils.File.separator()));
        os.execute(("mkdir Workspace/" .. wsname .. "/Sprites/LevelSprites"):gsub("/", Core.Utils.File.separator()));
        parser:root():createComplexAttribute(wsname);
        parser:root():getPath(wsname):createBaseAttribute("path", wsname);
        parser:writeFile("Workspace/Workspaces.vili", true);
        local defaultMount = io.open("Workspace/" .. wsname .. "/Mount.vili", "w")

        defaultMount:write("Include(Obe);\n\n");
        defaultMount:write("Mount:\n");
        defaultMount:write("    " .. wsname .. ":" .. "$Workspace(\"Workspace/" .. wsname .. "\" | 1)\n");
        defaultMount:write("    Root:$Path(\"\" | 0)");
        defaultMount:close()

        Color.print({
            {color = "lightgreen", text = "Workspace "},
            {color = "lightcyan", text = wsname},
            {color = "lightgreen", text = " has been successfully created\n"}
        }, 2);
    else
        Color.print({{color = "lightred", text = "Invalid action / parameters\n"}}, 2);
    end
end

return workspace;