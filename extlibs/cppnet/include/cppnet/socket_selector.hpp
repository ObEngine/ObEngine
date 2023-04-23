#pragma once

#include <cppnet/time.hpp>

#include <memory>

namespace cppnet
{
class Socket;

////////////////////////////////////////////////////////////
/// \brief Multiplexer that allows to read from multiple sockets
///
////////////////////////////////////////////////////////////
class SocketSelector
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    SocketSelector();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SocketSelector() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    SocketSelector(const SocketSelector& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Add a new socket to the selector
    ///
    /// This function keeps a weak reference to the socket,
    /// so you have to make sure that the socket is not destroyed
    /// while it is stored in the selector.
    /// This function does nothing if the socket is not valid.
    ///
    /// \param socket Reference to the socket to add
    ///
    /// \see remove, clear
    ///
    ////////////////////////////////////////////////////////////
    void add(Socket& socket);

    ////////////////////////////////////////////////////////////
    /// \brief Remove a socket from the selector
    ///
    /// This function doesn't destroy the socket, it simply
    /// removes the reference that the selector has to it.
    ///
    /// \param socket Reference to the socket to remove
    ///
    /// \see add, clear
    ///
    ////////////////////////////////////////////////////////////
    void remove(Socket& socket);

    ////////////////////////////////////////////////////////////
    /// \brief Remove all the sockets stored in the selector
    ///
    /// This function doesn't destroy any instance, it simply
    /// removes all the references that the selector has to
    /// external sockets.
    ///
    /// \see add, remove
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Wait until one or more sockets are ready to receive
    ///
    /// This function returns as soon as at least one socket has
    /// some data available to be received. To know which sockets are
    /// ready, use the is_ready function.
    /// If you use a timeout and no socket is ready before the timeout
    /// is over, the function returns false.
    ///
    /// \param timeout Maximum time to wait, (use Time::Zero for infinity)
    ///
    /// \return True if there are sockets ready, false otherwise
    ///
    /// \see is_ready
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool wait(Time timeout = 0s);

    ////////////////////////////////////////////////////////////
    /// \brief Test a socket to know if it is ready to receive data
    ///
    /// This function must be used after a call to Wait, to know
    /// which sockets are ready to receive data. If a socket is
    /// ready, a call to receive will never block because we know
    /// that there is data available to read.
    /// Note that if this function returns true for a TcpListener,
    /// this means that it is ready to accept a new connection.
    ///
    /// \param socket Socket to test
    ///
    /// \return True if the socket is ready to read, false otherwise
    ///
    /// \see is_ready
    ///
    ////////////////////////////////////////////////////////////
    bool is_ready(Socket& socket) const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of assignment operator
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    SocketSelector& operator=(const SocketSelector& right);

private:
    struct SocketSelectorImpl;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::unique_ptr<SocketSelectorImpl> m_impl; //!< Opaque pointer to the implementation (which requires OS-specific types)
};

} // namespace cppnet


////////////////////////////////////////////////////////////
/// \class cppnet::SocketSelector
/// \ingroup network
///
/// Socket selectors provide a way to wait until some data is
/// available on a set of sockets, instead of just one. This
/// is convenient when you have multiple sockets that may
/// possibly receive data, but you don't know which one will
/// be ready first. In particular, it avoids to use a thread
/// for each socket; with selectors, a single thread can handle
/// all the sockets.
///
/// All types of sockets can be used in a selector:
/// \li cppnet::TcpListener
/// \li cppnet::TcpSocket
/// \li cppnet::UdpSocket
///
/// A selector doesn't store its own copies of the sockets
/// (socket classes are not copyable anyway), it simply keeps
/// a reference to the original sockets that you pass to the
/// "add" function. Therefore, you can't use the selector as a
/// socket container, you must store them outside and make sure
/// that they are alive as long as they are used in the selector.
///
/// Using a selector is simple:
/// \li populate the selector with all the sockets that you want to observe
/// \li make it wait until there is data available on any of the sockets
/// \li test each socket to find out which ones are ready
///
/// Usage example:
/// \code
/// // Create a socket to listen to new connections
/// cppnet::TcpListener listener;
/// listener.listen(55001);
///
/// // Create a list to store the future clients
/// std::list<std::unique_ptr<cppnet::TcpSocket>> clients;
///
/// // Create a selector
/// cppnet::SocketSelector selector;
///
/// // Add the listener to the selector
/// selector.add(listener);
///
/// // Endless loop that waits for new connections
/// while (running)
/// {
///     // Make the selector wait for data on any socket
///     if (selector.wait())
///     {
///         // Test the listener
///         if (selector.is_ready(listener))
///         {
///             // The listener is ready: there is a pending connection
///             auto client = std::make_unique<cppnet::TcpSocket>();
///             if (listener.accept(*client) == cppnet::Socket::Status::Done)
///             {
///                 // Add the new client to the selector so that we will
///                 // be notified when he sends something
///                 selector.add(*client);
///
///                 // Add the new client to the clients list
///                 clients.push_back(std::move(client));
///             }
///             else
///             {
///                 // Error, we won't get a new connection, delete the socket
///                 client.reset();
///             }
///         }
///         else
///         {
///             // The listener socket is not ready, test all other sockets (the clients)
///             for (cppnet::TcpSocket& client : clients)
///             {
///                 if (selector.is_ready(client))
///                 {
///                     // The client has sent some data, we can receive it
///                     cppnet::Packet packet;
///                     if (client.receive(packet) == cppnet::Socket::Status::Done)
///                     {
///                         ...
///                     }
///                 }
///             }
///         }
///     }
/// }
/// \endcode
///
/// \see cppnet::Socket
///
////////////////////////////////////////////////////////////
