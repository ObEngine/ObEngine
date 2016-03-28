Import("Core.Trigger");
Import("Core.Console");

GetHook("TriggerDatabase");
GetHook("Console");


UseLocalTrigger("Init");
UseLocalTrigger("Click");

function Local.Init()
    switchStream = Hook.Console:createStream("Switch", true);
    switchMessage = switchStream:write("Interrupteur : Eteint", 100, 100, 100, 255);
    lightTrigger = Hook.TriggerDatabase:createTriggerGroup(PKey, "Switch")
        :addTrigger("On")
        :addTrigger("Off");
    This:setAnimationKey("Off");
    state = false;
end

function Local.Click()
    if (not state) then
        This:setAnimationKey("On");
        lightTrigger:pushParameter("On", "lolz", 3);
        lightTrigger:enableTrigger("On");
        switchMessage:setMessage("Interrupteur : Allume");
        switchMessage:setColor(255, 255, 0, 255);
    else
        This:setAnimationKey("Off");
        lightTrigger:enableTrigger("Off");
        switchMessage:setMessage("Interrupteur : Eteint");
        switchMessage:setColor(100, 100, 100, 255);
    end
    state = not state;
end