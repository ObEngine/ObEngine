Import("Core.Trigger");

GetHook("GameObjectHandler");
GetHook("TriggerDatabase");

Hook.GameObjectHandler:sendRequireArgument("door", "DoorControllerKey", Hook.GameObjectHandler:getGameObject("button"):getPublicKey());