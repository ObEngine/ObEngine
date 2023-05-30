#pragma once

#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

#include <cppnet/time.hpp>

namespace cppnet
{
////////////////////////////////////////////////////////////
/// \brief Encapsulate an IPv4 network address
///
////////////////////////////////////////////////////////////
class IpAddress
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Construct the address from a null-terminated string view
    ///
    /// Here \a address can be either a decimal address
    /// (ex: "192.168.1.56") or a network name (ex: "localhost").
    ///
    /// \param address IP address or network name
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] static std::optional<IpAddress> resolve(std::string_view address);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the address from 4 bytes
    ///
    /// Calling IpAddress(a, b, c, d) is equivalent to calling
    /// IpAddress::resolve("a.b.c.d"), but safer as it doesn't
    /// have to parse a string to get the address components.
    ///
    /// \param byte0 First byte of the address
    /// \param byte1 Second byte of the address
    /// \param byte2 Third byte of the address
    /// \param byte3 Fourth byte of the address
    ///
    ////////////////////////////////////////////////////////////
    IpAddress(std::uint8_t byte0, std::uint8_t byte1, std::uint8_t byte2, std::uint8_t byte3);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the address from a 32-bits integer
    ///
    /// This constructor uses the internal representation of
    /// the address directly. It should be used for optimization
    /// purposes, and only if you got that representation from
    /// IpAddress::to_integer().
    ///
    /// \param address 4 bytes of the address packed into a 32-bits integer
    ///
    /// \see to_integer
    ///
    ////////////////////////////////////////////////////////////
    explicit IpAddress(std::uint32_t address);

    ////////////////////////////////////////////////////////////
    /// \brief Get a string representation of the address
    ///
    /// The returned string is the decimal representation of the
    /// IP address (like "192.168.1.56"), even if it was constructed
    /// from a host name.
    ///
    /// \return String representation of the address
    ///
    /// \see to_integer
    ///
    ////////////////////////////////////////////////////////////
    std::string to_string() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get an integer representation of the address
    ///
    /// The returned number is the internal representation of the
    /// address, and should be used for optimization purposes only
    /// (like sending the address through a socket).
    /// The integer produced by this function can then be converted
    /// back to a cppnet::IpAddress with the proper constructor.
    ///
    /// \return 32-bits unsigned integer representation of the address
    ///
    /// \see to_string
    ///
    ////////////////////////////////////////////////////////////
    std::uint32_t to_integer() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the computer's local address
    ///
    /// The local address is the address of the computer from the
    /// LAN point of view, i.e. something like 192.168.1.56. It is
    /// meaningful only for communications over the local network.
    /// Unlike get_public_address, this function is fast and may be
    /// used safely anywhere.
    ///
    /// \return Local IP address of the computer
    ///
    /// \see get_public_address
    ///
    ////////////////////////////////////////////////////////////
    static std::optional<IpAddress> get_local_address();

    ////////////////////////////////////////////////////////////
    /// \brief Get the computer's public address
    ///
    /// The public address is the address of the computer from the
    /// internet point of view, i.e. something like 89.54.1.169.
    /// It is necessary for communications over the world wide web.
    /// The only way to get a public address is to ask it to a
    /// distant website; as a consequence, this function depends on
    /// both your network connection and the server, and may be
    /// very slow. You should use it as few as possible. Because
    /// this function depends on the network connection and on a distant
    /// server, you may use a time limit if you don't want your program
    /// to be possibly stuck waiting in case there is a problem; this
    /// limit is deactivated by default.
    ///
    /// \param timeout Maximum time to wait
    ///
    /// \return Public IP address of the computer
    ///
    /// \see get_local_address
    ///
    ////////////////////////////////////////////////////////////
    static std::optional<IpAddress> get_public_address(Time timeout = 0s);

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTBEGIN(readability-identifier-naming)
    static const IpAddress Any;       //!< Value representing any address (0.0.0.0)
    static const IpAddress LocalHost; //!< The "localhost" address (for connecting a computer to itself locally)
    static const IpAddress Broadcast; //!< The "broadcast" address (for sending UDP messages to everyone on a local network)
    // NOLINTEND(readability-identifier-naming)

