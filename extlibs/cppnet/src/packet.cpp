#include <cstring>
#include <cwchar>

#include <cppnet/packet.hpp>
#include <socket_impl.hpp>

namespace cppnet
{
////////////////////////////////////////////////////////////
Packet::Packet(const Packet&) = default;


////////////////////////////////////////////////////////////
Packet& Packet::operator=(const Packet&) = default;


////////////////////////////////////////////////////////////
Packet::Packet(Packet&&) noexcept = default;


////////////////////////////////////////////////////////////
Packet& Packet::operator=(Packet&&) noexcept = default;


////////////////////////////////////////////////////////////
void Packet::append(const void* data, std::size_t size_in_bytes)
{
    if (data && (size_in_bytes > 0))
    {
        std::size_t start = m_data.size();
        m_data.resize(start + size_in_bytes);
        std::memcpy(&m_data[start], data, size_in_bytes);
    }
}


////////////////////////////////////////////////////////////
std::size_t Packet::get_read_position() const
{
    return m_read_pos;
}


////////////////////////////////////////////////////////////
void Packet::clear()
{
    m_data.clear();
    m_read_pos = 0;
    m_is_valid = true;
}


////////////////////////////////////////////////////////////
const void* Packet::get_data() const
{
    return !m_data.empty() ? m_data.data() : nullptr;
}


////////////////////////////////////////////////////////////
std::size_t Packet::get_data_size() const
{
    return m_data.size();
}


////////////////////////////////////////////////////////////
bool Packet::end_of_packet() const
{
    return m_read_pos >= m_data.size();
}


////////////////////////////////////////////////////////////
Packet::operator bool() const
{
    return m_is_valid;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(bool& data)
{
    std::uint8_t value;
    if (*this >> value)
        data = (value != 0);

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::int8_t& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::uint8_t& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::int16_t& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        data = static_cast<std::int16_t>(ntohs(static_cast<std::uint16_t>(data)));
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::uint16_t& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        data = ntohs(data);
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::int32_t& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        data = static_cast<std::int32_t>(ntohl(static_cast<std::uint32_t>(data)));
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::uint32_t& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        data = ntohl(data);
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::int64_t& data)
{
    if (check_size(sizeof(data)))
    {
        // Since ntohll is not available everywhere, we have to convert
        // to network byte order (big endian) manually
        std::uint8_t bytes[sizeof(data)];
        std::memcpy(bytes, &m_data[m_read_pos], sizeof(data));

        data = (static_cast<std::int64_t>(bytes[0]) << 56) | (static_cast<std::int64_t>(bytes[1]) << 48) |
               (static_cast<std::int64_t>(bytes[2]) << 40) | (static_cast<std::int64_t>(bytes[3]) << 32) |
               (static_cast<std::int64_t>(bytes[4]) << 24) | (static_cast<std::int64_t>(bytes[5]) << 16) |
               (static_cast<std::int64_t>(bytes[6]) << 8) | (static_cast<std::int64_t>(bytes[7]));

        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::uint64_t& data)
{
    if (check_size(sizeof(data)))
    {
        // Since ntohll is not available everywhere, we have to convert
        // to network byte order (big endian) manually
        std::uint8_t bytes[sizeof(data)];
        std::memcpy(bytes, &m_data[m_read_pos], sizeof(data));

        data = (static_cast<std::uint64_t>(bytes[0]) << 56) | (static_cast<std::uint64_t>(bytes[1]) << 48) |
               (static_cast<std::uint64_t>(bytes[2]) << 40) | (static_cast<std::uint64_t>(bytes[3]) << 32) |
               (static_cast<std::uint64_t>(bytes[4]) << 24) | (static_cast<std::uint64_t>(bytes[5]) << 16) |
               (static_cast<std::uint64_t>(bytes[6]) << 8) | (static_cast<std::uint64_t>(bytes[7]));

        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(float& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(double& data)
{
    if (check_size(sizeof(data)))
    {
        std::memcpy(&data, &m_data[m_read_pos], sizeof(data));
        m_read_pos += sizeof(data);
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(char* data)
{
    // First extract string length
    std::uint32_t length = 0;
    *this >> length;

    if ((length > 0) && check_size(length))
    {
        // Then extract characters
        std::memcpy(data, &m_data[m_read_pos], length);
        data[length] = '\0';

        // Update reading position
        m_read_pos += length;
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::string& data)
{
    // First extract string length
    std::uint32_t length = 0;
    *this >> length;

    data.clear();
    if ((length > 0) && check_size(length))
    {
        // Then extract characters
        data.assign(&m_data[m_read_pos], length);

        // Update reading position
        m_read_pos += length;
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(wchar_t* data)
{
    // First extract string length
    std::uint32_t length = 0;
    *this >> length;

    if ((length > 0) && check_size(length * sizeof(std::uint32_t)))
    {
        // Then extract characters
        for (std::uint32_t i = 0; i < length; ++i)
        {
            std::uint32_t character = 0;
            *this >> character;
            data[i] = static_cast<wchar_t>(character);
        }
        data[length] = L'\0';
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator>>(std::wstring& data)
{
    // First extract string length
    std::uint32_t length = 0;
    *this >> length;

    data.clear();
    if ((length > 0) && check_size(length * sizeof(std::uint32_t)))
    {
        // Then extract characters
        for (std::uint32_t i = 0; i < length; ++i)
        {
            std::uint32_t character = 0;
            *this >> character;
            data += static_cast<wchar_t>(character);
        }
    }

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(bool data)
{
    *this << static_cast<std::uint8_t>(data);
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::int8_t data)
{
    append(&data, sizeof(data));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::uint8_t data)
{
    append(&data, sizeof(data));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::int16_t data)
{
    auto to_write = static_cast<std::int16_t>(htons(static_cast<std::uint16_t>(data)));
    append(&to_write, sizeof(to_write));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::uint16_t data)
{
    std::uint16_t to_write = htons(data);
    append(&to_write, sizeof(to_write));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::int32_t data)
{
    auto to_write = static_cast<std::int32_t>(htonl(static_cast<std::uint32_t>(data)));
    append(&to_write, sizeof(to_write));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::uint32_t data)
{
    std::uint32_t to_write = htonl(data);
    append(&to_write, sizeof(to_write));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::int64_t data)
{
    // Since htonll is not available everywhere, we have to convert
    // to network byte order (big endian) manually

    std::uint8_t to_write[] = {static_cast<std::uint8_t>((data >> 56) & 0xFF),
                              static_cast<std::uint8_t>((data >> 48) & 0xFF),
                              static_cast<std::uint8_t>((data >> 40) & 0xFF),
                              static_cast<std::uint8_t>((data >> 32) & 0xFF),
                              static_cast<std::uint8_t>((data >> 24) & 0xFF),
                              static_cast<std::uint8_t>((data >> 16) & 0xFF),
                              static_cast<std::uint8_t>((data >> 8) & 0xFF),
                              static_cast<std::uint8_t>((data)&0xFF)};

    append(&to_write, sizeof(to_write));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(std::uint64_t data)
{
    // Since htonll is not available everywhere, we have to convert
    // to network byte order (big endian) manually

    std::uint8_t to_write[] = {static_cast<std::uint8_t>((data >> 56) & 0xFF),
                              static_cast<std::uint8_t>((data >> 48) & 0xFF),
                              static_cast<std::uint8_t>((data >> 40) & 0xFF),
                              static_cast<std::uint8_t>((data >> 32) & 0xFF),
                              static_cast<std::uint8_t>((data >> 24) & 0xFF),
                              static_cast<std::uint8_t>((data >> 16) & 0xFF),
                              static_cast<std::uint8_t>((data >> 8) & 0xFF),
                              static_cast<std::uint8_t>((data)&0xFF)};

    append(&to_write, sizeof(to_write));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(float data)
{
    append(&data, sizeof(data));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(double data)
{
    append(&data, sizeof(data));
    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(const char* data)
{
    // First insert string length
    auto length = static_cast<std::uint32_t>(std::strlen(data));
    *this << length;

    // Then insert characters
    append(data, length * sizeof(char));

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(const std::string& data)
{
    // First insert string length
    auto length = static_cast<std::uint32_t>(data.size());
    *this << length;

    // Then insert characters
    if (length > 0)
        append(data.c_str(), length * sizeof(std::string::value_type));

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(const wchar_t* data)
{
    // First insert string length
    auto length = static_cast<std::uint32_t>(std::wcslen(data));
    *this << length;

    // Then insert characters
    for (const wchar_t* c = data; *c != L'\0'; ++c)
        *this << static_cast<std::uint32_t>(*c);

    return *this;
}


////////////////////////////////////////////////////////////
Packet& Packet::operator<<(const std::wstring& data)
{
    // First insert string length
    auto length = static_cast<std::uint32_t>(data.size());
    *this << length;

    // Then insert characters
    if (length > 0)
    {
        for (wchar_t c : data)
            *this << static_cast<std::uint32_t>(c);
    }

    return *this;
}


////////////////////////////////////////////////////////////
bool Packet::check_size(std::size_t size)
{
    m_is_valid = m_is_valid && (m_read_pos + size <= m_data.size());

    return m_is_valid;
}


////////////////////////////////////////////////////////////
const void* Packet::on_send(std::size_t& size)
{
    size = get_data_size();
    return get_data();
}


////////////////////////////////////////////////////////////
void Packet::on_receive(const void* data, std::size_t size)
{
    append(data, size);
}

} // namespace cppnet
