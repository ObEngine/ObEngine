#include <Graphics/Color.hpp>

#include <array>
#include <sstream>

namespace obe::Graphics
{
    Color::Color(const uint_fast8_t r, const uint_fast8_t g, const uint_fast8_t b, const uint_fast8_t a)
    {
        this->fromRgb(r, g, b, a);
    }

    Color::Color(const std::string& hexCode)
    {
        this->fromHex(hexCode);
    }

    void Color::fromRgb(const uint_fast8_t r, const uint_fast8_t g, const uint_fast8_t b, const uint_fast8_t a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    void Color::fromHex(std::string hexCode)
    {
        std::array<unsigned char, 3> rgb {};
        std::stringstream ss;
        std::string str;

        if (hexCode[0] == '#')
            hexCode.erase(0,1);

        const int size = hexCode.size();

        for (unsigned int i = 0; i < 3; i++) 
        {
            if (size == 3) { str = std::string(2, hexCode[i]); }
            else if (size == 6) { str = hexCode.substr(i * 2, 2); }
            else { break; }
            ss << std::hex << str;
            ss >> rgb[i];
            ss.clear();
        }

        this->r = rgb[0];
        this->g = rgb[1];
        this->b = rgb[2];
    }
}