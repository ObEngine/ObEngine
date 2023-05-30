#include <cstddef>
#include <ostream>

#include <cppnet/ip_address.hpp>
#include <cppnet/log.hpp>
#include <cppnet/packet.hpp>
#include <cppnet/udp_socket.hpp>
#include <socket_impl.hpp>

namespace cppnet
{
////////////////////////////////////////////////////////////
UdpSocket::UdpSocket() : Socket(Type::UDP)
{
}


////////////////////////////////////////////////////////////
unsigned short UdpSocket::get_local_port() const
{
    if (get_handle() != priv::SocketImpl::invalid_socket())
    {
        // Retrieve informations about the local end of the socket
        sockaddr_in                  address;
        priv::SocketImpl::AddrLength size = sizeof(address);
        if (getsockname(get_handle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
        {
            return ntohs(address.sin_port);
        }
    }

    // We failed to retrieve the port
    return 0;
}


////////////////////////////////////////////////////////////
Socket::Status UdpSocket::bind(unsigned short port, const IpAddress& address)
{
    // Close the socket if it is already bound
    close();

    // Create the internal socket if it doesn't exist
    create();

    // Check if the address is valid
    if (address == IpAddress::Broadcast)
        return Status::Error;

    // Bind the socket
    sockaddr_in addr = priv::SocketImpl::create_address(address.to_integer(), port);
    if (::bind(get_handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
    {
        err() << "Failed to bind socket to port " << port << std::endl;
        return Status::Error;
    }

    return Status::Done;
}


////////////////////////////////////////////////////////////
void UdpSocket::unbind()
{
    // Simply close the socket
    close();
}


////////////////////////////////////////////////////////////
Socket::Status UdpSocket::send(const void* data, std::size_t size, const IpAddress& remote_address, unsigned short remote_port)
{
    // Create the internal socket if it doesn't exist
    create();

    // Make sure that all the data will fit in one datagram
    if (size > MAX_DATAGRAM_SIZE)
    {
        err() << "Cannot send data over the network "
              << "(the number of bytes to send is greater than cppnet::UdpSocket::MaxDatagramSize)" << std::endl;
        return Status::Error;
    }

    // Build the target address
    sockaddr_in address = priv::SocketImpl::create_address(remote_address.to_integer(), remote_port);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
    // Send the data (unlike TCP, all the data is always sent in one call)
    int sent = static_cast<int>(
        sendto(get_handle(),
               static_cast<const char*>(data),
               static_cast<priv::SocketImpl::Size>(size),
               0,
               reinterpret_cast<sockaddr*>(&address),
               sizeof(address)));
#pragma GCC diagnostic pop

    // Check for errors
    if (sent < 0)
        return priv::SocketImpl::get_error_status();

    return Status::Done;
}


////////////////////////////////////////////////////////////
Socket::Status UdpSocket::receive(void*                     data,
                                  std::size_t               size,
                                  std::size_t&              received,
                                  std::optional<IpAddress>& remote_address,
                                  unsigned short&           remote_port)
{
    // First clear the variables to fill
    received      = 0;
    remote_address = std::nullopt;
    remote_port    = 0;

    // Check the destination buffer
    if (!data)
    {
        err() << "Cannot receive data from the network (the destination buffer is invalid)" << std::endl;
        return Status::Error;
    }

    // Data that will be filled with the other computer's address
    sockaddr_in address = priv::SocketImpl::create_address(INADDR_ANY, 0);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
    // Receive a chunk of bytes
    priv::SocketImpl::AddrLength address_size  = sizeof(address);
    int                          size_received = static_cast<int>(
        recvfrom(get_handle(),
                 static_cast<char*>(data),
                 static_cast<priv::SocketImpl::Size>(size),
                 0,
                 reinterpret_cast<sockaddr*>(&address),
                 &address_size));
#pragma GCC diagnostic pop

    // Check for errors
    if (size_received < 0)
        return priv::SocketImpl::get_error_status();

    // Fill the sender informations
    received      = static_cast<std::size_t>(size_received);
    remote_address = IpAddress(ntohl(address.sin_addr.s_addr));
    remote_port    = ntohs(address.sin_port);

    return Status::Done;
}


////////////////////////////////////////////////////////////
Socket::Status UdpSocket::send(Packet& packet, const IpAddress& remote_address, unsigned short remote_port)
{
    // UDP is a datagram-oriented protocol (as opposed to TCP which is a stream protocol).
    // Sending one datagram is almost safe: it may be lost but if it's received, then its data
    // is guaranteed to be ok. However, splitting a packet into multiple datagrams would be highly
    // unreliable, since datagrams may be reordered, dropped or mixed between different sources.
    // That's why CppNet imposes a limit on packet size so that they can be sent in a single datagram.
    // This also removes the overhead associated to packets -- there's no size to send in addition
    // to the packet's data.

    // Get the data to send from the packet
    std::size_t size = 0;
    const void* data = packet.on_send(size);

    // Send it
    return send(data, size, remote_address, remote_port);
}


////////////////////////////////////////////////////////////
Socket::Status UdpSocket::receive(Packet& packet, std::optional<IpAddress>& remote_address, unsigned short& remote_port)
{
    // See the detailed comment in send(Packet) above.

    // Receive the datagram
    std::size_t received = 0;
    Status      status   = receive(m_buffer.data(), m_buffer.size(), received, remote_address, remote_port);

    // If we received valid data, we can copy it to the user packet
    packet.clear();
    if ((status == Status::Done) && (received > 0))
        packet.on_receive(m_buffer.data(), received);

    return status;
}


} // namespace cppnet
