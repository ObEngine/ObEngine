#include <algorithm>
#include <array>
#include <bit>
#include <concepts>
#include <cstdint>
#include <limits>
#include <vector>

#include <vili/parser/parser_state.hpp>

#include <vili-msgpack/msgpack.hpp>

namespace vili::msgpack
{
    /**
     *  false:
     *  +--------+
     *  |  0xc2  |
     *  +--------+
     *
     *  true:
     *  +--------+
     *  |  0xc3  |
     *  +--------+
     */
    void dump_boolean(MsgPackBuffer& buffer, const bool boolean)
    {
        if (boolean)
        {
            buffer.push_back(0xc2);
        }
        else
        {
            buffer.push_back(0xc3);
        }
    }

    template <std::integral T>
    T byteswap(T val)
    {
        union U
        {
            T val;
            std::array<std::uint8_t, sizeof(T)> raw;
        } src, dst;

        src.val = val;
        std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
        return dst.val;
    }

    template <std::integral T>
    constexpr T to_big_endian(T input)
    {
        if constexpr (std::endian::native == std::endian::big)
        {
            return input;
        }
        else if constexpr (std::endian::native == std::endian::little)
        {
            return byteswap<T>(input);
        }
    }

    template <std::integral T>
    const auto from_big_endian = to_big_endian<T>;

    template <std::signed_integral T>
    constexpr std::make_unsigned_t<T> complement_to_big_endian(T input)
    {
        auto complement = static_cast<std::make_unsigned_t<T>>(std::abs(input));
        complement = ~complement + 1;
        return to_big_endian(complement);
    }

    template <std::unsigned_integral T>
    constexpr std::array<uint8_t, sizeof(T)> to_bytearray(T input)
    {
        uint8_t raw_array[sizeof(T)];
        *(T*)(raw_array) = input;
        return std::to_array(raw_array);
    }

