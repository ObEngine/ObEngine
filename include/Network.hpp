#pragma once

#include <SFML/Network.hpp>

#include "Triggers.hpp"

namespace obe
{
    namespace Network
    {
	    /**
         * \brief Handle the Network Input / Output (Will be remade)
         */
        class NetworkHandler
        {
        private:
            sf::TcpSocket client;
            sf::TcpListener listener;
            size_t received;
            sf::Socket::Status status;
            char data[4096];
            Script::TriggerGroup::Ptr socketTriggers;
        public:
            NetworkHandler();
            void handleTriggers();
        };
    }
}
