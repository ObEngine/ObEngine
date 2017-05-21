-- Dependancies
local String = require("Lib/StdLib/String");
local Table = require("Lib/StdLib/Table");
local Color = require("Lib/StdLib/ConsoleColor");
local inspect = require("Lib/StdLib/inspect");

-- Melting Saga Engine Toolkit
Color.print({{color = "white", text = "ObEngine Toolkit\n"}});
Color.print({{color = "white", text = "Version 1.0.0\n"}});

function loadToolkitFunctions()
    local fileList = Core.Utils.File.listFileInDir("Lib/Toolkit/Functions");
    local allFunctions = {};
    for _, content in pairs(fileList) do
        allFunctions[String.split(content, ".")[1]] = require("Lib/Toolkit/Functions/" .. String.split(content, ".")[1]);
    end
    return allFunctions;
end

function autocompleteCommand(query)
    local currentWord;
    for char in query:gmatch(".") do
        if char == " " then
            return "";
        else
            currentWord = currentWord .. char;
        end
    end
end

function autocomplete(command, query)
    local path = {};
    local currentWord = "";
    for char in query:gmatch(".") do
        if char == " " then
            table.insert(path, currentWord);
            currentWord = "";
        else
            currentWord = currentWord .. char;
        end
    end
    if currentWord ~= "" then start = currentWord end
    local entries = 0;
    local subpath = {};
    for _, content in pairs(path) do
        if entries ~= 0 then
            table.insert(subpath, content);
        end
        entries = entries + 1;
    end
    if entries > 0 then
        local recurseIn = nil;
        for _, content in pairs(command) do
            if (content.type == "Path" or content.type == "Arg") and content.id == path[1] then
                recurseIn = content;
                break;
            end
        end
        if recurseIn then
            return autocomplete(recurseIn.children, string.join(subpath, " "));
        else
            return {};
        end
    else
        local arglist = {};
        for _, arg in pairs(command) do
            if arg.type == "Path" then
                if start ~= nil and string.sub(arg.id, 1, string.len(start)) == start then
                    table.insert(arglist, arg.id);
                elseif start == nil then
                    table.insert(arglist, arg.id);
                end
            elseif arg.type == "Arg" then
                print(arg.autocomplete)
                if arg.autocomplete then
                    local autocompleteResult = arg.autocomplete(start);
                    for _, content in pairs(autocompleteResult) do
                        if start ~= nil and string.sub(content, 1, string.len(start)) == start then
                            table.insert(arglist, content);
                        elseif start == nil then
                            table.insert(arglist, content);
                        end
                    end
                end
            end
        end
        return arglist;
    end
end

function getBiggestCommonRoot(baseWord, completionWords)
    local completed = true;
    local baseLetter = "";
    for index, content in pairs(completionWords) do
        if #content > #baseWord then
            if index == 1 then
                baseLetter = content:sub(#baseWord + 1, #baseWord + 1);
            elseif content:sub(#baseWord + 1, #baseWord + 1) ~= baseLetter then
                completed = false;
                break;
            end
        else
            completed = false;
            break;
        end
    end
    if completed == true then
        return getBiggestCommonRoot(baseWord .. baseLetter, completionWords)
    else
        return baseWord
    end
end

function getLastArgument(command)
  local lastArg = "";
  while command:sub(#command, #command) ~= " " do
    lastArg = command:sub(#command, #command) .. lastArg;
    command = command:sub(1, -2);
  end
  return lastArg;
end

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

function decomposeCommand(command)
    local commandName = "";
    local cargs = {};
    for k, v in pairs(String.split(command, " ")) do
        if k == 1 then
            commandName = v;
        else
            table.insert(cargs, v);
        end
    end
    return commandName, cargs;
end

function autocompleteHandle(ToolkitFunctions, currentInput)
    if #currentInput > 0 then
        local commandName, cargs = decomposeCommand(currentInput);
        if ToolkitFunctions[commandName] then
            local completions = autocomplete(ToolkitFunctions[commandName].Routes, String.join(cargs));
            if #completions == 1 then
                while currentInput:sub(#currentInput, #currentInput) ~= " " do
                    currentInput = currentInput:sub(1, -2);
                    io.write("\b \b");
                end
                currentInput = currentInput .. completions[1];
                io.write(completions[1]);
            elseif #completions > 1 then
                while currentInput:sub(#currentInput, #currentInput) ~= " " do
                    currentInput = currentInput:sub(1, -2);
                    io.write("\b \b");
                end
                local commonRoot = getBiggestCommonRoot(getLastArgument(currentInput), completions);
                currentInput = currentInput .. commonRoot;
                io.write(commonRoot);
            end
        end
    end
    return currentInput;
end

local currentInput = "";
local promptType = "Toolkit";
local continue = true;
local ToolkitFunctions = loadToolkitFunctions();

function toolkitPrompt()
    Color.print({
        {color = "green", text = "OBE"}, 
        {color = "cyan", text = "@"}, 
        {color = "cyan", text = promptType, dark = true}, 
        {color = "white", text = " >> "}
    });
end

toolkitPrompt();

-- Input / Main
while continue do
    local getchInput = _term_getch();
    if getchInput == "CR" then
        if #currentInput > 0 then
            local cargs = {};
            for k, v in pairs(String.split(currentInput, " ")) do
                if String.isNumeric(v) then table.insert(cargs, tonumber(v));
                elseif v == "true" then table.insert(cargs, true);
                elseif v == "false" then table.insert(cargs, false);
                else table.insert(cargs, v);
                end
            end
            print(inspect(cargs));
        end
        currentInput = "";
        toolkitPrompt();
    elseif getchInput == "TAB" then
        local commandName, cargs = decomposeCommand(currentInput);
        if ToolkitFunctions[commandName] then
            local checkCurrentInput = autocompleteHandle(ToolkitFunctions, currentInput);
            if currentInput == checkCurrentInput then
                local completions = autocomplete(ToolkitFunctions[commandName].Routes, String.join(cargs));
                print()
                for _, completion in pairs(completions) do
                    print(" > " .. completion);
                end
                toolkitPrompt();
                io.write(currentInput);
            else
                currentInput = checkCurrentInput;
            end
        else
            
        end
    elseif getchInput == "BS" then
        if #currentInput > 0 then
            currentInput = currentInput:sub(1, -2);
            io.write("\b \b");
        end
    else
        currentInput = currentInput .. getchInput;
        io.write(getchInput);
    end
end