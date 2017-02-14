-- Dependancies
local String = require("Lib/StdLib/String");
local Table = require("Lib/StdLib/Table");
local Color = require("Lib/StdLib/ConsoleColor");

-- Melting Saga Engine Toolkit
Color.print({{color = "white", text = "Melting Saga Engine Toolkit\n"}});
Color.print({{color = "white", text = "Version 0.0.3-rev032\n"}});

local ToolkitFunctions = require("Lib/Toolkit/Functions");

function getCommandArgsLength(command)
    if command ~= nil then
        local required = 0;
        local total = 0;
        for k, v in pairs(command) do
            if v.optional then total = total + 1;
            else total = total + 1; required = required + 1;
            end
        end
        return {required, total};
    else
        return {0, 0};
    end
end

-- Input / Main
while continue do
    Color.print({{color = "lightgreen", text = "MSE"}, {color = "lightcyan", text = "@"}, {color = "cyan", text = promptType}, {color = "white", text = " >> "}});
    local argv = io.read();
    if #argv > 0 then
        local shortcut = String.split(argv, " ")[1];
        local cargs = {};
        if #argv > 1 then
            for k, v in pairs(String.split(argv, " ")) do
                if k > 1 then
                    if v:sub(0, 1) == "#" then table.insert(cargs, v:sub(1));
                    elseif String.isNumeric(v) then table.insert(cargs, tonumber(v));
                    elseif v == "true" then table.insert(cargs, true);
                    elseif v == "false" then table.insert(cargs, false);
                    else table.insert(cargs, v);
                    end
                end
            end
        end

        local foundCommand = false;
        for k, v in pairs(Toolkit.commands) do
            for k_sc, v_sc in pairs(Toolkit.commands[k].shortcuts) do
                if v_sc == shortcut then
                    foundCommand = true;
                    local correctUsage = true;
                    if not (Table.size(cargs) >= getCommandArgsLength(Toolkit.commands[k].args)[1] and 
                    Table.size(cargs) <= getCommandArgsLength(Toolkit.commands[k].args)[2]) then 
                        correctUsage = false; 
                    end
                    local correctUsageStr = shortcut;
                    local argTable = {};
                    if Toolkit.commands[k].args ~= nil then
                        for carg_i = 1, #Toolkit.commands[k].args, 1 do
                            correctUsageStr = correctUsageStr .. " <" .. Toolkit.commands[k].args[carg_i].type .. ">" .. Toolkit.commands[k].args[carg_i].name;
                            if Toolkit.commands[k].args[carg_i].type ~= type(cargs[carg_i]) and not Toolkit.commands[k].args[carg_i].optional then 
                                correctUsage = false; 
                                Color.print({
                                    {color = "lightred", text = "- "}, 
                                    {color = "lightcyan", text = Toolkit.commands[k].args[carg_i].name}, 
                                    {color = "lightred", text = " is not a " .. type(cargs[carg_i]) .. " (expected " .. Toolkit.commands[k].args[carg_i].type .. ")\n"},
                                }, 1);
                            elseif Toolkit.commands[k].args[carg_i].type ~= type(cargs[carg_i]) then
                                Color.print({
                                    {color = "yellow", text = "- "}, 
                                    {color = "lightcyan", text = Toolkit.commands[k].args[carg_i].name}, 
                                    {color = "yellow", text = " is not a " .. type(cargs[carg_i]) .. " (expected " .. Toolkit.commands[k].args[carg_i].type .. ") [Optional]\n"},
                                }, 1);
                            else 
                                argTable[Toolkit.commands[k].args[carg_i].name] = cargs[carg_i]; 
                            end
                        end
                        if correctUsage then Color.print({{color = "lightmagenta", text = "Command " .. k .. " : \n"}}, 1); Toolkit.functions[k](argTable);
                        else Color.print({{color = "darkgrey", text = "Command usage : " .. correctUsageStr .. "\n"}}, 1);
                        end
                    elseif Table.size(cargs) == 0 then Color.print({{color = "magenta", text = "Command " .. k .. " : \n"}}, 1); Toolkit.functions[k]();
                    else Color.print({{color = "darkgrey", text = "Command usage : " .. shortcut .. "\n"}}, 1);
                    end
                end
            end
        end
        if not foundCommand then
            Color.print({{color = "lightred", text = "Error : Can't find command \"" .. shortcut .. "\"\n"}}, 1);
        end
    end 
end