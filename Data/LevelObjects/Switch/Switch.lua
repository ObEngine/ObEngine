Import("Core.Trigger");
Import("Core.Console");
Import("Core.Animation.Animator");

GetHook("TriggerDatabase");
GetHook("Console");


UseLocalTrigger("Init");
UseLocalTrigger("Click");

function Local.Init()
    switchStream = Hook.Console:createStream("Switch", true);
    switchMessage = switchStream:write("Interrupteur : Eteint", 100, 100, 100, 255);
    lightTrigger = Hook.TriggerDatabase:createTriggerGroup(Public, "Switch")
        :addTrigger("On")
        :addTrigger("Off");
    This:Animator():setKey("Off");
    state = false;
end

function Local.Click()
    if (not state) then
        This:Animator():setKey("On");
        lightTrigger:pushParameter("On", "lolz", {one = 1.1, two = 2.2, three = 3.3});
        lightTrigger:enableTrigger("On");
        switchMessage:setMessage("Interrupteur : Allume");
        switchMessage:setColor(255, 255, 0, 255);
    else
        This:Animator():setKey("Off");
        lightTrigger:enableTrigger("Off");
        switchMessage:setMessage("Interrupteur : Eteint");
        switchMessage:setColor(100, 100, 100, 255);
    end
    state = not state;
end