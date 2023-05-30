#include <ostream>

#include <cppnet/log.hpp>
#include <cppnet/tcp_listener.hpp>
#include <cppnet/tcp_socket.hpp>
#include <socket_impl.hpp>

namespace cppnet
{
////////////////////////////////////////////////////////////
TcpListener::TcpListener() : Socket(Type::TCP)
{
}


////////////////////////////////////////////////////////////
unsigned short TcpListener::get_local_port() const
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
Socket::Status TcpListener::listen(unsigned short port, const IpAddress& address)
{
    // Close the socket if it is already bound
    close();

    // Create the internal socket if it doesn't exist
    create();

    // Check if the address is valid
    if (address == IpAddress::Broadcast)
        return Status::Error;

    // Bind the socket to the specified port
    sockaddr_in addr = priv::SocketImpl::create_address(address.to_integer(), port);
    if (bind(get_handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
    {
        // Not likely to happen, but...
        err() << "Failed to bind listener socket to port " << port << std::endl;
        return Status::Error;
    }

    // Listen to the bound port
    if (::listen(get_handle(), SOMAXCONN) == -1)
    {
        // Oops, socket is deaf
        err() << "Failed to listen to port " << port << std::endl;
        return Status::Error;
    }

    return Status::Done;
}


////////////////////////////////////////////////////////////
void TcpListener::close()
{
    // Simply close the socket
    Socket::close();
}


////////////////////////////////////////////////////////////
Socket::Status TcpListener::accept(TcpSocket& socket)
{
    // Make sure that we're listening
    if (get_handle() == priv::SocketImpl::invalid_socket())
    {
        err() << "Failed to accept a new connection, the socket is not listening" << std::endl;
        return Status::Error;
    }

    // Accept a new connection
    sockaddr_in                  address;
    priv::SocketImpl::AddrLength length = sizeof(address);
    SocketHandle                 remote = ::accept(get_handle(), reinterpret_cast<sockaddr*>(&address), &length);

    // Check for errors
    if (remote == priv::SocketImpl::invalid_socket())
        return priv::SocketImpl::get_error_status();

    // Initialize the new connected socket
    socket.close();
    socket.create(remote);

    return Status::Done;
}

} // namespace cppnet
