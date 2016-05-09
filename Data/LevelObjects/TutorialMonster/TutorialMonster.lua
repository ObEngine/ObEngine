Octopus = {}

Import("Core.Animation.Animator");
Import("Core.Collision");
Import("Core.MathExp");
Import("Core.Dialog");
Import("Core.LevelSprite");

GetHook("TextDisplay");

UseLocalTrigger("Init");
UseLocalTrigger("Update");

function round(num) 
    if num >= 0 then return math.floor(num+.5) 
    else return math.ceil(num-.5) end
end

function Local.Init()
    This:Animator():setKey("Left");
    xTarget = 0;
    yTarget = 0;
    xPos = 0;
    yPos = 0;
    tSpeed = 0;
    targetReached = true;
    step = 0;
    Hook.TextDisplay:createRenderer("VisualNovel", "VN");
    Hook.TextDisplay:createRenderer("Shade", "SH");
end

function Local.Update(param)
    if step == 0 then
        Hook.TextDisplay:sendToRenderer("VN", {speaker = "Poulpe", text = "Salut !"});
        Hook.TextDisplay:sendToRenderer("VN", {speaker = "Poulpe", text = "Je suis le poulpe qui est censé te faire le tutoriel"});
        Octopus.MoveTo(200, 900, 2);
        step = step + 1;
    elseif step == 1 and not Hook.TextDisplay:textRemaining() then
        print("next step");
        Hook.TextDisplay:sendToRenderer("VN", {speaker = "Poulpe", text = "Premièrement on va apprendre à se déplacer"});
        step = step + 1;
    elseif step == 2 and not Hook.TextDisplay:textRemaining() then
        Hook.TextDisplay:sendToRenderer("SH", {text = "Changement de type de dialogue ! 1"});
        Hook.TextDisplay:sendToRenderer("SH", {text = "Et là encore :) 2"});
        step = step + 1;
    end
    Octopus.UpdateMovement(param.dt)
end

function Octopus.UpdateMovement(dt)
    if not targetReached then
        local xReach = false;
        if xPos > xTarget then
            xPos = xPos - (dt * tSpeed * (xDist / yDist));
        elseif xPos < xTarget then
            xPos = xPos + (dt * tSpeed * (xDist / yDist));
        end
        if yPos > yTarget then
            yPos = yPos - (dt * tSpeed * (yDist / xDist));
        elseif yPos < yTarget then
            yPos = yPos + (dt * tSpeed * (yDist / xDist));
        end
        if round(xPos) == round(xTarget) then
            xPos = xTarget;
            xReach = true;
        end
        if round(yPos) == round(yTarget) then
            yPos = yTarget;
            yReach = true;
        end
        if xReach and yReach then
            targetReached = true;
        end
        This:LevelSprite():setPosition(xPos, yPos);
        This:Collider():setPosition(round(xPos), round(yPos));
    end
end

function Octopus.MoveTo(x, y, speed)
    xTarget = x;
    yTarget = y;
    xDist = math.abs(xPos - xTarget);
    yDist = math.abs(yPos - yTarget);
    tSpeed = speed;
    targetReached = false;
end