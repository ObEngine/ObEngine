-- Toolkit
Toolkit = {};
Toolkit.commands = {};
Toolkit.functions = {};

-- Globals
continue = true;
reload = true;
promptType = "Toolkit";

-- Commands Definition
Toolkit.commands.exit = {
    shortcuts = {"q", "quit", "exit"}
};
Toolkit.commands.help = {
    shortcuts = {"h", "help", "?"}
};
Toolkit.commands.object = {
    shortcuts = {"o", "obj", "object"},
    args = {
        {name = "action", type = "string"},
        {name = "objname", type = "string", optional = true},
        {name = "attributes", type = "string", optional = true}
    }
}
Toolkit.commands.package = {
    shortcuts = {"p", "pkg", "package"}, 
    args = {
        {name = "action", type = "string"},
        {name = "pkgname", type = "string"}
    }
};
Toolkit.commands.reload = {
    shortcuts = {"r", "reload"}, 
};
Toolkit.commands.workspace = {
    shortcuts = {"w", "ws", "workspace"},
    args = {
        {name = "action", type = "string"},
        {name = "wsname", type = "string", optional = true}
    }
};

-- Functions loading
for k, v in pairs(Toolkit.commands) do
    Toolkit.functions[k] = require("Lib/Toolkit/Functions/" .. k);
end

return Toolkit;