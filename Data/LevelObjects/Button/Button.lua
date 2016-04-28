Button = {}

Import("Core.Trigger");
Import("Core.Dialog");
Import("Core.Animation.Animator");

GetHook("TriggerDatabase");
GetHook("TextDisplay");

UseLocalTrigger("Init");
UseLocalTrigger("Click");

function Local.Init()
    selfTrGrp = Hook.TriggerDatabase:createTriggerGroup(Private, "Button")
            :addTrigger("Back");
    UseCustomTrigger(Private, "Button", "Back");
    buttonTrigger = Hook.TriggerDatabase:createTriggerGroup(Public, "Output")
        :addTrigger("On")
        :addTrigger("Off");
    This:Animator():setKey("Off");
    needToWait = false;
end

function Local.Click()
    if not needToWait then
        This:Animator():setKey("On");
        buttonTrigger:enableTrigger("On");
        selfTrGrp:delayTriggerState("Back", 2000, true);
        needToWait = true;
    end
end

function Button.Back()
    This:Animator():setKey("Off");
    buttonTrigger:enableTrigger("Off");
    needToWait = false;
end