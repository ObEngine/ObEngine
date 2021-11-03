#pragma once

#include <SFML/Network.hpp>

#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>

namespace obe::Network
{
    class TcpServer
    {
    private:
        std::vector<std::unique_ptr<sf::TcpSocket>> m_clients;
        sf::TcpListener m_listener;
        sf::Socket::Status m_status = sf::Socket::Status::Disconnected;
        Event::EventGroupPtr e_server;
        size_t m_maxBufferSize = 4096;
        std::vector<char> m_data;

    public:
        TcpServer(Event::EventNamespace& eventNamespace, unsigned short port,
            std::string triggerNamespace = "", std::string triggerGroup = "");
        void update();
        void setBufferSize(unsigned int maxBufferSize);
        // std::vector<sf::TcpSocket&> getClients();
    };
} // namespace obe::Network
