local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");

local Functions = {};
function Functions.create(objectName, components)
    components = components:upper();
    local currentWs = Core.Path.Path.Paths()[1]:getPath();
    local haveAnimator = false;
    local haveLevelSprite = false;
    local haveCollider = false;
    local haveScript = false;
    Color.print({ text = "Creating GameObject '" .. objectName .. "' ...", color = {0, 0, 255}}, 1);
    os.execute(("mkdir " .. currentWs .. "/Data/GameObjects/" .. objectName):gsub("/", Core.Filesystem.separator()));
    local objSaveFile = Core.Vili.DataParser.new();
    objSaveFile:root():createComplexAttribute(objectName);
    if (components ~= nil) then
        if (string.find(components, "C") ~= nil) then
            haveCollider = true;
            Color.print({ text = "+ Using component (C)ollider", color = {0, 255, 255}}, 2);
            objSaveFile:root():at(objectName):createComplexAttribute("Collider");
            objCollider = objSaveFile:root():at(objectName .. "/Collider");
            objCollider:createComplexAttribute("unit");
            objCollider:at("unit"):createBaseAttribute("unit", "WorldUnits");
            objCollider:createListAttribute("points");
            objCollider:getListAttribute("points"):push(0);
            objCollider:getListAttribute("points"):push(0);
            objCollider:getListAttribute("points"):push(1);
            objCollider:getListAttribute("points"):push(0);
            objCollider:getListAttribute("points"):push(1);
            objCollider:getListAttribute("points"):push(1);
            objCollider:getListAttribute("points"):push(0);
            objCollider:getListAttribute("points"):push(1);
        end
        if (string.find(components, "A") ~= nil) then
            haveAnimator = true;
            objSaveFile:root():at(objectName):createComplexAttribute("Animator");
            objSaveFile:root():at(objectName .. "/" .. "Animator"):createBaseAttribute("path",
            "Sprites/GameObjects/" .. objectName);
            Color.print({ text = "+ Using component (A)nimator", color = {0, 255, 255}}, 2);
        end
        if (string.find(components, "L") ~= nil) then
            haveLevelSprite = true;
            os.execute(("mkdir " .. currentWs .. "/Sprites/GameObjects/" .. objectName):gsub("/", Core.Filesystem.separator()));
            Color.print({ text = "+ Using component (L)evelSprite", color = {0, 255, 255}}, 2);
            objSaveFile:root():at(objectName):createComplexAttribute("LevelSprite");
            local objLevelSprite = objSaveFile:root():at(objectName .. "/" .. "LevelSprite");
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
        if (string.find(components, "S") ~= nil) then
            haveScript = true;
            local scriptFile = io.open((currentWs .. "/Data/GameObjects/" ..
                objectName .. "/" .. objectName .. ".lua"):gsub("/", Core.Filesystem.separator()), "w");
            scriptFile:write("function Local.Init()\n    print(\"Hello, World!\");\nend");
            scriptFile:close();
            Color.print({ text = "+ Using component (S)cript", color = {0, 255, 255}}, 2);
            objSaveFile:root():at(objectName):createComplexAttribute("Script");
            objSaveFile:root():at(objectName .. "/Script"):createBaseAttribute("priority", 0);
            objSaveFile:root():at(objectName .. "/Script"):createListAttribute("scriptList", "string");
            objSaveFile:root():at(objectName .. "/Script"):getListAttribute("scriptList"):push("Data/GameObjects/" .. 
                objectName .. "/" .. objectName .. ".lua");
        end
    end
    objSaveFile:writeFile((currentWs .. "/Data/GameObjects/" ..
        objectName .. "/" .. objectName .. ".obj.vili"):gsub("/", Core.Filesystem.separator()));
    Color.print({ text = "GameObject '" .. objectName .. "' has been successfully created !", color = {0, 255, 0}}, 1);
end

function Functions.list()
    local allObjects = Core.Path.ListDirInDir("Data/GameObjects");
    for _, key in pairs(allObjects) do 
        Color.print({ text = "- Object : " .. key, color = {0, 255, 255}}, 2);
    end
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with GameObjects");
        Route.Arg("create", {
            Route.Help("Creates a new GameObject");
            Route.Arg("objectName", Route.Types.Any, {
                Route.Arg("components", Route.Types.Any, {
                    Route.Call("create");
                })
            })
        }),
        Route.Arg("list", {
            Route.Help("List all existing GameObjects");
            Route.Call("list");
        });
    }
};