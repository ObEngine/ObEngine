-- Dependancies
local String = require("Lib/StdLib/String");
local Table = require("Lib/StdLib/Table");
local Color = require("Lib/StdLib/ConsoleColor");
local inspect = require("Lib/StdLib/Inspect");
local copy = require("Lib/StdLib/Copy");

function loadToolkitFunctions()
    local fileList = Core.Filesystem.getFileList("Lib/Toolkit/Functions");
    local allFunctions = {};
    for _, content in pairs(fileList) do
        allFunctions[String.split(content, ".")[1]] = require("Lib/Toolkit/Functions/" .. String.split(content, ".")[1]);
    end
    return allFunctions;
end

function autocompleteArgs(command, query)
    local path = {};
    local currentWord = "";
    local start = "";
    print("Query : '" .. query .. "'");
    for char in query:gmatch(".") do
        if char == " " then
            table.insert(path, currentWord);
            currentWord = "";
        else
            currentWord = currentWord .. char;
        end
    end
    print("PATH : ", inspect(path));
    print("CW : ", currentWord);
    if currentWord ~= "" then start = currentWord end
    local entries = 0;
    local subpath = {};
    for _, content in pairs(path) do
        if entries ~= 0 then
            table.insert(subpath, content);
        end
        entries = entries + 1;
    end
    table.insert(subpath, start);
    print("SP : ", inspect(subpath));
    if entries > 0 then
        local recurseIn = nil;
        for _, content in pairs(command) do
            if (content.type == "Path" or content.type == "Arg") and content.id == path[1] then
                recurseIn = content;
                break;
            end
        end
        if recurseIn then
            return autocompleteArgs(recurseIn.children, String.join(subpath, " "));
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
                print("FOUND ARG", arg.autocomplete, start);
                if arg.autocomplete then
                    local autocompleteResult = arg.autocomplete(start);
                    for _, content in pairs(autocompleteResult) do
                        if start ~= nil and content:sub(1, string.len(start)) == start then
                            table.insert(arglist, content);
                        elseif start == nil then
                            table.insert(arglist, content);
                        end
                    end
                    print("GOT ACR : ", inspect(arglist));
                end
            end
        end
        return arglist;
    end
end

