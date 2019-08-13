--local binser = require("Lib/Extlibs/binser");

--[[function obe.Network.DefaultAcceptClient(self, client)
    self.accept(client);
end

obe.Network.TCPServer = Class("Server", function(self, port)
    self.port = port;
    self.server = obe.Network.InternalServer(port);
    self.server:setBlocking(false, false);
    self.server:listen(obe.Network.DefaultAcceptClient);
    self.hooks = obe.Listen(self.server.privateKey, "Default");
end)

function obe.Network.TCPServer:getHooks(This)
    return self.hooks;
end

function obe.Network.TCPServer:send(...)
    return self.server:send(binser.serialize(...));
end

obe.Network.Client = Class("Server")]]