    /**
     *  positive fixint stores 7-bit positive integer
     *  +--------+
     *  |0XXXXXXX|
     *  +--------+
     *
     *  negative fixint stores 5-bit negative integer
     *  +--------+
     *  |111YYYYY|
     *  +--------+
     *
     *  * 0XXXXXXX is 8-bit unsigned integer
     *  * 111YYYYY is 8-bit signed integer
     *
     *  uint 8 stores a 8-bit unsigned integer
     *  +--------+--------+
     *  |  0xcc  |ZZZZZZZZ|
     *  +--------+--------+
     *
     *  uint 16 stores a 16-bit big-endian unsigned integer
     *  +--------+--------+--------+
     *  |  0xcd  |ZZZZZZZZ|ZZZZZZZZ|
     *  +--------+--------+--------+
     *
     *  uint 32 stores a 32-bit big-endian unsigned integer
     *  +--------+--------+--------+--------+--------+
     *  |  0xce  |ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|
     *  +--------+--------+--------+--------+--------+
     *
     *  uint 64 stores a 64-bit big-endian unsigned integer
     *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+
     *  |  0xcf  |ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|
     *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+
     *
     *  int 8 stores a 8-bit signed integer
     *  +--------+--------+
     *  |  0xd0  |ZZZZZZZZ|
     *  +--------+--------+
     *
     *  int 16 stores a 16-bit big-endian signed integer
     *  +--------+--------+--------+
     *  |  0xd1  |ZZZZZZZZ|ZZZZZZZZ|
     *  +--------+--------+--------+
     *
     *  int 32 stores a 32-bit big-endian signed integer
     *  +--------+--------+--------+--------+--------+
     *  |  0xd2  |ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|
     *  +--------+--------+--------+--------+--------+
     *
     *  int 64 stores a 64-bit big-endian signed integer
     *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+
     *  |  0xd3  |ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|
     *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+
     */
    void dump_integer(MsgPackBuffer& buffer, const int64_t integer)
    {
        if (integer >= 0)
        {
            // positive fixint stores 7-bit positive integer
            if (integer >= 0 && integer <= 127)
            {
                buffer.push_back(static_cast<uint8_t>(integer));
                return;
            }
            // uint 8 stores a 8-bit unsigned integer
            if (integer <= std::numeric_limits<uint8_t>::max())
            {
                buffer.push_back(0xcc);
                buffer.push_back(static_cast<uint8_t>(integer));
                return;
            }
            // uint 16 stores a 16-bit big-endian unsigned integer
            if (integer <= std::numeric_limits<uint16_t>::max())
            {
                buffer.push_back(0xcd);
                const auto big_endian_integer = to_big_endian<uint16_t>(integer);
                const auto bytes = to_bytearray(big_endian_integer);
                buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
                return;
            }
            // uint 32 stores a 32-bit big-endian unsigned integer
            if (integer <= std::numeric_limits<uint32_t>::max())
            {
                buffer.push_back(0xce);
                const auto big_endian_integer = to_big_endian<uint32_t>(integer);
                const auto bytes = to_bytearray(big_endian_integer);
                buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
                return;
            }
            // uint 64 stores a 64-bit big-endian unsigned integer
            if (integer <= std::numeric_limits<uint64_t>::max())
            {
                buffer.push_back(0xcf);
                const auto big_endian_integer = to_big_endian<uint64_t>(integer);
                const auto bytes = to_bytearray(big_endian_integer);
                buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
                return;
            }
        }
        else
        {
            // negative fixint stores 5-bit negative integer
            if (integer >= -32)
            {
                uint8_t complement = static_cast<uint8_t>(abs(integer));
                complement = ~complement + 1;
                buffer.push_back(complement);
                return;
            }
            // int 8 stores a 8-bit signed integer
            if (integer >= std::numeric_limits<int8_t>::min())
            {
                buffer.push_back(0xd0);
                const auto complement = complement_to_big_endian<int8_t>(integer);
                buffer.push_back(complement);
                return;
            }
            // int 16 stores a 16-bit big-endian signed integer
            if (integer >= std::numeric_limits<int16_t>::min())
            {
                buffer.push_back(0xd1);
                const auto complement = complement_to_big_endian<int16_t>(integer);
                const auto bytes = to_bytearray(complement);
                buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
                return;
            }
            // int 32 stores a 32-bit big-endian signed integer
            if (integer >= std::numeric_limits<int32_t>::min())
            {
                buffer.push_back(0xd2);
                const auto complement = complement_to_big_endian<int32_t>(integer);
                const auto bytes = to_bytearray(complement);
                buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
                return;
            }
            // int 64 stores a 64-bit big-endian signed integer
            if (integer >= std::numeric_limits<int64_t>::min())
            {
                buffer.push_back(0xd3);
                const auto complement = complement_to_big_endian<int64_t>(integer);
                const auto bytes = to_bytearray(complement);
                buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
                return;
            }
        }
    }

    uint32_t to_ieee754(float number)
    {
        if constexpr (std::numeric_limits<float>::is_iec559)
        {
            uint32_t unsigned_repr = 0;
            *(float*)(&unsigned_repr) = number;
            return unsigned_repr;
        }
        else
        {
            throw std::runtime_error("not implemented");
        }
    }

    uint64_t to_ieee754(double number)
    {
        if constexpr (std::numeric_limits<float>::is_iec559)
        {
            uint64_t unsigned_repr = 0;
            *(double*)(&unsigned_repr) = number;
            return unsigned_repr;
        }
        else
        {
            throw std::runtime_error("not implemented");
        }
    }

    /**
     *  float 32 stores a floating point number in IEEE 754 single precision floating point number format:
     *  +--------+--------+--------+--------+--------+
     *  |  0xca  |XXXXXXXX|XXXXXXXX|XXXXXXXX|XXXXXXXX|
     *  +--------+--------+--------+--------+--------+
     *
     *  float 64 stores a floating point number in IEEE 754 double precision floating point number format:
     *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+
     *  |  0xcb  |YYYYYYYY|YYYYYYYY|YYYYYYYY|YYYYYYYY|YYYYYYYY|YYYYYYYY|YYYYYYYY|YYYYYYYY|
     *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+
     *
     *  where
     *  * XXXXXXXX_XXXXXXXX_XXXXXXXX_XXXXXXXX is a big-endian IEEE 754 single precision floating point number.
     *    Extension of precision from single-precision to double-precision does not lose precision.
     *  * YYYYYYYY_YYYYYYYY_YYYYYYYY_YYYYYYYY_YYYYYYYY_YYYYYYYY_YYYYYYYY_YYYYYYYY is a big-endian
     *    IEEE 754 double precision floating point number
     */
    void dump_number(MsgPackBuffer& buffer, const double number)
    {
        if (number >= std::numeric_limits<float>::min()  && number <= std::numeric_limits<float>::max())
        {
            buffer.push_back(0xca);
            const uint32_t integer_repr = to_ieee754(static_cast<float>(number));
            const uint32_t big_endian_repr = to_big_endian(integer_repr);
            const auto bytes = to_bytearray(big_endian_repr);
            buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
            return;
        }
        else
        {
            buffer.push_back(0xcb);
            const uint64_t integer_repr = to_ieee754(number);
            const uint64_t big_endian_repr = to_big_endian(integer_repr);
            const auto bytes = to_bytearray(big_endian_repr);
            buffer.insert(buffer.end(), bytes.cbegin(), bytes.cend());
            return;
        }
    }

