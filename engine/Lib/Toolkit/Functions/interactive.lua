local Commands = require("Lib/Toolkit/Commands");

local function _interactive_()
    print("Entering interactive mode")
    TOOLKIT_CONTEXTS.interactive = true;
end

return {
    Commands.call(_interactive_);
    Commands.help("Enters interactive mode");
    Commands.context("terminal");
};