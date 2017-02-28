local AI = {};
AI.Links = {};
AI.States = {};
AI.CurrentState = "";

-- ADD PRIORITIES

AI.State = setmetatable({}, {__newindex = function (table, key, value)
    AI.States[key] = value;
    AI.Links[key] = {};
end});

function AI.Link(from, to, test)
    if from == "*" then
        if AI.States[to] then
            for key, _ in pairs(AI.Links) do
                table.insert(AI.Links[key], {to = to, test = test});
            end
        else 
            print("<Error:AI:AI>[Link] : Link target <" .. to .. "> doesn't exists");
        end
    elseif AI.States[from] and AI.States[to] then
        table.insert(AI.Links[from], {to = to, test = test});
    elseif AI.States[from] then
        print("<Error:AI:AI>[Link] : Link target <" .. to .. "> doesn't exists");
    elseif AI.States[to] then
        print("<Error:AI:AI>[Link] : Link source <" .. from .. "> doesn't exists");
    end
end

function AI.SetState(state)
    if AI.States[state] then
        AI.CurrentState = state;
    else
        print("<Error:AI:AI>[Start] : State <" .. state .. "> doesn't exists");
    end
end

function AI.Update()
    if AI.CurrentState ~= "" then
        for key, value in pairs(AI.Links[AI.CurrentState]) do
            if value.test() then
                AI.CurrentState = value.to;
            end
        end
        AI.States[AI.CurrentState](); -- Execute if just changed ?
    end
end

return AI;