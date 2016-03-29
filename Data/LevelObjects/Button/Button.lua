Button = {}

Import("Core.Trigger");
Import("Core.Dialog");

GetHook("TriggerDatabase");
GetHook("TextDisplay");

UseLocalTrigger("Init");
UseLocalTrigger("Click");

function Local.Init()
    selfTrGrp = Hook.TriggerDatabase:createTriggerGroup(Key, "Button")
            :addTrigger("Back");
    UseCustomTrigger(Key, "Button", "Back");
    buttonTrigger = Hook.TriggerDatabase:createTriggerGroup(PKey, "Button")
        :addTrigger("Click");
    This:setAnimationKey("Off");
    needToWait = false;
    pdbait = true;
end

function Local.Click()
    if not needToWait then
        This:setAnimationKey("On");
        buttonTrigger:enableTrigger("Click");
        selfTrGrp:delayTriggerState("Back", 1000, true);
        needToWait = true;
    end
    if pdbait then
        Hook.TextDisplay:appendText("Sygmei", "Bienvenue dans Melting Saga MMO");
        Hook.TextDisplay:appendText("Sygmei", "Veuillez rentrer vos identifiants");
        Hook.TextDisplay:appendText("Sygmei", "E NON EN FAIT C 1 PIEJ");
        Hook.TextDisplay:appendText("Sygmei", "JE T B1 U HOHOHO");
        Hook.TextDisplay:appendText("Sygmei", "VOUALA G INSTALLER PL1 DE VIRUS SUR TON PC");
        pdbait = false;
    end
end

function Button.Back()
    This:setAnimationKey("Off");
    needToWait = false;
end