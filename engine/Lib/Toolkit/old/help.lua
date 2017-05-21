local Color = require("Lib/StdLib/ConsoleColor");

function help()
    for k, v in pairs(Toolkit.commands) do
        local f_desc = {};
        table.insert(f_desc, {color = "grey", text = "    - Command : " .. k});
        if Toolkit.commands[k].args ~= nil then
            for k_com, v_com in pairs(Toolkit.commands[k].args) do
                table.insert(f_desc, {color = "lightgrey", text = " <"});
                table.insert(f_desc, {color = "yellow", text = v_com.type});
                table.insert(f_desc, {color = "lightgrey", text = ">" .. v_com.name});
            end
        end
        table.insert(f_desc, {color = "white", text = "\n"});
        Color.print(f_desc);
    end
end

return help;