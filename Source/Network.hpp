#pragma once

#include <SFML/Network.hpp>

#include "Triggers.hpp"

namespace mse
{
	namespace Input
	{
		class NetworkHandler
		{
			private:
				sf::TcpSocket client;
				sf::TcpListener listener;
				std::size_t received;
				sf::Socket::Status status;
				char data[4096];
				Script::TriggerGroup* socketTriggers;
			public:
				NetworkHandler();
				void handleTriggers();
		};
	}
}

