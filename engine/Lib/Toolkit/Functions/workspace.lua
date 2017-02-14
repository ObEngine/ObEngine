local Color = require("Lib/StdLib/ConsoleColor");

Import("Core.DataParser");

function workspace(argtable)
    local action = argtable.action;
    local wsname = argtable.wsname;
    local parser = Core.DataParser.DataParser.new();
    parser:parseFile("Workspace/workspace.cfg.msd", true);
    if action == "get" then
        local currentWs = parser:getBaseAttribute("Workspace", "current"):get_string();
        Color.print({
            {color = "white", text = "Current Workspace : "}, 
            {color = "cyan", text = currentWs .. "\n"}
        }, 2);
    elseif action == "use" and wsname ~= nil then
        if (parser:containsComplexAttribute("Workspace", wsname)) then
            parser:getBaseAttribute("Workspace", "current"):set(wsname);
            parser:writeFile("Workspace/workspace.cfg.msd", true);
            Color.print({
                {color = "green", text = "Current workspace has been successfully switched to "},
                {color = "cyan", text = wsname .. "\n"}
            }, 2);
        else
            Color.print({
                {color = "red", text = "Workspace "},
                {color = "cyan", text = wsname},
                {color = "red", text = " doesn't exists\n"}
            }, 2);
        end
    elseif action == "desc" and wsname ~= nil then
        if (parser:containsComplexAttribute("Workspace", wsname)) then
            Color.print({
                {color = "cyan", text = wsname},
                {color = "white", text = "'s description : "},
                {color = "grey", text = parser:getBaseAttribute("Workspace/" .. wsname, "description"):get_string() .. "\n"}
            }, 2);
        else
            Color.print({
                {color = "red", text = "Workspace "},
                {color = "cyan", text = wsname},
                {color = "red", text = " doesn't exists\n"}
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
        parser:createComplexAttribute("Workspace", wsname);
        parser:getPath("Workspace/" .. wsname):createBaseAttribute("path", wsname);
        parser:writeFile("Workspace/workspace.cfg.msd", true);
        Color.print({
            {color = "green", text = "Workspace "},
            {color = "cyan", text = wsname},
            {color = "green", text = " has been successfully created\n"}
        }, 2);
    else
        Color.print({{color = "red", text = "Invalid action / parameters\n"}}, 2);
    end
end

return workspace;