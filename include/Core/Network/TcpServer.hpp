#pragma once

#include <SFML/Network.hpp>

#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>

namespace obe::network
{
    class TcpServer
    {
    private:
        std::vector<std::unique_ptr<sf::TcpSocket>> m_clients;
        sf::TcpListener m_listener;
        sf::Socket::Status m_status = sf::Socket::Status::Disconnected;
        event::EventGroupPtr e_server;
        size_t m_max_buffer_size = 4096;
        std::vector<char> m_data;

    public:
        TcpServer(event::EventNamespace& event_namespace, unsigned short port);
        void update();
        void setBufferSize(unsigned int max_buffer_size);
        // std::vector<sf::TcpSocket&> getClients();
    };
} // namespace obe::network
