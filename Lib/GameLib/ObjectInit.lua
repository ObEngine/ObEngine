Local = {}; -- Local Events
Global = {}; -- Global Events
Lua_ReqList = {}; -- Require Parameters

function Require(param)
    if (Lua_ReqList[param] ~= nil) then
        return Lua_ReqList[param];
    else
        error("Can't find requirement : " .. param);
    end
end

function RequireInjection()

end

function IsArgumentInRequireList(paramName)
    if (Lua_ReqList[paramName] ~= nil) then
        return true;
    else
        return false;
    end
end

function Local.Init()
end
function Local.Update()
end
function Local.Collide()
end
function Local.Click()
end
function Local.Delete()
end