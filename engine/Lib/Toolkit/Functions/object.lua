local Color = require("Lib/StdLib/ConsoleColor");

Import("Core.DataParser");

function object(argtable)
    local parser = Core.Vili.DataParser.new();
    parser:parseFile("Workspace/workspace.cfg.msd", true);
    local currentWs = parser:root():at("Workspace"):getBaseAttribute("current"):get_string();
    if (argtable.action == "create") then
        local haveAnimator = false;
        local haveLevelSprite = false;
        local haveCollider = false;
        local haveScript = false;
        os.execute("mkdir Workspace\\" .. currentWs .. "\\Data\\GameObjects\\" .. argtable.objname);
        local objSaveFile = Core.Vili.DataParser.new();
        objSaveFile:root():createComplexAttribute(argtable.objname);
        if (argtable.attributes ~= nil) then
            if (string.find(argtable.attributes, "C") ~= nil) then
                haveCollider = true;
                Color.print({
                    {color = "lightgreen", text = "+ Using component : "},
                    {color = "lightcyan", text = "(C)ollider\n"}
                }, 2);
                objSaveFile:root():at(argtable.objname):createComplexAttribute("Collider");
                objCollider = objSaveFile:root():at(argtable.objname .. "/Collider");
                objCollider:createBaseAttribute("solid", true);
                objCollider:createListAttribute("polygonPoints", "string");
                objCollider:getListAttribute("polygonPoints"):push("0,0");
                objCollider:getListAttribute("polygonPoints"):push("32,0");
                objCollider:getListAttribute("polygonPoints"):push("32,32");
                objCollider:getListAttribute("polygonPoints"):push("0,32");
            end
            if (string.find(argtable.attributes, "A") ~= nil) then
                haveAnimator = true;
                objSaveFile:root():at(argtable.objname):createComplexAttribute("Animator");
                objSaveFile:root():at(argtable.objname .. "/" .. "Animator"):createBaseAttribute("path",
                "Sprites/GameObjects/" .. argtable.objname);
                Color.print({
                    {color = "lightgreen", text = "+ Using component : "},
                    {color = "lightcyan", text = "(A)nimator\n"}
                }, 2);
            end
            if (string.find(argtable.attributes, "L") ~= nil) then
                haveLevelSprite = true;
                os.execute("mkdir Workspace\\" .. currentWs .. "\\Sprites\\GameObjects\\" .. argtable.objname);
                Color.print({
                    {color = "lightgreen", text = "+ Using component : "},
                    {color = "lightcyan", text = "(L)evelSprite\n"}
                }, 2);
                objSaveFile:root():at(argtable.objname):createComplexAttribute("LevelSprite");
                local objLevelSprite = objSaveFile:root():at(argtable.objname .. "/" .. "LevelSprite");
                if (haveCollider) then
                    objLevelSprite:createBaseAttribute("position", "relative");
                else
                    objLevelSprite:createBaseAttribute("position", "absolute");
                end
                objLevelSprite:createBaseAttribute("offsetX", 0);
                objLevelSprite:createBaseAttribute("offsetY", 0);
                objLevelSprite:createBaseAttribute("rotation", 0);
                objLevelSprite:createBaseAttribute("scale", 1.0);
                objLevelSprite:createBaseAttribute("layer", 1);
                objLevelSprite:createBaseAttribute("z-depth", 0);
            end
            if (string.find(argtable.attributes, "S") ~= nil) then
                haveScript = true;
                local scriptFile = io.open("Workspace\\" .. currentWs .. "\\Data\\GameObjects\\" ..
                 argtable.objname .. "\\" .. argtable.objname .. ".lua", "w")
                scriptFile:write("function Local.Init()\n    print(\"Hello World\");\nend")
                scriptFile:close()
                Color.print({
                    {color = "lightgreen", text = "+ Using component : "},
                    {color = "lightcyan", text = "(S)cript\n"}
                }, 2);
                objSaveFile:root():at(argtable.objname):createComplexAttribute("Script");
                objSaveFile:root():at(argtable.objname .. "/Script"):createBaseAttribute("priority", 0);
                objSaveFile:root():at(argtable.objname .. "/Script"):createListAttribute("scriptList", "string");
                objSaveFile:root():at(argtable.objname .. "/Script"):getListAttribute("scriptList"):push("Data/GameObjects/" .. 
                 argtable.objname .. "/" .. argtable.objname .. ".lua");
            end
        end
        objSaveFile:writeFile("Workspace\\" .. currentWs .. "\\Data\\GameObjects\\" ..
         argtable.objname .. "\\" .. argtable.objname .. ".obj.msd");
        Color.print({
            {color = "lightgreen", text = "Object "},
            {color = "lightcyan", text = argtable.objname},
            {color = "lightgreen", text = " has been successfully created\n"}
        }, 2);
    end
end

return object;