function excludeNonMatchingWords(baseWord, matchList)
    local newMatchList = {};
    for _, content in pairs(matchList) do
        if #content >= #baseWord then
            if content:sub(0, #baseWord) == baseWord then
                table.insert(newMatchList, content);
            end
        end
    end
    return newMatchList;
end

function getBiggestCommonRoot(baseWord, completionWords)
    local completed = (#completionWords > 0);
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

function autocompleteHandle(ToolkitFunctions, command)
    if #command > 0 then
        local commandName, cargs = decomposeCommand(command);
        if ToolkitFunctions[commandName] then
            local useQuery = String.join(cargs, " ");
            if command:sub(#command, #command) == " " then
                useQuery = useQuery .. " ";
            end
            local completions = autocompleteArgs(ToolkitFunctions[commandName].Routes, useQuery);
            if #completions == 1 then
                while command:sub(#command, #command) ~= " " do
                    command = command:sub(1, -2);
                end
                command = command .. completions[1];
            elseif #completions > 1 then
                while command:sub(#command, #command) ~= " " do
                    command = command:sub(1, -2);
                end
                local commonRoot = getBiggestCommonRoot(getLastArgument(command), completions);
                command = command .. commonRoot;
            end
        end
    end
    return command;
end

ToolkitFunctions = loadToolkitFunctions();

function autocomplete(command)
    local commandName, cargs = decomposeCommand(command);
    _term_last();
    if ToolkitFunctions[commandName] then   
        if #cargs == 0 and command:sub(#command, #command) ~= " " then
            command = command .. " ";
            _term_write(" ");
        end
        local checkCurrentInput = autocompleteHandle(ToolkitFunctions, command);
        if command == checkCurrentInput then
            local completions = autocompleteArgs(ToolkitFunctions[commandName].Routes, String.join(cargs, " "));
            Color.print({text = "> " .. command, color = {0, 128, 128}});
            for _, completion in pairs(completions) do
                Color.print({text = "    > " .. completion, color = {255, 255, 0}});
            end
        else
            _term_clear();
            _term_write(checkCurrentInput);
        end
    else
        local allFunctions = {};
        for key, func in pairs(ToolkitFunctions) do
            table.insert(allFunctions, key);
        end
        local newCurrentInput = getBiggestCommonRoot(command, excludeNonMatchingWords(command, allFunctions));
        if #newCurrentInput ~= #command then
            _term_write(newCurrentInput:sub(#command + 1));
        end
    end
end

function getIdentifiedArgArraySize(idargs)
    local size = 0;
    for _, _ in pairs(idargs) do
        size = size + 1;
    end
    return size;
end

function reachCommand(command, branch, args, idargs)
    local identifiedArgs = idargs or {};
    local entries = 0;
    local subargs = {};
    local nextJump = "";
    for _, content in pairs(args) do
        if entries ~= 0 then
            table.insert(subargs, content);
        else
            nextJump = content;
        end
        entries = entries + 1;
    end
    if nextJump ~= "" then
        local recurseIn = nil;
        for _, content in pairs(branch.children) do
            if content.type == "Path" and content.id == nextJump then
                recurseIn = content;
                identifiedArgs[content.id] = { index = getIdentifiedArgArraySize(identifiedArgs), type = "Path" };
                break;
            end
        end
        if recurseIn == nil then
            for _, content in pairs(branch.children) do
                if content.type == "Arg" then
                    -- ADD TYPE CHECK
                    recurseIn = content;
                    identifiedArgs[content.id] = { index = getIdentifiedArgArraySize(identifiedArgs), type = "Arg" };
                    break;
                end
            end
        end
        if recurseIn then
            return reachCommand(command, recurseIn, subargs, identifiedArgs);
        else
            Color.print({text = "Invalid argument '" .. nextJump .. "'", color = {255, 0, 0}});
        end
    else
        local futureCall = nil;
        for _, content in pairs(branch.children) do
            if content.type == "Call" then
                futureCall = copy(content);
                break;
            end
        end
        if futureCall then
            if futureCall.calltype == "Ref" then
                futureCall.ref = ToolkitFunctions[command].Functions[futureCall.ref];
            end
            return futureCall.ref, identifiedArgs;
        else
            Color.print({text = "Nothing to call with argument '" .. branch.id .. "' in command '" .. command .. "'", color = {255, 0, 0}});
        end
    end
end

function getAtIndex(array, index)
    for key, content in pairs(array) do
        if content.index == index then
            return key;
        end
    end
end

function evaluate(command)
    local commandName, cargs = decomposeCommand(command);
    print("Evaluate : " .. command);
    if ToolkitFunctions[commandName] then
        local callFunction, identifiedArgs = reachCommand(commandName, {id = "{root}", children = ToolkitFunctions[commandName].Routes}, cargs);
        for key, content in pairs(identifiedArgs) do
            if content.type == "Path" then
                identifiedArgs[key].value = getAtIndex(identifiedArgs, content.index + 1);
            elseif content.type == "Arg" then
                identifiedArgs[key].value = cargs[content.index + 1];
            end
        end
        print(inspect(identifiedArgs));
        local ArgMirror = require('Lib/Internal/ArgMirror');
        local argList = ArgMirror.GetArgs(callFunction);
        local callArgs = {};
        for _, arg in pairs(argList) do
            table.insert(callArgs, identifiedArgs[arg].value);
        end
        callFunction(ArgMirror.Unpack(callArgs));
    else
        Color.print({text = "Command '" .. commandName .. "' not found.", color = {255, 0, 0}});
    end
    
end

Color.print({text = "-- ObEngine Toolkit v1.0 --", color = {0, 255, 0}});
