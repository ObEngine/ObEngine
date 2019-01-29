local binser = require("Lib/Extlibs/binser");

obe.Network.TCPServer = Class("Server", function(self, port)
    self.port = port;
    self.server = obe.Network.InternalServer(port);
    self.server:setBlocking(false, false);
    self.server:listen();
    self.hooks = obe.Triggers.Listen(self.server, obe.Triggers.DefaultGroup);
    self.hooks.OnConnect = function(client)
        return true;
    end
end)

function obe.Network.TCPServer:getHooks(This)
    return self.hooks;
end

function obe.Network.TCPServer:send(...)
    return self.server:send(binser.serialize(...));
end

obe.Network.Client = Class("Server")