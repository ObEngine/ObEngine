#pragma once

#include <cppnet/ip_address.hpp>
#include <cppnet/socket.hpp>

namespace cppnet
{
class TcpSocket;

////////////////////////////////////////////////////////////
/// \brief Socket that listens to new TCP connections
///
////////////////////////////////////////////////////////////
class TcpListener : public Socket
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    TcpListener();

    ////////////////////////////////////////////////////////////
    /// \brief Get the port to which the socket is bound locally
    ///
    /// If the socket is not listening to a port, this function
    /// returns 0.
    ///
    /// \return Port to which the socket is bound
    ///
    /// \see listen
    ///
    ////////////////////////////////////////////////////////////
    unsigned short get_local_port() const;

    ////////////////////////////////////////////////////////////
    /// \brief Start listening for incoming connection attempts
    ///
    /// This function makes the socket start listening on the
    /// specified port, waiting for incoming connection attempts.
    ///
    /// If the socket is already listening on a port when this
    /// function is called, it will stop listening on the old
    /// port before starting to listen on the new port.
    ///
    /// When providing cppnet::Socket::AnyPort as port, the listener
    /// will request an available port from the system.
    /// The chosen port can be retrieved by calling get_local_port().
    ///
    /// \param port    Port to listen on for incoming connection attempts
    /// \param address Address of the interface to listen on
    ///
    /// \return Status code
    ///
    /// \see accept, close
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] Status listen(unsigned short port, const IpAddress& address = IpAddress::Any);

    ////////////////////////////////////////////////////////////
    /// \brief Stop listening and close the socket
    ///
    /// This function gracefully stops the listener. If the
    /// socket is not listening, this function has no effect.
    ///
    /// \see listen
    ///
    ////////////////////////////////////////////////////////////
    void close();

    ////////////////////////////////////////////////////////////
    /// \brief Accept a new connection
    ///
    /// If the socket is in blocking mode, this function will
    /// not return until a connection is actually received.
    ///
    /// \param socket Socket that will hold the new connection
    ///
    /// \return Status code
    ///
    /// \see listen
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] Status accept(TcpSocket& socket);
};


} // namespace cppnet


////////////////////////////////////////////////////////////
/// \class cppnet::TcpListener
/// \ingroup network
///
/// A listener socket is a special type of socket that listens to
/// a given port and waits for connections on that port.
/// This is all it can do.
///
/// When a new connection is received, you must call accept and
/// the listener returns a new instance of cppnet::TcpSocket that
/// is properly initialized and can be used to communicate with
/// the new client.
///
/// Listener sockets are specific to the TCP protocol,
/// UDP sockets are connectionless and can therefore communicate
/// directly. As a consequence, a listener socket will always
/// return the new connections as cppnet::TcpSocket instances.
///
/// A listener is automatically closed on destruction, like all
/// other types of socket. However if you want to stop listening
/// before the socket is destroyed, you can call its close()
/// function.
///
/// Usage example:
/// \code
/// // Create a listener socket and make it wait for new
/// // connections on port 55001
/// cppnet::TcpListener listener;
/// listener.listen(55001);
///
/// // Endless loop that waits for new connections
/// while (running)
/// {
///     cppnet::TcpSocket client;
///     if (listener.accept(client) == cppnet::Socket::Done)
///     {
///         // A new client just connected!
///         std::cout << "New connection received from " << client.get_remote_address().value() << std::endl;
///         do_something_with(client);
///     }
/// }
/// \endcode
///
/// \see cppnet::TcpSocket, cppnet::Socket
///
////////////////////////////////////////////////////////////
