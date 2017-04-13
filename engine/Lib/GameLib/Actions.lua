local Actions = {};
Actions.Listener = {};

contains = require("Lib/StdLib/Contains");

function Actions.Listener.ActionPressed(PKeys)
    for key, value in pairs(Actions.Press__Meta.ActionMap) do 
        if (contains(PKeys.PressedActions, key)) then value(); end
    end
end

function Actions.Listener.ActionReleased(RKeys)
    for key, value in pairs(Actions.Release__Meta.ActionMap) do 
        if (contains(RKeys.ReleasedActions, key)) then value(); end
    end
end

function Actions.Listener.ActionToggled(TKeys)
    for key, value in pairs(Actions.Toggle__Meta.ActionMap) do 
        if (contains(TKeys.ToggledActions, key)) then value(); end
    end
end

function Actions.Init(This)
    This:useExternalTrigger("Global", "Keys", "ActionPressed", "Actions.Listener");
    This:useExternalTrigger("Global", "Keys", "ActionReleased", "Actions.Listener");
    This:useExternalTrigger("Global", "Keys", "ActionToggled", "Actions.Listener");
end

Actions.Press = {};
Actions.Press__Meta = {
    ActionMap = {},
    __newindex = function(object, index, value)
        Actions.Press__Meta.ActionMap[index] = value;
    end
};
setmetatable(Actions.Press, Actions.Press__Meta);

Actions.Release = {};
Actions.Release__Meta = {
    ActionMap = {},
    __newindex = function(object, index, value)
        Actions.Release__Meta.ActionMap[index] = value;
    end
};
setmetatable(Actions.Release, Actions.Release__Meta);

Actions.Toggle = {};
Actions.Toggle__Meta = {
    ActionMap = {},
    __newindex = function(object, index, value)
        Actions.Toggle__Meta.ActionMap[index] = value;
    end
};
setmetatable(Actions.Toggle, Actions.Toggle__Meta);

return Actions;