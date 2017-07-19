#pragma once

#include <SFML/Network.hpp>

#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Network
    {
        /**
         * \brief Handle the Network input / output (Will be remade)
         */
        class NetworkHandler
        {
        private:
            sf::TcpSocket client;
            sf::TcpListener listener;
            size_t received;
            sf::Socket::Status status;
            char data[4096];
            Triggers::TriggerGroupPtr socketTriggers;
        public:
            NetworkHandler();
            void handleTriggers();
        };
    }
}
