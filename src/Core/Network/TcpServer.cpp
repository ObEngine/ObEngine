#include <Debug/Logger.hpp>
#include <Network/TcpServer.hpp>

namespace obe::network
{
    TcpServer::TcpServer(event::EventNamespace& event_namespace, unsigned short port)
    {
        /*if (!event_namespace.empty())
        {
            m_socketTriggers
                = triggers.createTriggerGroup(event_namespace, event_group);
            m_socketTriggers->add("DataReceived").add("Connected").add("Disconnected");
        }
        m_listener.setBlocking(false);
        m_listener.listen(port);

        m_clients.push_back(std::make_unique<sf::TcpSocket>());
        m_data.resize(m_max_buffer_size);*/
    }

    void TcpServer::update()
    {
        /*if (m_listener.accept(*m_clients.back()) == sf::Socket::Done)
        {
            if (m_socketTriggers)
            {
                m_socketTriggers->pushParameter(
                    "Connected", "client", m_clients.back().get());
                m_socketTriggers->pushParameter(
                    "Connected", "ip", m_clients.back()->getRemoteAddress().toString());
                m_socketTriggers->trigger("Connected");
            }
            debug::Log->debug("<TcpServer> New client connected to server "
                              "listening at port {}",
                m_listener.getLocalPort());
            m_clients.push_back(std::make_unique<sf::TcpSocket>());
        }
        for (auto& client : m_clients)
        {
            std::size_t receivedDataSize = 0;
            m_status = client->receive(m_data.data(), m_max_buffer_size, receivedDataSize);
            if (m_status == sf::Socket::Done)
            {
                if (m_socketTriggers)
                {
                    m_socketTriggers->pushParameter("DataReceived", "content",
                        std::string(m_data.begin(), m_data.end())
                            .substr(0, receivedDataSize));
                    m_socketTriggers->pushParameter(
                        "DataReceived", "client", client.get());
                    m_socketTriggers->trigger("DataReceived");
                }
            }
            else if (m_status == sf::Socket::Disconnected)
            {
                if (m_socketTriggers)
                {
                    m_socketTriggers->trigger("Disconnected");
                }
            }
        }*/
    }

    void TcpServer::setBufferSize(unsigned int max_buffer_size)
    {
        m_max_buffer_size = max_buffer_size;
        m_data.resize(m_max_buffer_size);
    }

    /*std::vector<sf::TcpSocket&> TcpServer::getClients()
    {
        std::vector<sf::TcpSocket&> clientReferences;
        for (auto& client : m_clients)
        {
            clientReferences.push_back(*client.get());
        }
        return clientReferences;
    }*/
} // namespace obe::network
