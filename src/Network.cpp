#include "Network.hpp"

namespace mse
{
	namespace Input
	{
		NetworkHandler::NetworkHandler()
		{
			listener.setBlocking(false);
			listener.listen(53000);
			client.setBlocking(false);
			socketTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Network")
				->addTrigger("DataReceived")
				->addTrigger("Connected")
				->addTrigger("Disconnected");
		}

		void NetworkHandler::handleTriggers()
		{
			if (listener.accept(client) == sf::Socket::Done)
			{
				socketTriggers->pushParameter("Connected", "IP", client.getRemoteAddress().toString());
				socketTriggers->enableTrigger("Connected");
				std::cout << "[Network] Client Accepted" << std::endl;
			}
			status = client.receive(data, 100, received);
			if (status == sf::Socket::Done)
			{
				socketTriggers->pushParameter("DataReceived", "Content", std::string(data).substr(0, received));
				socketTriggers->enableTrigger("DataReceived");
			}
			else if (status == sf::Socket::Disconnected)
			{
				socketTriggers->enableTrigger("Disconnected");
			}
		}
	}
}

