function vili.array(t)
    local new_node = vili.node.from_type(vili.node_type.array);
    for _, v in pairs(t) do
        print("Pushing", v);
        new_node:push(vili.node(v));
    end
    return new_node;
end

function vili.object(t)
    local new_node = vili.node.from_type(vili.node_type.object);
    for k, v in pairs(t) do
        new_node:insert(k, vili.node(v));
    end
    return new_node;
end

function vili.from_lua(t)
    return obe.Script.ViliLuaBridge.luaToVili(t);
end

function vili.to_lua(t)
    return obe.Script.ViliLuaBridge.viliToLua(t);
end