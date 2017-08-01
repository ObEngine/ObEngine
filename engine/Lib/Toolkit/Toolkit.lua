-- Dependancies
local String = require("Lib/StdLib/String");
local Table = require("Lib/StdLib/Table");
local Color = require("Lib/StdLib/ConsoleColor");
local inspect = require("Lib/StdLib/Inspect");
local copy = require("Lib/StdLib/Copy");
local Style = require("Lib/Toolkit/Stylesheet");

function loadToolkitFunctions()
    local fileList = Core.Utils.File.getFileList("Lib/Toolkit/Functions");
    local allFunctions = {};
    for _, content in pairs(fileList) do
        allFunctions[String.split(content, ".")[1]] = require("Lib/Toolkit/Functions/" .. String.split(content, ".")[1]);
    end
    return allFunctions;
end

function askForCompletion(command)
    Color.print({
        {text = "> ", color = Style.CompletionPrompt.Prompt},
        {text = command, color = Style.CompletionPrompt.Text},
        {text = " ...", color = Style.CompletionPrompt.TripleDot}
    });
end

function autocompleteArgs(command, query)
    print("AUTOCOMPLETE ARGS CALLED");
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
    print("CURRENTWORD : ", currentWord);
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
    print("SUBPATH : ", inspect(subpath));
    print("Entries : ", entries);
    if entries > 0 then
        local recurseIn = nil;
        for _, content in pairs(command) do
            if content.type == "Node" and content.id == path[1] then
                recurseIn = content;
                break;
            elseif content.type == "Argument" then
                recurseIn = content;
            end
        end
        if recurseIn then
            print("RECURSION")
            return autocompleteArgs(recurseIn.children, String.join(subpath, " "));
        else
            print("NOT FOUND HURR DURR");
            return {};
        end
    else
        print("Start inspection in ", inspect(command))
        local arglist = {};
        for _, arg in pairs(command) do
            if arg.type == "Node" then
                if start ~= nil and string.sub(arg.id, 1, string.len(start)) == start then
                    arglist[arg.id] = arg;
                elseif start == nil then
                    arglist[arg.id] = arg;
                end
            elseif arg.type == "Argument" then
                print("FOUND ARG", arg.autocomplete, start);
                local autocompleteFunction;
                for _, searchFunction in pairs(arg.children) do
                    if searchFunction.type == "Autocomplete" then
                        print("FOUND AUTOCOMPLETE FUNCTION");
                        autocompleteFunction = searchFunction.ref;
                        break;
                    end
                end
                if autocompleteFunction then
                    local autocompleteResult = autocompleteFunction(start);
                    for _, content in pairs(autocompleteResult) do
                        if start ~= nil and content:sub(1, string.len(start)) == start then
                            -- Add help ?
                            arglist[content] = { children = {{ type = "Help", help = "Argument suggestion for <" .. arg.id .. "> parameter" }}};
                        elseif start == nil then
                            -- Add help ?
                            arglist[content] = { children = {{ type = "Help", help = "Argument suggestion for <" .. arg.id .. "> parameter" }}};
                        end
                    end
                    print("GOT ACR : ", inspect(arglist));
                else
                    local defaultHelp = "Variable for argument <" .. arg.id .. ">";
                    print("Arg inspect : ", inspect(arg));
                    print("Help Got : ", getHelp(arg.children))
                    if getHelp(arg.children) ~= "" then
                        defaultHelp = getHelp(arg.children);
                    end
                    arglist["<" .. arg.id .. ">"] = { children = {{ type = "Help", help = defaultHelp }}};
                end
            end
        end
        return arglist;
    end
end

-- Returns a table with only the elements from matchList that starts like baseWord
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

function getTableSize(mtable)
    local size = 0;
    for _, v in pairs(mtable) do
        size = size + 1;
    end
    return size;
end

function getTableKeys(mtable)
    local keys = {};
    for k, v in pairs(mtable) do
        table.insert(keys, k);
    end
    return keys;
end

