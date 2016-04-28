Enemy = {}

Import("Core.Animation.Animator");
Import("Core.Collision");
Import("Core.MathExp");
Import("Core.LevelSprite");

UseLocalTrigger("Init");
UseLocalTrigger("Update");

function Local.Init()
    This:Animator():setKey("Left");
    xMovement = Core.MathExp.MathExp.new("cos@(t/10) * 250 + 550");
    xMovement:buildMathExp();
    yMovement = Core.MathExp.MathExp.new("cos@(t) * 30 + 750");
    yMovement:buildMathExp();
    dMovement = Core.MathExp.MathExp.new("cos@(t/10)");
    dMovement:buildMathExp();
    t = 0;
end

function Local.Update(param)
    This:LevelSprite():setPosition(xMovement:getResult(), yMovement:getResult());
    This:Collider():setPosition(math.floor(xMovement:getResult()), math.floor(yMovement:getResult()));
    t = t + (param.dt / 10);
    xMovement:setVar("t", t);
    yMovement:setVar("t", t);
    dMovement:setVar("t", t);
    if dMovement:getResult() < -0.99 then
        This:Animator():setKey("Right");
    elseif dMovement:getResult() > 0.99 then
        This:Animator():setKey("Left");
    end
end