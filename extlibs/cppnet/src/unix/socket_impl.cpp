#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <ostream>

#include <cppnet/log.hpp>
#include <unix/socket_impl.hpp>

namespace cppnet::priv
{
////////////////////////////////////////////////////////////
sockaddr_in SocketImpl::create_address(std::uint32_t address, unsigned short port)
{
    auto addr            = sockaddr_in();
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);

#if defined(CPPNET_PLATFORM_MACOS)
    addr.sin_len = sizeof(addr);
#endif

    return addr;
}


////////////////////////////////////////////////////////////
SocketHandle SocketImpl::invalid_socket()
{
    return -1;
}


////////////////////////////////////////////////////////////
void SocketImpl::close(SocketHandle sock)
{
    ::close(sock);
}


////////////////////////////////////////////////////////////
void SocketImpl::set_blocking(SocketHandle sock, bool block)
{
    int status = fcntl(sock, F_GETFL);
    if (block)
    {
        if (fcntl(sock, F_SETFL, status & ~O_NONBLOCK) == -1)
            err() << "Failed to set file status flags: " << errno << std::endl;
    }
    else
    {
        if (fcntl(sock, F_SETFL, status | O_NONBLOCK) == -1)
            err() << "Failed to set file status flags: " << errno << std::endl;
    }
}


////////////////////////////////////////////////////////////
Socket::Status SocketImpl::get_error_status()
{
    // The followings are sometimes equal to EWOULDBLOCK,
    // so we have to make a special case for them in order
    // to avoid having double values in the switch case
    if ((errno == EAGAIN) || (errno == EINPROGRESS))
        return Socket::Status::NotReady;

    // clang-format off
    switch (errno)
    {
        case EWOULDBLOCK:  return Socket::Status::NotReady;
        case ECONNABORTED: return Socket::Status::Disconnected;
        case ECONNRESET:   return Socket::Status::Disconnected;
        case ETIMEDOUT:    return Socket::Status::Disconnected;
        case ENETRESET:    return Socket::Status::Disconnected;
        case ENOTCONN:     return Socket::Status::Disconnected;
        case EPIPE:        return Socket::Status::Disconnected;
        default:           return Socket::Status::Error;
    }
    // clang-format on
}

} // namespace cppnet::priv
