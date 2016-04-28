Keys = {}

Import("Core.MathExp");
Import("Core.Console");

GetHook("Console");

UseLocalTrigger("Init");

function Local.Init()
    switchStream = Hook.Console:createStream("Calculator", true);
    expr = "";
    UseCustomTrigger("Map", "Keys", "Click", "Keys");
    mathexp = Core.MathExp.MathExp.new("", true);
    print("Calculator Initialised");
end

function Keys.Click(parameters)
    print("Recv Key : ", parameters.KeyNum);
    if parameters.KeyNum == "C" then
        expr = "";
    elseif parameters.KeyNum == "V" then
        mathexp:setExpr(expr);
        mathexp:buildMathExp();
        switchStream:write(expr .. " = " .. tostring(mathexp:getResult()), 0, 255, 0, 255);
        expr = "";
    else
        expr = expr .. parameters.KeyNum;
    end
end