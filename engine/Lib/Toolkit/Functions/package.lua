local Color = require("Lib/StdLib/ConsoleColor");

function package(argtable)
    local action = argtable.action;
    local packageName = argtable.pkgname;
    if action == "install" then
        if Core.Package.Package.Install(packageName) then
            Color.print({
                {color = "white", text = "Package <"},
                {color = "lightgreen", text = packageName},
                {color = "white", text = "> has been successfully installed\n"},
            }, 2);
            local parser = Core.Vili.DataParser.new();
            parser:parseFile("Package/Opaque.vili", true);
            local tPackageName = parser:root():at("Meta"):getBaseAttribute("name"):get_string();
            if parser:hasFlag("Mount") then
                repeat
                    print("The package asks the <Mount> permission, do you want to allow it ? (Y/N)");
                    answer = io.read()
                until answer == "y" or answer == "n" or answer == "Y" or answer == "N"
                if answer == "Y" or answer == "y" then
                    Core.Utils.File.copy("Package/" .. tPackageName .. "/Mount.vili", "Mount.vili");
                end
            end
        else
            Color.print({
                {color = "red", text = "Package <"},
                {color = "lightgreen", text = packageName},
                {color = "red", text = "> has not been installed (Already installed ?)\n"},
            }, 2);
        end
    end
end

return package;