#pragma once

#include <algorithm>
#include <string>

namespace obe::utils::base64
{
    constexpr std::string_view base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz"
                                              "0123456789+/";

    inline std::string encode(std::string const& data)
    {
        int counter = 0;
        uint32_t bit_stream = 0;
        std::string encoded;
        int offset = 0;
        for (const unsigned char c : data)
        {
            const auto num_val = static_cast<unsigned int>(c);
            offset = 16 - counter % 3 * 8;
            bit_stream += num_val << offset;
            if (offset == 16)
            {
                encoded += base64_chars.at(bit_stream >> 18 & 0x3f);
            }
            if (offset == 8)
            {
                encoded += base64_chars.at(bit_stream >> 12 & 0x3f);
            }
            if (offset == 0 && counter != 3)
            {
                encoded += base64_chars.at(bit_stream >> 6 & 0x3f);
                encoded += base64_chars.at(bit_stream & 0x3f);
                bit_stream = 0;
            }
            counter++;
        }
        if (offset == 16)
        {
            encoded += base64_chars.at(bit_stream >> 12 & 0x3f);
            encoded += "==";
        }
        if (offset == 8)
        {
            encoded += base64_chars.at(bit_stream >> 6 & 0x3f);
            encoded += '=';
        }
        return encoded;
    }

    inline std::string decode(std::string const& data)
    {
        int counter = 0;
        uint32_t bit_stream = 0;
        std::string decoded;
        int offset = 0;
        for (const unsigned char c : data)
        {
            const auto num_val = base64_chars.find(c);
            if (num_val != std::string::npos)
            {
                offset = 18 - counter % 4 * 6;
                bit_stream += num_val << offset;
                if (offset == 12)
                {
                    decoded += static_cast<char>(bit_stream >> 16 & 0xff);
                }
                if (offset == 6)
                {
                    decoded += static_cast<char>(bit_stream >> 8 & 0xff);
                }
                if (offset == 0 && counter != 4)
                {
                    decoded += static_cast<char>(bit_stream & 0xff);
                    bit_stream = 0;
                }
            }
            else if (c != '=')
            {
                return "";
            }
            counter++;
        }
        return decoded;
    }
}