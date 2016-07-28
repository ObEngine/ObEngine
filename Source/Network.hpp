#pragma once

#include <SFML/Network.hpp>

#include "Triggers.hpp"

class NetworkHandler
{
	private:
		sf::TcpSocket client;
		sf::TcpListener listener;
		std::size_t received;
		sf::Socket::Status status;
		char data[4096];
		TriggerGroup* socketTriggers;
	public:
		NetworkHandler();
		void handleTriggers();
};