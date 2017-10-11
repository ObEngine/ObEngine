#include <Network/Network.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe
{
    namespace Network
    {
        NetworkHandler::NetworkHandler() : socketTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Network"))
        {
            listener.setBlocking(false);
            listener.listen(53000);
            client.setBlocking(false);
            socketTriggers->addTrigger("DataReceived")
                          ->addTrigger("Connected")
                          ->addTrigger("Disconnected");
        }

        void NetworkHandler::handleTriggers()
        {
            if (listener.accept(client) == sf::Socket::Done)
            {
                socketTriggers->pushParameter("Connected", "IP", client.getRemoteAddress().toString());
                socketTriggers->trigger("Connected");
                std::cout << "[Network] Client Accepted" << std::endl;
            }
            status = client.receive(data, 100, received);
            if (status == sf::Socket::Done)
            {
                socketTriggers->pushParameter("DataReceived", "Content", std::string(data).substr(0, received));
                socketTriggers->trigger("DataReceived");
            }
            else if (status == sf::Socket::Disconnected)
            {
                socketTriggers->trigger("Disconnected");
            }
        }
    }
}
