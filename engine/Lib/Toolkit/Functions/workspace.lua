local Color = require("Lib/StdLib/ConsoleColor");

function workspace(argtable)
    local action = argtable.action;
    local wsname = argtable.wsname;
    local parser = Core.Vili.DataParser.new();
    local Types = Core.Vili.AttributeType;
    parser:parseFile("Workspace/workspace.cfg.msd", true);
    if action == "get" then
        local currentWs = parser:root():at("Workspace"):getBaseAttribute("current"):get_string();
        Color.print({
            {color = "white", text = "Current Workspace : "}, 
            {color = "lightcyan", text = currentWs .. "\n"}
        }, 2);
    elseif action == "use" and wsname ~= nil then
        if (parser:root():contains(Types.ComplexAttribute, "Workspace", wsname)) then
            parser:root():at("Workspace"):getBaseAttribute("current"):set(wsname);
            parser:writeFile("Workspace/workspace.cfg.msd", true);
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
        if (parser:root():at("Workspace"):contains(Types.ComplexAttribute, wsname)) then
            Color.print({
                {color = "lightcyan", text = wsname},
                {color = "white", text = "'s description : "},
                {color = "darkgrey", text = parser:root():at("Workspace/" .. wsname):getBaseAttribute("description"):get_string() .. "\n"}
            }, 2);
        else
            Color.print({
                {color = "lightred", text = "Workspace "},
                {color = "lightcyan", text = wsname},
                {color = "lightred", text = " doesn't exists\n"}
            }, 2);
        end
    elseif action == "create" and wsname ~= nil then
        os.execute("mkdir Workspace\\" .. wsname);
        os.execute("mkdir Workspace\\" .. wsname .. "\\Data");
        os.execute("mkdir Workspace\\" .. wsname .. "\\Data\\Maps");
        os.execute("mkdir Workspace\\" .. wsname .. "\\Data\\GameObjects");
        os.execute("mkdir Workspace\\" .. wsname .. "\\Data\\GameScripts");
        os.execute("mkdir Workspace\\" .. wsname .. "\\Sprites");
        os.execute("mkdir Workspace\\" .. wsname .. "\\Sprites\\GameObjects");
        os.execute("mkdir Workspace\\" .. wsname .. "\\Sprites\\LevelSprites");
        parser:root():at("Workspace"):createComplexAttribute(wsname);
        parser:root():getPath("Workspace/" .. wsname):createBaseAttribute("path", wsname);
        parser:writeFile("Workspace/workspace.cfg.msd", true);
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