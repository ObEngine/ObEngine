#include <Bindings/NetworkBindings.hpp>
#include <Network/TcpServer.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::NetworkBindings
{
    void LoadTcpServer(kaguya::State* lua)
    {
        (*lua)["obe"]["Network"] = kaguya::NewTable();
        (*lua)["obe"]["Network"]["TcpServer"].setClass(
            kaguya::UserdataMetatable<obe::Network::TcpServer>()
                .setConstructors<
                    Network::TcpServer(int),
                    Network::TcpServer(int, std::string, std::string)
                >()
                .addFunction("setBufferSize", &Network::TcpServer::setBufferSize)
                .addFunction("update", &Network::TcpServer::update)
        );
        /*(*lua)["obe"]["Network"]["TcpServer"]["getClients"] = kaguya::function([](Network::TcpServer* self) {
            std::vector<sf::TcpSocket*> ptrVector;
            for (sf::TcpSocket& client : self->getClients())
            {
                ptrVector.push_back(&client);
            }
            return ptrVector;
        });*/
        System::Path("Lib/Internal/Network.lua").load(System::Loaders::luaLoader, Script::ScriptEngine);
    }
}