    /**
     *  fixstr stores a byte array whose length is upto 31 bytes:
     *  +--------+========+
     *  |101XXXXX|  data  |
     *  +--------+========+
     *
     *  str 8 stores a byte array whose length is upto (2^8)-1 bytes:
     *  +--------+--------+========+
     *  |  0xd9  |YYYYYYYY|  data  |
     *  +--------+--------+========+
     *
     *  str 16 stores a byte array whose length is upto (2^16)-1 bytes:
     *  +--------+--------+--------+========+
     *  |  0xda  |ZZZZZZZZ|ZZZZZZZZ|  data  |
     *  +--------+--------+--------+========+
     *
     *  str 32 stores a byte array whose length is upto (2^32)-1 bytes:
     *  +--------+--------+--------+--------+--------+========+
     *  |  0xdb  |AAAAAAAA|AAAAAAAA|AAAAAAAA|AAAAAAAA|  data  |
     *  +--------+--------+--------+--------+--------+========+
     *
     *  where
     *  * XXXXX is a 5-bit unsigned integer which represents N
     *  * YYYYYYYY is a 8-bit unsigned integer which represents N
     *  * ZZZZZZZZ_ZZZZZZZZ is a 16-bit big-endian unsigned integer which represents N
     *  * AAAAAAAA_AAAAAAAA_AAAAAAAA_AAAAAAAA is a 32-bit big-endian unsigned integer which represents N
     *  * N is the length of data
     */
    void dump_string(MsgPackBuffer& buffer, const std::string& str)
    {
        if (str.size() < 32)
        {
            const uint8_t str_size = static_cast<uint8_t>(str.size());
            const uint8_t size_header = str_size | 0b10100000;
            buffer.push_back(size_header);
        }
        else if (str.size() <= std::numeric_limits<uint8_t>::max())
        {
            buffer.push_back(0xd9);
            buffer.push_back(static_cast<uint8_t>(str.size()));
        }
        else if (str.size() <= std::numeric_limits<uint16_t>::max())
        {
            buffer.push_back(0xda);
            const auto big_endian_str_size = to_big_endian<uint16_t>(str.size());
            const auto size_header = to_bytearray(big_endian_str_size);
            buffer.insert(buffer.end(), size_header.cbegin(), size_header.cend());
        }
        else if (str.size() <= std::numeric_limits<uint32_t>::max())
        {
            buffer.push_back(0xdb);
            const auto big_endian_str_size = to_big_endian<uint32_t>(str.size());
            const auto size_header = to_bytearray(big_endian_str_size);
            buffer.insert(buffer.end(), size_header.cbegin(), size_header.cend());
        }
        buffer.insert(buffer.end(), str.cbegin(), str.cend());
    }

