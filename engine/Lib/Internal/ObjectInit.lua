Object = {
    type = __OBJECT_TYPE;
    id = __OBJECT_ID;
};

-- Engine Events
Event = LuaCore.EventNamespaceHooks(Object.type .. "." .. Object.id, "Event");