local Color = require("Lib/StdLib/ConsoleColor");

function alias(argtable)
    local commandName = argtable.command;
    local aliasName = argtable.alias;
    local aliasNotDefined = true;
    for k, v in pairs(Toolkit.commands) do
        for k_sc, v_sc in pairs(v.shortcuts) do
            if v_sc == aliasName then
                aliasNotDefined = false;
                Color.print({{color = "lightred", text = "    Error : Alias or Shortcut \"" .. aliasName .. "\" already exists\n"}});
                break;
            end
        end
    end
    if aliasNotDefined then
        table.insert(Toolkit.commands[commandName].shortcuts, aliasName);
        Color.print({{color = "lightgreen", text = "    Alias \"" .. aliasName .. "\" created with success\n"}});
    end
end

return alias;