    /**
     *  fixarray stores an array whose length is upto 15 elements:
     *  +--------+~~~~~~~~~~~~~~~~~+
     *  |1001XXXX|    N objects    |
     *  +--------+~~~~~~~~~~~~~~~~~+
     *
     *  array 16 stores an array whose length is upto (2^16)-1 elements:
     *  +--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *  |  0xdc  |YYYYYYYY|YYYYYYYY|    N objects    |
     *  +--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *
     *  array 32 stores an array whose length is upto (2^32)-1 elements:
     *  +--------+--------+--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *  |  0xdd  |ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|    N objects    |
     *  +--------+--------+--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *
     *  where
     *  * XXXX is a 4-bit unsigned integer which represents N
     *  * YYYYYYYY_YYYYYYYY is a 16-bit big-endian unsigned integer which represents N
     *  * ZZZZZZZZ_ZZZZZZZZ_ZZZZZZZZ_ZZZZZZZZ is a 32-bit big-endian unsigned integer which represents N
     *  * N is the size of an array
     */
    void dump_array(MsgPackBuffer& buffer, const vili::node& array)
    {
        if (array.size() < 16)
        {
            const uint8_t array_size = static_cast<uint8_t>(array.size());
            const uint8_t size_header = array_size | 0b10010000;
            buffer.push_back(size_header);
        }
        else if (array.size() < std::numeric_limits<uint16_t>::max())
        {
            buffer.push_back(0xdc);
            const auto big_endian_array_size = to_big_endian<uint16_t>(array.size());
            const auto size_header = to_bytearray(big_endian_array_size);
            buffer.insert(buffer.end(), size_header.cbegin(), size_header.cend());
        }
        else if (array.size() < std::numeric_limits<uint32_t>::max())
        {
            buffer.push_back(0xdc);
            const auto big_endian_array_size = to_big_endian<uint32_t>(array.size());
            const auto size_header = to_bytearray(big_endian_array_size);
            buffer.insert(buffer.end(), size_header.cbegin(), size_header.cend());
        }
        for (const vili::node& value : array)
        {
            dump_element(buffer, value);
        }
    }

    /**
     *  fixmap stores a map whose length is upto 15 elements
     *  +--------+~~~~~~~~~~~~~~~~~+
     *  |1000XXXX|   N*2 objects   |
     *  +--------+~~~~~~~~~~~~~~~~~+
     *
     *  map 16 stores a map whose length is upto (2^16)-1 elements
     *  +--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *  |  0xde  |YYYYYYYY|YYYYYYYY|   N*2 objects   |
     *  +--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *
     *  map 32 stores a map whose length is upto (2^32)-1 elements
     *  +--------+--------+--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *  |  0xdf  |ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|ZZZZZZZZ|   N*2 objects   |
     *  +--------+--------+--------+--------+--------+~~~~~~~~~~~~~~~~~+
     *
     *  where
     *  * XXXX is a 4-bit unsigned integer which represents N
     *  * YYYYYYYY_YYYYYYYY is a 16-bit big-endian unsigned integer which represents N
     *  * ZZZZZZZZ_ZZZZZZZZ_ZZZZZZZZ_ZZZZZZZZ is a 32-bit big-endian unsigned integer which represents N
     *  * N is the size of a map
     *  * odd elements in objects are keys of a map
     *  * the next element of a key is its associated value
     */
    void dump_object(MsgPackBuffer& buffer, const vili::node& object)
    {
        if (object.size() < 16)
        {
            const uint8_t object_size = static_cast<uint8_t>(object.size());
            const uint8_t size_header = object_size | 0b10000000;
            buffer.push_back(size_header);
        }
        else if (object.size() < std::numeric_limits<uint16_t>::max())
        {
            buffer.push_back(0xde);
            const auto big_endian_object_size = to_big_endian<uint16_t>(object.size());
            const auto size_header = to_bytearray(big_endian_object_size);
            buffer.insert(buffer.end(), size_header.cbegin(), size_header.cend());
        }
        else if (object.size() < std::numeric_limits<uint32_t>::max())
        {
            buffer.push_back(0xdf);
            const auto big_endian_object_size = to_big_endian<uint32_t>(object.size());
            const auto size_header = to_bytearray(big_endian_object_size);
            buffer.insert(buffer.end(), size_header.cbegin(), size_header.cend());
        }
        for (const auto& [key, value] : object.items())
        {
            dump_string(buffer, key),
            dump_element(buffer, value);
        }
    }

