#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include <string>

namespace obe::network
{
    class LuaPacket
    {
    private:
        std::string m_serialized_object;

    public:
    };

    class TcpSocket : public sf::TcpSocket
    {
    public:
    };
} // namespace obe::network