function autocompleteHandle(ToolkitFunctions, command)
    print("AUTOCOMPLETE HANDLE CALLED")
    if #command > 0 then
        local commandName, cargs = decomposeCommand(command);
        if ToolkitFunctions[commandName] then
            local useQuery = String.join(cargs, " ");
            if command:sub(#command, #command) == " " then
                useQuery = useQuery .. " ";
            end
            print("Use Query : <" .. useQuery .. ">");
            local completions = autocompleteArgs(ToolkitFunctions[commandName].Routes, useQuery);
            if getTableSize(completions) == 1 then
                -- Only one completion found, complete and add space (if not a variable)
                local onlyCompletion = getTableKeys(completions)[1];
                if onlyCompletion:sub(1, 1) == "<" and onlyCompletion:sub(#onlyCompletion, #onlyCompletion) == ">" then
                    -- Variable Parameter, do nothing
                else
                    while command:sub(#command, #command) ~= " " do
                        command = command:sub(1, -2);
                    end
                    command = command .. getTableKeys(completions)[1] .. " ";
                end
            elseif getTableSize(completions) > 1 then
                -- Multiple completions found, completing with biggest common root
                while command:sub(#command, #command) ~= " " do
                    command = command:sub(1, -2);
                end
                local commonRoot = getBiggestCommonRoot(getLastArgument(command), getTableKeys(completions));
                command = command .. commonRoot;
            end
        end
    end
    return command;
end

function isUniqueValidCommand(command, commandName)
    local obfuscatedCommand = 0;
    for key, func in pairs(ToolkitFunctions) do
        if key:sub(0, #command) == commandName then
            obfuscatedCommand = obfuscatedCommand + 1;
        end
    end
    return obfuscatedCommand == 1;
end

function getHelp(arg)
    for _, child in pairs(arg) do
        if child.type == "Help" then
            return child.help;
        end
    end
    return "";
end

function autocomplete(command)
    print("AUTOCOMPLETE CALLED --------------------------------------------")
    local commandName, cargs = decomposeCommand(command);
    _term_last();
    if ToolkitFunctions[commandName] then
        if isUniqueValidCommand(command, commandName) then
            -- Adding a space when command is valid
            if #cargs == 0 and command:sub(#command, #command) ~= " " then
                command = command .. " ";
                _term_write(" ");
            end
            local checkCurrentInput = autocompleteHandle(ToolkitFunctions, command);
            print("Check Current Input : '" .. checkCurrentInput .. "'")
            if command == checkCurrentInput then
                local addSpace = "";
                if command:sub(#command, #command) == " " and #cargs > 0 then
                    addSpace = " ";
                end
                local completions = autocompleteArgs(ToolkitFunctions[commandName].Routes, String.join(cargs, " ") .. addSpace);
                if getTableSize(completions) == 1 and getTableKeys(completions)[1] == getLastArgument(command) then
                    command = command .. " ";
                    _term_write(" ");
                else
                    askForCompletion(command);
                    for compId, completion in pairs(completions) do
                        Color.print({
                            {text = "> ", color = Style.Default},
                            {text = compId, color = Style.Argument},
                            {text = " : ", color = Style.Default},
                            {text = getHelp(completion.children), color = Style.Help}
                        }, 2);
                    end
                end
                print("Completions gathered");
            else
                _term_clear();
                _term_write(checkCurrentInput);
            end
        else
            -- When commands overlaps
            askForCompletion(command);
            for key, func in pairs(ToolkitFunctions) do
                if key:sub(0, #command) == command then
                    Color.print({
                        {text = "> ", color = Style.Default},
                        {text = key, color = Style.Command},
                        {text = " : ", color = Style.Default},
                        {text = getHelp(func.Routes), color = Style.Help}
                    }, 2);
                end
            end
        end
    else
        local allFunctions = {};
        for key, func in pairs(ToolkitFunctions) do
            table.insert(allFunctions, key);
        end
        local newCurrentInput = getBiggestCommonRoot(command, excludeNonMatchingWords(command, allFunctions));
        print("NCI : ", newCurrentInput)
        if #newCurrentInput ~= #command then
            _term_write(newCurrentInput:sub(#command + 1));
            if isUniqueValidCommand(command, commandName) then
                _term_write(" ");
            end
        else
            askForCompletion(command);
            for key, func in pairs(ToolkitFunctions) do
                if key:sub(0, #command) == command then
                    Color.print({
                        {text = "> ", color = Style.Default},
                        {text = key, color = Style.Command},
                        {text = " : ", color = Style.Default},
                        {text = getHelp(func.Routes), color = Style.Help}
                    }, 2);
                end
            end
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
    print("Reach Command : ", command, inspect(branch), inspect(args), inspect(idargs));
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
    print("Next JUmp", nextJump);
    if nextJump ~= "" then
        local recurseIn = nil;
        for _, content in pairs(branch.children) do
            if content.type == "Node" and content.id == nextJump then
                recurseIn = content;
                identifiedArgs[content.id] = { index = getIdentifiedArgArraySize(identifiedArgs), type = "Node" };
                break;
            end
        end
        if recurseIn == nil then
            for _, content in pairs(branch.children) do
                if content.type == "Argument" then
                    -- ADD TYPE CHECK
                    recurseIn = content;
                    identifiedArgs[content.id] = { index = getIdentifiedArgArraySize(identifiedArgs), type = "Argument" };
                    break;
                end
            end
        end
        if recurseIn then
            return reachCommand(command, recurseIn, subargs, identifiedArgs);
        else
            -- Invalid Argument
            Color.print({
                {text = "Invalid argument ", color = Style.Error},
                {text = nextJump, color = Style.Argument}
            }, 2);
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
            -- No callable function found
            Color.print({
                {text = "Nothing to call with argument ", color = Style.Error},
                {text = branch.id, color = Style.Argument},
                {text = " in command ", color = Style.Error},
                {text = command, color = Style.Command}
            }, 2);
            return nil, nil
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
        print("===========> COMMAND", inspect(ToolkitFunctions[commandName]));
        -- Command found
        print("Cargs is ", cargs);
        local callFunction, identifiedArgs = reachCommand(commandName, {id = "{root}", children = ToolkitFunctions[commandName].Routes}, cargs);
        if callFunction and identifiedArgs then
            -- Successful Reach Command Call
            for key, content in pairs(identifiedArgs) do
                if content.type == "Node" then
                    identifiedArgs[key].value = getAtIndex(identifiedArgs, content.index + 1);
                elseif content.type == "Argument" then
                    identifiedArgs[key].value = cargs[content.index + 1];
                end
            end
            local ArgMirror = require('Lib/Internal/ArgMirror');
            local argList = ArgMirror.GetArgs(callFunction);
            local callArgs = {};
            for _, arg in pairs(argList) do
                table.insert(callArgs, identifiedArgs[arg].value);
            end
            callFunction(ArgMirror.Unpack(callArgs));
        end
    else
        -- Command not found
        Color.print({
            {text = "Command ", color = Style.Error},
            {text = commandName, color = Style.Command},
            {text = " not found.", color = Style.Error}
        }, 2);
    end
    
end

ToolkitFunctions = loadToolkitFunctions();
Color.print({
    {text = "@", color = Style.Boot.At},
    {text = "ObEngine Toolkit ", color = Style.Boot.Text},
    {text = " (v1.0)", color = Style.Boot.Version}
});
