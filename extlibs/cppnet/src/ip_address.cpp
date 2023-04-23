#include <cstring>
#include <istream>
#include <ostream>
#include <utility>

#include <cppnet/http.hpp>
#include <cppnet/ip_address.hpp>
#include <socket_impl.hpp>

namespace cppnet
{
constexpr std::string_view PUBLIC_IP_RESOLVER = "checkip.amazonaws.com";

////////////////////////////////////////////////////////////
const IpAddress IpAddress::Any(0, 0, 0, 0);
const IpAddress IpAddress::LocalHost(127, 0, 0, 1);
const IpAddress IpAddress::Broadcast(255, 255, 255, 255);


////////////////////////////////////////////////////////////
std::optional<IpAddress> IpAddress::resolve(std::string_view address)
{
    using namespace std::string_view_literals;

    if (address.empty())
        return std::nullopt;

    if (address == "255.255.255.255"sv)
    {
        // The broadcast address needs to be handled explicitly,
        // because it is also the value returned by inet_addr on error
        return Broadcast;
    }

    if (address == "0.0.0.0"sv)
        return Any;

    // Try to convert the address as a byte representation ("xxx.xxx.xxx.xxx")
    if (const std::uint32_t ip = inet_addr(address.data()); ip != INADDR_NONE)
        return IpAddress(ntohl(ip));

    // Not a valid address, try to convert it as a host name
    addrinfo hints{}; // Zero-initialize
    hints.ai_family = AF_INET;

    addrinfo* result = nullptr;
    if (getaddrinfo(address.data(), nullptr, &hints, &result) == 0 && result != nullptr)
    {
        sockaddr_in sin;
        std::memcpy(&sin, result->ai_addr, sizeof(*result->ai_addr));

        const std::uint32_t ip = sin.sin_addr.s_addr;
        freeaddrinfo(result);

        return IpAddress(ntohl(ip));
    }

    return std::nullopt;
}


////////////////////////////////////////////////////////////
IpAddress::IpAddress(std::uint8_t byte0, std::uint8_t byte1, std::uint8_t byte2, std::uint8_t byte3) :
m_address(htonl(static_cast<std::uint32_t>((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3)))
{
}


////////////////////////////////////////////////////////////
IpAddress::IpAddress(std::uint32_t address) : m_address(htonl(address))
{
}


////////////////////////////////////////////////////////////
std::string IpAddress::to_string() const
{
    in_addr address;
    address.s_addr = m_address;

    return inet_ntoa(address);
}


////////////////////////////////////////////////////////////
std::uint32_t IpAddress::to_integer() const
{
    return ntohl(m_address);
}


////////////////////////////////////////////////////////////
std::optional<IpAddress> IpAddress::get_local_address()
{
    // The method here is to connect a UDP socket to anyone (here to localhost),
    // and get the local socket address with the getsockname function.
    // UDP connection will not send anything to the network, so this function won't cause any overhead.

    // Create the socket
    SocketHandle sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == priv::SocketImpl::invalid_socket())
        return std::nullopt;

    // Connect the socket to localhost on any port
    sockaddr_in address = priv::SocketImpl::create_address(ntohl(INADDR_LOOPBACK), 9);
    if (connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1)
    {
        priv::SocketImpl::close(sock);
        return std::nullopt;
    }

    // Get the local address of the socket connection
    priv::SocketImpl::AddrLength size = sizeof(address);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&address), &size) == -1)
    {
        priv::SocketImpl::close(sock);
        return std::nullopt;
    }

    // Close the socket
    priv::SocketImpl::close(sock);

    // Finally build the IP address
    return IpAddress(ntohl(address.sin_addr.s_addr));
}


////////////////////////////////////////////////////////////
std::optional<IpAddress> IpAddress::get_public_address(Time timeout)
{
    // The trick here is more complicated, because the only way
    // to get our public IP address is to get it from a distant computer.
    // Here we get the web page from http://checkip.amazonaws.com
    // and parse the result to extract our IP address
    // (not very hard: the web page contains only our IP address).

    Http           server(PUBLIC_IP_RESOLVER.data());
    Http::Request  request("/", Http::Request::Method::GET);
    Http::Response page = server.send_request(request, timeout);
    if (page.get_status() == Http::Response::Status::Ok)
    {
        std::string body = page.get_body();
        // Remove the trailing newline
        if (!body.empty() && body[body.size() - 1] == '\n')
            body.erase(body.size() - 1);
        
        return IpAddress::resolve(body);
    }

    // Something failed: return an invalid address
    return std::nullopt;
}


////////////////////////////////////////////////////////////
bool operator==(const IpAddress& left, const IpAddress& right)
{
    return !(left < right) && !(right < left);
}


////////////////////////////////////////////////////////////
bool operator!=(const IpAddress& left, const IpAddress& right)
{
    return !(left == right);
}


////////////////////////////////////////////////////////////
bool operator<(const IpAddress& left, const IpAddress& right)
{
    return left.m_address < right.m_address;
}


////////////////////////////////////////////////////////////
bool operator>(const IpAddress& left, const IpAddress& right)
{
    return right < left;
}


////////////////////////////////////////////////////////////
bool operator<=(const IpAddress& left, const IpAddress& right)
{
    return !(right < left);
}


////////////////////////////////////////////////////////////
bool operator>=(const IpAddress& left, const IpAddress& right)
{
    return !(left < right);
}


////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& stream, std::optional<IpAddress>& address)
{
    std::string str;
    stream >> str;
    address = IpAddress::resolve(str);

    return stream;
}


////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& stream, const IpAddress& address)
{
    return stream << address.to_string();
}

} // namespace cppnet
