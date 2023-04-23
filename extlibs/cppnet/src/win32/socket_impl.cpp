#include <cstring>

#include <socket_impl.hpp>

namespace cppnet::priv
{
////////////////////////////////////////////////////////////
sockaddr_in SocketImpl::create_address(std::uint32_t address, unsigned short port)
{
    auto addr            = sockaddr_in();
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);

    return addr;
}


////////////////////////////////////////////////////////////
SocketHandle SocketImpl::invalid_socket()
{
    return INVALID_SOCKET;
}


////////////////////////////////////////////////////////////
void SocketImpl::close(SocketHandle sock)
{
    closesocket(sock);
}


////////////////////////////////////////////////////////////
void SocketImpl::set_blocking(SocketHandle sock, bool block)
{
    u_long blocking = block ? 0 : 1;
    ioctlsocket(sock, static_cast<long>(FIONBIO), &blocking);
}


////////////////////////////////////////////////////////////
Socket::Status SocketImpl::get_error_status()
{
    // clang-format off
    switch (WSAGetLastError())
    {
        case WSAEWOULDBLOCK:  return Socket::Status::NotReady;
        case WSAEALREADY:     return Socket::Status::NotReady;
        case WSAECONNABORTED: return Socket::Status::Disconnected;
        case WSAECONNRESET:   return Socket::Status::Disconnected;
        case WSAETIMEDOUT:    return Socket::Status::Disconnected;
        case WSAENETRESET:    return Socket::Status::Disconnected;
        case WSAENOTCONN:     return Socket::Status::Disconnected;
        case WSAEISCONN:      return Socket::Status::Done; // when connecting a non-blocking socket
        default:              return Socket::Status::Error;
    }
    // clang-format on
}


////////////////////////////////////////////////////////////
// Windows needs some initialization and cleanup to get
// sockets working properly... so let's create a class that will
// do it automatically
////////////////////////////////////////////////////////////
struct SocketInitializer
{
    SocketInitializer()
    {
        WSADATA init;
        WSAStartup(MAKEWORD(2, 2), &init);
    }

    ~SocketInitializer()
    {
        WSACleanup();
    }
};

SocketInitializer global_initializer;

} // namespace cppnet::priv
