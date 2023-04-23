#include <cstdint>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <cppnet/socket.hpp>
#include <win32/windows_header.hpp>

namespace cppnet::priv
{
////////////////////////////////////////////////////////////
/// \brief Helper class implementing all the non-portable
///        socket stuff; this is the Windows version
///
////////////////////////////////////////////////////////////
class SocketImpl
{
public:
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    using AddrLength = int;
    using Size       = int;

    ////////////////////////////////////////////////////////////
    /// \brief Create an internal sockaddr_in address
    ///
    /// \param address Target address
    /// \param port    Target port
    ///
    /// \return sockaddr_in ready to be used by socket functions
    ///
    ////////////////////////////////////////////////////////////
    static sockaddr_in create_address(std::uint32_t address, unsigned short port);

    ////////////////////////////////////////////////////////////
    /// \brief Return the value of the invalid socket
    ///
    /// \return Special value of the invalid socket
    ///
    ////////////////////////////////////////////////////////////
    static SocketHandle invalid_socket();

    ////////////////////////////////////////////////////////////
    /// \brief Close and destroy a socket
    ///
    /// \param sock Handle of the socket to close
    ///
    ////////////////////////////////////////////////////////////
    static void close(SocketHandle sock);

    ////////////////////////////////////////////////////////////
    /// \brief Set a socket as blocking or non-blocking
    ///
    /// \param sock  Handle of the socket
    /// \param block New blocking state of the socket
    ///
    ////////////////////////////////////////////////////////////
    static void set_blocking(SocketHandle sock, bool block);

    ////////////////////////////////////////////////////////////
    /// Get the last socket error status
    ///
    /// \return Status corresponding to the last socket error
    ///
    ////////////////////////////////////////////////////////////
    static Socket::Status get_error_status();
};

} // namespace cppnet::priv