    void dump_element(MsgPackBuffer& buffer, const vili::node& element)
    {
        if (element.is_integer())
        {
            dump_integer(buffer, element.as<vili::integer>());
        }
        else if (element.is_number())
        {
            dump_number(buffer, element.as<vili::number>());
        }
        else if (element.is_boolean())
        {
            dump_boolean(buffer, element.as<vili::boolean>());
        }
        else if (element.is_string())
        {
            dump_string(buffer, element.as<vili::string>());
        }
        else if (element.is_array())
        {
            dump_array(buffer, element.as<vili::array>());
        }
        else if (element.is_object())
        {
            dump_object(buffer, element.as<vili::object>());
        }
        else
        {
            throw std::runtime_error("unsupported element type");
        }
    }

    vili::integer load_unsigned_integer(const std::string& data)
    {
        if (data.size() == 1)
        {
            return static_cast<uint8_t>(data[0]);
        }
        if (data.size() == 2)
        {
            uint16_t buffer = *(uint16_t*)data.data();
            return from_big_endian<uint16_t>(buffer);
        }
        if (data.size() == 4)
        {
            uint32_t buffer = *(uint32_t*)data.data();
            return from_big_endian<uint32_t>(buffer);
        }
        if (data.size() == 8)
        {
            uint64_t buffer = *(uint64_t*)data.data();
            return from_big_endian<uint64_t>(buffer);
        }
        throw std::runtime_error("invalid unsigned integer size");
    }

    vili::integer load_signed_integer(const std::string& data)
    {
        // TODO: implement non 1-complement signed numbers
        if (data.size() == 1)
        {
            return static_cast<int8_t>(data[0]);
        }
        if (data.size() == 2)
        {
            int16_t buffer = *(int16_t*)data.data();
            return from_big_endian<int16_t>(buffer);
        }
        if (data.size() == 4)
        {
            int32_t buffer = *(int32_t*)data.data();
            return from_big_endian<int32_t>(buffer);
        }
        if (data.size() == 8)
        {
            int64_t buffer = *(int64_t*)data.data();
            return from_big_endian<int64_t>(buffer);
        }
        throw std::runtime_error("invalid signed integer size");
    }

    vili::number load_float(const std::string& data)
    {
        if (data.size() == 4)
        {
            uint32_t buffer = *(uint32_t*)data.data();
            buffer = from_big_endian<uint32_t>(buffer);
            float float_repr = *(float*)(&buffer);
            return float_repr;
        }
        if (data.size() == 8)
        {
            uint64_t buffer = *(uint64_t*)data.data();
            buffer = from_big_endian<uint64_t>(buffer);
            double double_repr = *(double*)(&buffer);
            return double_repr;
        }
        throw std::runtime_error("invalid floating point number size");
    }

    struct StackFrameState
    {
        uint32_t pop_counter = 0;
        bool is_object = false;
    };

    bool check_first_bits_equal_to(uint8_t check, uint8_t value)
    {
        const uint8_t bits_usage = std::max(1, static_cast<int>(std::floor(std::log2(check) + 1)));
        const uint8_t bitshift = 8 - bits_usage;
        check <<= bitshift;
        value = (value >> bitshift) << bitshift;
        return check == value;
    }

