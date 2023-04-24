#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace cppnet
{
class TcpSocket;
class UdpSocket;

////////////////////////////////////////////////////////////
/// \brief Utility class to build blocks of data to transfer
///        over the network
///
////////////////////////////////////////////////////////////
class Packet
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty packet.
    ///
    ////////////////////////////////////////////////////////////
    Packet() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Packet() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ////////////////////////////////////////////////////////////
    Packet(const Packet&);

    ////////////////////////////////////////////////////////////
    /// \brief Copy assignment
    ///
    ////////////////////////////////////////////////////////////
    Packet& operator=(const Packet&);

    ////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ////////////////////////////////////////////////////////////
    Packet(Packet&&) noexcept;

    ////////////////////////////////////////////////////////////
    /// \brief Move assignment
    ///
    ////////////////////////////////////////////////////////////
    Packet& operator=(Packet&&) noexcept;

    ////////////////////////////////////////////////////////////
    /// \brief Append data to the end of the packet
    ///
    /// \param data        Pointer to the sequence of bytes to append
    /// \param size        Number of bytes to append
    ///
    /// \see clear
    /// \see get_read_position
    ///
    ////////////////////////////////////////////////////////////
    void append(const void* data, std::size_t size);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current reading position in the packet
    ///
    /// The next read operation will read data from this position
    ///
    /// \return The byte offset of the current read position
    ///
    /// \see append
    ///
    ////////////////////////////////////////////////////////////
    std::size_t get_read_position() const;

    ////////////////////////////////////////////////////////////
    /// \brief Clear the packet
    ///
    /// After calling Clear, the packet is empty.
    ///
    /// \see append
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Get a pointer to the data contained in the packet
    ///
    /// Warning: the returned pointer may become invalid after
    /// you append data to the packet, therefore it should never
    /// be stored.
    /// The return pointer is a null pointer if the packet is empty.
    ///
    /// \return Pointer to the data
    ///
    /// \see get_data_size
    ///
    ////////////////////////////////////////////////////////////
    const void* get_data() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the data contained in the packet
    ///
    /// This function returns the number of bytes pointed to by
    /// what get_data returns.
    ///
    /// \return Data size, in bytes
    ///
    /// \see get_data
    ///
    ////////////////////////////////////////////////////////////
    std::size_t get_data_size() const;

    ////////////////////////////////////////////////////////////
    /// \brief Tell if the reading position has reached the
    ///        end of the packet
    ///
    /// This function is useful to know if there is some data
    /// left to be read, without actually reading it.
    ///
    /// \return True if all data was read, false otherwise
    ///
    /// \see operator bool
    ///
    ////////////////////////////////////////////////////////////
    bool end_of_packet() const;

    ////////////////////////////////////////////////////////////
    /// \brief Test the validity of the packet, for reading
    ///
    /// This operator allows to test the packet as a boolean
    /// variable, to check if a reading operation was successful.
    ///
    /// A packet will be in an invalid state if it has no more
    /// data to read.
    ///
    /// This behavior is the same as standard C++ streams.
    ///
    /// Usage example:
    /// \code
    /// float x;
    /// packet >> x;
    /// if (packet)
    /// {
    ///    // ok, x was extracted successfully
    /// }
    ///
    /// // -- or --
    ///
    /// float x;
    /// if (packet >> x)
    /// {
    ///    // ok, x was extracted successfully
    /// }
    /// \endcode
    ///
    /// Don't focus on the return type, it's equivalent to bool but
    /// it disallows unwanted implicit conversions to integer or
    /// pointer types.
    ///
    /// \return True if last data extraction from packet was successful
    ///
    /// \see end_of_packet
    ///
    ////////////////////////////////////////////////////////////
    explicit operator bool() const;

    ////////////////////////////////////////////////////////////
    /// Overload of operator >> to read data from the packet
    ///
    ////////////////////////////////////////////////////////////
    Packet& operator>>(bool& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::int8_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::uint8_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::int16_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::uint16_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::int32_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::uint32_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::int64_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::uint64_t& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(float& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(double& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(char* data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::string& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(wchar_t* data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator>>(std::wstring& data);

    ////////////////////////////////////////////////////////////
    /// Overload of operator << to write data into the packet
    ///
    ////////////////////////////////////////////////////////////
    Packet& operator<<(bool data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::int8_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::uint8_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::int16_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::uint16_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::int32_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::uint32_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::int64_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(std::uint64_t data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(float data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(double data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(const char* data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(const std::string& data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(const wchar_t* data);

    ////////////////////////////////////////////////////////////
    /// \overload
    ////////////////////////////////////////////////////////////
    Packet& operator<<(const std::wstring& data);

protected:
    friend class TcpSocket;
    friend class UdpSocket;

    ////////////////////////////////////////////////////////////
    /// \brief Called before the packet is sent over the network
    ///
    /// This function can be defined by derived classes to
    /// transform the data before it is sent; this can be
    /// used for compression, encryption, etc.
    /// The function must return a pointer to the modified data,
    /// as well as the number of bytes pointed.
    /// The default implementation provides the packet's data
    /// without transforming it.
    ///
    /// \param size Variable to fill with the size of data to send
    ///
    /// \return Pointer to the array of bytes to send
    ///
    /// \see on_receive
    ///
    ////////////////////////////////////////////////////////////
    virtual const void* on_send(std::size_t& size);

    ////////////////////////////////////////////////////////////
    /// \brief Called after the packet is received over the network
    ///
    /// This function can be defined by derived classes to
    /// transform the data after it is received; this can be
    /// used for decompression, decryption, etc.
    /// The function receives a pointer to the received data,
    /// and must fill the packet with the transformed bytes.
    /// The default implementation fills the packet directly
    /// without transforming the data.
    ///
    /// \param data Pointer to the received bytes
    /// \param size Number of bytes
    ///
    /// \see on_send
    ///
    ////////////////////////////////////////////////////////////
    virtual void on_receive(const void* data, std::size_t size);

private:
    ////////////////////////////////////////////////////////////
    /// Disallow comparisons between packets
    ///
    ////////////////////////////////////////////////////////////
    bool operator==(const Packet& right) const;
    bool operator!=(const Packet& right) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check if the packet can extract a given number of bytes
    ///
    /// This function updates accordingly the state of the packet.
    ///
    /// \param size Size to check
    ///
    /// \return True if \a size bytes can be read from the packet
    ///
    ////////////////////////////////////////////////////////////
    bool check_size(std::size_t size);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<char> m_data;          //!< Data stored in the packet
    std::size_t       m_read_pos{};     //!< Current reading position in the packet
    std::size_t       m_send_pos{};     //!< Current send position in the packet (for handling partial sends)
    bool              m_is_valid{true}; //!< Reading state of the packet
};

} // namespace cppnet


////////////////////////////////////////////////////////////
/// \class cppnet::Packet
/// \ingroup network
///
/// Packets provide a safe and easy way to serialize data,
/// in order to send it over the network using sockets
/// (cppnet::TcpSocket, cppnet::UdpSocket).
///
/// Packets solve 2 fundamental problems that arise when
/// transferring data over the network:
/// \li data is interpreted correctly according to the endianness
/// \li the bounds of the packet are preserved (one send == one receive)
///
/// The cppnet::Packet class provides both input and output modes.
/// It is designed to follow the behavior of standard C++ streams,
/// using operators >> and << to extract and insert data.
///
/// It is recommended to use only fixed-size types (like std::int32_t, etc.),
/// to avoid possible differences between the sender and the receiver.
/// Indeed, the native C++ types may have different sizes on two platforms
/// and your data may be corrupted if that happens.
///
/// Usage example:
/// \code
/// std::uint32_t x = 24;
/// std::string s = "hello";
/// double d = 5.89;
///
/// // Group the variables to send into a packet
/// cppnet::Packet packet;
/// packet << x << s << d;
///
/// // Send it over the network (socket is a valid cppnet::TcpSocket)
/// socket.send(packet);
///
/// -----------------------------------------------------------------
///
/// // Receive the packet at the other end
/// cppnet::Packet packet;
/// socket.receive(packet);
///
/// // Extract the variables contained in the packet
/// std::uint32_t x;
/// std::string s;
/// double d;
/// if (packet >> x >> s >> d)
/// {
///     // Data extracted successfully...
/// }
/// \endcode
///
/// Packets have built-in operator >> and << overloads for
/// standard types:
/// \li bool
/// \li fixed-size integer types (int[8|16|32]_t, uint[8|16|32]_t)
/// \li floating point numbers (float, double)
/// \li string types (char*, wchar_t*, std::string, std::wstring)
///
/// Like standard streams, it is also possible to define your own
/// overloads of operators >> and << in order to handle your
/// custom types.
///
/// \code
/// struct MyStruct
/// {
///     float       number;
///     std::int8_t integer;
///     std::string str;
/// };
///
/// cppnet::Packet& operator <<(cppnet::Packet& packet, const MyStruct& m)
/// {
///     return packet << m.number << m.integer << m.str;
/// }
///
/// cppnet::Packet& operator >>(cppnet::Packet& packet, MyStruct& m)
/// {
///     return packet >> m.number >> m.integer >> m.str;
/// }
/// \endcode
///
/// Packets also provide an extra feature that allows to apply
/// custom transformations to the data before it is sent,
/// and after it is received. This is typically used to
/// handle automatic compression or encryption of the data.
/// This is achieved by inheriting from cppnet::Packet, and overriding
/// the on_send and on_receive functions.
///
/// Here is an example:
/// \code
/// class ZipPacket : public cppnet::Packet
/// {
///     const void* on_send(std::size_t& size) override
///     {
///         const void* src_data = get_data();
///         std::size_t src_size = get_data_size();
///
///         return my_zip_function(src_data, src_size, &size);
///     }
///
///     void on_receive(const void* data, std::size_t size) override
///     {
///         std::size_t dst_size;
///         const void* dst_data = my_unzip_function(data, size, &dst_size);
///
///         append(dst_data, dst_size);
///     }
/// };
///
/// // Use like regular packets:
/// ZipPacket packet;
/// packet << x << s << d;
/// ...
/// \endcode
///
/// \see cppnet::TcpSocket, cppnet::UdpSocket
///
////////////////////////////////////////////////////////////
