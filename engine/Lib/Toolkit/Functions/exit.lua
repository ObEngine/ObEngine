local Commands = require("Lib/Toolkit/Commands");

local function _exit_()
    print("Exiting Toolkit")
    TOOLKIT_CONTEXTS["interactive"] = false;
end

return {
    Commands.call(_exit_);
    Commands.help("Exits the Toolkit Console");
    Commands.context("interactive")
};