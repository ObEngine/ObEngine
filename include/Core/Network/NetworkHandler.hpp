#pragma once

#include <SFML/Network.hpp>

#include <Triggers/TriggerGroup.hpp>

namespace obe::Network
{
    /**
     * \brief Handle the Network input / output (Will be remade)
     */
    class NetworkHandler
    {
    private:
        sf::TcpSocket m_client;
        sf::TcpListener m_listener;
        size_t m_received;
        sf::Socket::Status m_status;
        char m_data[4096];
        Triggers::TriggerGroupPtr m_socketTriggers;

    public:
        NetworkHandler();
        void handleTriggers();
    };
} // namespace obe::Network