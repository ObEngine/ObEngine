#include <ostream>

#include <cppnet/log.hpp>
#include <cppnet/socket.hpp>
#include <socket_impl.hpp>

namespace cppnet
{
////////////////////////////////////////////////////////////
Socket::Socket(Type type) : m_type(type), m_socket(priv::SocketImpl::invalid_socket())
{
}


////////////////////////////////////////////////////////////
Socket::~Socket()
{
    // Close the socket before it gets destructed
    close();
}


////////////////////////////////////////////////////////////
void Socket::set_blocking(bool blocking)
{
    // Apply if the socket is already created
    if (m_socket != priv::SocketImpl::invalid_socket())
        priv::SocketImpl::set_blocking(m_socket, blocking);

    m_is_blocking = blocking;
}


////////////////////////////////////////////////////////////
bool Socket::is_blocking() const
{
    return m_is_blocking;
}


////////////////////////////////////////////////////////////
SocketHandle Socket::get_handle() const
{
    return m_socket;
}


////////////////////////////////////////////////////////////
void Socket::create()
{
    // Don't create the socket if it already exists
    if (m_socket == priv::SocketImpl::invalid_socket())
    {
        SocketHandle handle = socket(PF_INET, m_type == Type::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);

        if (handle == priv::SocketImpl::invalid_socket())
        {
            err() << "Failed to create socket" << std::endl;
            return;
        }

        create(handle);
    }
}


////////////////////////////////////////////////////////////
void Socket::create(SocketHandle handle)
{
    // Don't create the socket if it already exists
    if (m_socket == priv::SocketImpl::invalid_socket())
    {
        // Assign the new handle
        m_socket = handle;

        // Set the current blocking state
        set_blocking(m_is_blocking);

        if (m_type == Type::TCP)
        {
            // Disable the Nagle algorithm (i.e. removes buffering of TCP packets)
            int yes = 1;
            if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
            {
                err() << "Failed to set socket option \"TCP_NODELAY\" ; "
                      << "all your TCP packets will be buffered" << std::endl;
            }

// On Mac OS X, disable the SIGPIPE signal on disconnection
#ifdef CPPNET_PLATFORM_MACOS
            if (setsockopt(m_socket, SOL_SOCKET, SO_NOSIGPIPE, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
            {
                err() << "Failed to set socket option \"SO_NOSIGPIPE\"" << std::endl;
            }
#endif
        }
        else
        {
            // Enable broadcast by default for UDP sockets
            int yes = 1;
            if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
            {
                err() << "Failed to enable broadcast on UDP socket" << std::endl;
            }
        }
    }
}


////////////////////////////////////////////////////////////
void Socket::close()
{
    // Close the socket
    if (m_socket != priv::SocketImpl::invalid_socket())
    {
        priv::SocketImpl::close(m_socket);
        m_socket = priv::SocketImpl::invalid_socket();
    }
}

} // namespace cppnet