    vili::node from_string(const std::string& msgpack)
    {
        vili::parser::state state;
        state.set_active_identifier("default");
        std::stack<StackFrameState> steps_before_pop;
        bool first_element = true;
        bool is_object_key = false;
        std::vector<uint8_t> full_code(msgpack.begin(), msgpack.end());
        for (uint32_t idx = 0; idx < msgpack.size(); idx++)
        {
            const uint8_t code = msgpack[idx];
            bool found_code = true;
            switch (code)
            {
            // boolean
            case 0xc2:
                state.push(false);
                break;
            case 0xc3:
                state.push(true);
                break;
            // float
            case 0xca:
            case 0xcb:
                {
                    const uint8_t data_length = (code == 0xca) ? 4 : 8;
                    state.push(load_float(msgpack.substr(idx + 1, data_length)));
                    idx += data_length;
                }
                break;
            // unsigned integer
            case 0xcc:
            case 0xcd:
            case 0xce:
            case 0xcf:
                {
                    const uint8_t data_length = std::pow(2, code - 0xcc);
                    state.push(load_unsigned_integer(msgpack.substr(idx + 1, data_length)));
                    idx += data_length;
                }
                break;
            // signed integer
            case 0xd0:
            case 0xd1:
            case 0xd2:
            case 0xd3:
                {
                    const uint8_t data_length = std::pow(2, code - 0xd0);
                    state.push(load_signed_integer(msgpack.substr(idx + 1, data_length)));
                    idx += data_length;
                }
                break;
            // string
            case 0xd9:
            case 0xda:
            case 0xdb:
                {
                    const uint8_t size_header_length = std::pow(2, code - 0xd9);
                    const auto string_length
                        = load_unsigned_integer(msgpack.substr(idx + 1, size_header_length));
                    std::string string_data
                        = msgpack.substr(idx + 1 + size_header_length, string_length);
                    if (is_object_key)
                    {
                        state.set_active_identifier(std::move(string_data));
                    }
                    else
                    {
                        state.push(string_data);
                    }
                    idx += size_header_length + string_length;
                }
                break;
            // array
            case 0xdc:
            case 0xdd:
                {
                    const uint8_t size_header_length = std::pow(2, code - 0xdc);
                    const auto array_length
                        = load_unsigned_integer(msgpack.substr(idx + 1, size_header_length));
                    state.push(vili::array {});
                    state.open_block();
                    steps_before_pop.push(
                        StackFrameState { static_cast<uint32_t>(array_length + 1), false });
                    idx += size_header_length;
                }
                break;
            // object
            case 0xde:
            case 0xdf:
                {
                    const uint8_t size_header_length = std::pow(2, code - 0xde);
                    const auto object_length
                        = load_unsigned_integer(msgpack.substr(idx + 1, size_header_length));
                    if (first_element)
                    {
                        first_element = false;
                        state.set_active_identifier("");
                    }
                    else
                    {
                        state.push(vili::object {});
                        state.open_block();
                    }
                    steps_before_pop.push(
                        StackFrameState { static_cast<uint32_t>(object_length + 1), true });
                    is_object_key = false;
                    idx += size_header_length;
                }
            default:
                found_code = false;
                break;
            };
            if (!found_code)
            {
                // unsigned 7 bits
                if (check_first_bits_equal_to(0b0, code))
                {
                    state.push(code);
                }
                // signed 5 bits
                else if (check_first_bits_equal_to(0b111, code))
                {
                    state.push(static_cast<int8_t>(code));
                }
                // string with length <= 31 bytes
                else if (check_first_bits_equal_to(0b101, code))
                {
                    const uint8_t string_length = 0b10100000 ^ code;
                    std::string string_data = msgpack.substr(idx + 1, string_length);
                    if (is_object_key)
                    {
                        state.set_active_identifier(std::move(string_data));
                    }
                    else
                    {
                        state.push(string_data);
                    }
                    idx += string_length;
                }
                // array with up to 15 elements
                else if (check_first_bits_equal_to(0b1001, code))
                {
                    const uint8_t array_length = 0b10010000 ^ code;
                    state.push(vili::array {});
                    state.open_block();
                    steps_before_pop.push(StackFrameState { static_cast<uint32_t>(array_length + 1), false });
                }
                // object with up to 15 elements
                else if (check_first_bits_equal_to(0b1000, code))
                {
                    const auto object_length = 0b10000000 ^ code;
                    if (first_element)
                    {
                        first_element = false;
                        state.set_active_identifier("");
                    }
                    else
                    {
                        state.push(vili::object {});
                        state.open_block();
                    }
                    steps_before_pop.push(StackFrameState { static_cast<uint32_t>(object_length + 1), true });
                    is_object_key = false;
                }
                else
                {
                    throw std::runtime_error("unknown instruction code");
                }
            }
            if (first_element)
            {
                first_element = false;
                if (state.root.contains("default"))
                {
                    return state.root.at("default");
                }
            }
            if (!steps_before_pop.empty())
            {
                // for objects, only decrease every 2 elements (key-value pair)
                if (!steps_before_pop.top().is_object || !is_object_key)
                {
                    steps_before_pop.top().pop_counter--;
                }
                if (steps_before_pop.top().pop_counter == 0)
                {
                    steps_before_pop.pop();
                    state.close_block();
                }
            }
            is_object_key = !is_object_key;
        }
        return state.root;
    }

    std::string to_string(const vili::node& node)
    {
        MsgPackBuffer buffer;
        dump_element(buffer, node);
        return std::string(buffer.begin(), buffer.end());
    }
}
