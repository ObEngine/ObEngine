local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Style = require("Lib/Toolkit/Stylesheet");
local Package = Core.System.Package;

local Functions = {};

function getPackageList()
    local parser = Vili.ViliParser.new();
    parser:parseFile("Package/Packages.vili");
    local allPackages = {};
    for _, key in pairs(parser:root():getAll(Vili.NodeType.ComplexNode)) do 
        table.insert(allPackages, key);
    end
    return allPackages;
end

function Functions.install(packageName)
    Color.print({
            { text = "Installing Package <", color = Style.Execute},
            { text = packageName, color = Style.Package},
            { text = "> ...", color = Style.Execute},
        }, 1)
    if Package.Install(packageName) then
        Color.print({
            { text = "Package <", color = Style.Success},
            { text = packageName, color = Style.Package},
            { text = "> has been successfully installed", color = Style.Success}
        }, 2);
        local parser = Vili.ViliParser.new();
        parser:parseFile("Package/Opaque.vili");
        local tPackageName = parser:root():at("Meta"):getDataNode("name"):getString();
        if parser:hasFlag("Mount") then
            Core.Utils.File.copy(Package.GetPackageLocation(tPackageName) .. "/Mount.vili", "Mount.vili");
        end
    else
        Color.print({
            { text = "Package <", color = Style.Error},
            { text = packageName, color = Style.Package},
            { text = "> has not been installed (Already installed ?)", color = Style.Error}
        }, 2);
    end
end

function Functions.mount(packageName)
    Color.print({
        { text = "Mounting Package <", color = Style.Execute},
        { text = packageName, color = Style.Package},
        { text = "> ...", color = Style.Execute},
    }, 1)
    if Package.PackageExists(packageName) then
        Core.Utils.File.copy(Package.GetPackageLocation(packageName) .. "/Mount.vili", "Mount.vili");
        Color.print({
            { text = "Package <", color = Style.Success},
            { text = packageName, color = Style.Package},
            { text = "> has been successfully mounted", color = Style.Success}
        }, 2);
    else
        Color.print({
            { text = "Package <", color = Style.Error},
            { text = packageName, color = Style.Package},
            { text = "> does not exists", color = Style.Error}
        }, 2);
    end
end

function Functions.list()
    local allPackages = getPackageList();
    Color.print({
        { text = "All Registered Packages : ", color = Style.Execute}
    }, 1);
    for _, key in pairs(allPackages) do 
        Color.print({
            { text = "- Package : ", color = Style.Default},
            { text = key, color = Style.Package}
        }, 2);
    end
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with Packages");
        Route.Node("install", {
            Route.Help("Installs a Package");
            Route.Arg("packageName", {
                Route.Help("Name of the .opaque package file you want to install");
                Route.Call("install");
                Route.Autocomplete(function(start)
                    local fileList = Core.Utils.File.getFileList("Package/");
                    local opaqueFiles = {};
                    local extension = ".opaque";
                    for _, file in pairs(fileList) do
                        if file:sub(-extension:len()) == extension then
                            table.insert(opaqueFiles, file:sub(1, #file - #extension));
                        end
                    end
                    return opaqueFiles;
                end)
            });
        }),
        Route.Node("mount", {
            Route.Help("Mount a Package");
            Route.Arg("packageName", {
                Route.Help("Name of the package you want to mount");
                Route.Call("mount");
            });
            Route.Autocomplete(function(start)
                return getPackageList();
            end)
        }),
        Route.Node("list", {
            Route.Help("Lists all Packages");
            Route.Call("list");
        });
    }
};