private:
    friend bool operator<(const IpAddress& left, const IpAddress& right);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::uint32_t m_address; //!< Address stored as an unsigned 32 bits integer
};

////////////////////////////////////////////////////////////
/// \brief Overload of == operator to compare two IP addresses
///
/// \param left  Left operand (a IP address)
/// \param right Right operand (a IP address)
///
/// \return True if both addresses are equal
///
////////////////////////////////////////////////////////////
bool operator==(const IpAddress& left, const IpAddress& right);

////////////////////////////////////////////////////////////
/// \brief Overload of != operator to compare two IP addresses
///
/// \param left  Left operand (a IP address)
/// \param right Right operand (a IP address)
///
/// \return True if both addresses are different
///
////////////////////////////////////////////////////////////
bool operator!=(const IpAddress& left, const IpAddress& right);

////////////////////////////////////////////////////////////
/// \brief Overload of < operator to compare two IP addresses
///
/// \param left  Left operand (a IP address)
/// \param right Right operand (a IP address)
///
/// \return True if \a left is lesser than \a right
///
////////////////////////////////////////////////////////////
bool operator<(const IpAddress& left, const IpAddress& right);

////////////////////////////////////////////////////////////
/// \brief Overload of > operator to compare two IP addresses
///
/// \param left  Left operand (a IP address)
/// \param right Right operand (a IP address)
///
/// \return True if \a left is greater than \a right
///
////////////////////////////////////////////////////////////
bool operator>(const IpAddress& left, const IpAddress& right);

////////////////////////////////////////////////////////////
/// \brief Overload of <= operator to compare two IP addresses
///
/// \param left  Left operand (a IP address)
/// \param right Right operand (a IP address)
///
/// \return True if \a left is lesser or equal than \a right
///
////////////////////////////////////////////////////////////
bool operator<=(const IpAddress& left, const IpAddress& right);

////////////////////////////////////////////////////////////
/// \brief Overload of >= operator to compare two IP addresses
///
/// \param left  Left operand (a IP address)
/// \param right Right operand (a IP address)
///
/// \return True if \a left is greater or equal than \a right
///
////////////////////////////////////////////////////////////
bool operator>=(const IpAddress& left, const IpAddress& right);

////////////////////////////////////////////////////////////
/// \brief Overload of >> operator to extract an IP address from an input stream
///
/// \param stream  Input stream
/// \param address IP address to extract
///
/// \return Reference to the input stream
///
////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& stream, std::optional<IpAddress>& address);

////////////////////////////////////////////////////////////
/// \brief Overload of << operator to print an IP address to an output stream
///
/// \param stream  Output stream
/// \param address IP address to print
///
/// \return Reference to the output stream
///
////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& stream, const IpAddress& address);

} // namespace cppnet


////////////////////////////////////////////////////////////
/// \class cppnet::IpAddress
/// \ingroup network
///
/// cppnet::IpAddress is a utility class for manipulating network
/// addresses. It provides a set a implicit constructors and
/// conversion functions to easily build or transform an IP
/// address from/to various representations.
///
/// Usage example:
/// \code
/// auto a2 = cppnet::IpAddress::resolve("127.0.0.1");      // the local host address
/// auto a3 = cppnet::IpAddress::Broadcast;                 // the broadcast address
/// cppnet::IpAddress a4(192, 168, 1, 56);                  // a local address
/// auto a5 = cppnet::IpAddress::resolve("my_computer");    // a local address created from a network name
/// auto a6 = cppnet::IpAddress::resolve("89.54.1.169");    // a distant address
/// auto a7 = cppnet::IpAddress::resolve("www.google.com"); // a distant address created from a network name
/// auto a8 = cppnet::IpAddress::get_local_address();         // my address on the local network
/// auto a9 = cppnet::IpAddress::get_public_address();        // my address on the internet
/// \endcode
///
/// Note that cppnet::IpAddress currently doesn't support IPv6
/// nor other types of network addresses.
///
////////////////////////////////////////////////////////////
