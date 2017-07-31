local Color = require("Lib/StdLib/ConsoleColor");
local Route = require("Lib/Toolkit/Route");
local Package = Core.System.Package;

local Functions = {};

function Functions.install(packageName)
    if Core.Package.Package.Install(packageName) then
        Color.print({ text = "Package '" .. packageName .. "' has been successfully installed", color = {0, 255, 0}}, 1);
        local parser = Core.Vili.DataParser.new();
        parser:parseFile("Package/Opaque.vili", true);
        local tPackageName = parser:root():at("Meta"):getBaseAttribute("name"):get_string();
        if parser:hasFlag("Mount") then
            Core.Filesystem.copy(Package.GetPackageLocation(tPackageName) .. "/Mount.vili", "Mount.vili");
        end
    else
        Color.print({ text = "Package '" .. packageName .. "' has not been installed (Already installed ?)", color = {255, 0, 0}}, 1);
    end
end

function Functions.mount(packageName)
    if Package.PackageExists(packageName) then
        Core.Filesystem.copy(Package.GetPackageLocation(packageName) .. "/Mount.vili", "Mount.vili");
        Color.print({ text = "Package '" .. packageName .. "' has been successfully mounted", color = {0, 255, 0}}, 1);
    else
        Color.print({ text = "Package '" .. packageName .. "' does not exists", color = {255, 0, 0}}, 1);
    end
end

return {
    Functions = Functions,
    Routes = {
        Route.Help("Commands to work with Packages");
        Route.Arg("install", {
            Route.Help("Installs a Package");
            Route.Arg("packageName", Route.Types.Any, {
                Route.Call("install");
            }, function() return { "bob", "ana" }; end);
        }),
        Route.Arg("mount", {
            Route.Help("Mount a Package");
            Route.Arg("packageName", Route.Types.Any, {
                Route.Call("mount");
            });
        })
    }
};