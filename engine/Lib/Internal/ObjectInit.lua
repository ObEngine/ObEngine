Object = {
    type = __OBJECT_TYPE;
    id = __OBJECT_ID;
};

LuaCore.ObjectInitInjectionTable = {}; -- Used when Object is built from Editor Menu

function ObjectInit(argtable)
    local argt = argtable or {};
    for k, v in pairs(argt) do
        GameObject:sendInitArg(k, v);
    end
    GameObject:initialize();
    return Object;
end

__PRIVATE_TRIGGERS = LuaCore.MakeTriggerGroupHook(GameObject, Private);
Local = __PRIVATE_TRIGGERS["Local"];
getmetatable(Local).__alias_function = function(namespace, group, id)
    return "Local." .. id;
end

-- Global Triggers
Global = LuaCore.MakeTriggerGroupHook(GameObject, "Global");

function LuaCore.InjectInitInjectionTable()
    for k, v in pairs(LuaCore.ObjectInitInjectionTable) do
        GameObject:sendInitArg(k, v);
    end
end

-- Should not be here
obe.Network.__SERVER_LIST = {};
function obe.Network.Server(port)
    obe.Network.__SERVER_LIST[port] = {};
    local triggerGroupName = "TcpServer_" .. tostring(port);
    obe.Network.__SERVER_LIST[port].server = obe.Network.TcpServer(port, Private, triggerGroupName);
    local triggers = __PRIVATE_TRIGGERS[triggerGroupName];
    obe.Network.__SERVER_LIST[port].triggers = triggers;
    getmetatable(triggers).__alias_function = function(namespace, group, id)
        return "obe.Network.__SERVER_LIST[" .. port .. "].triggers." .. id;
    end
    return triggers;
end