#include <Graphics/Color.hpp>

#include <array>
#include <sstream>

namespace obe::Graphics
{
    Color::Color(const uint_fast8_t r, const uint_fast8_t g, const uint_fast8_t b,
        const uint_fast8_t a)
    {
        this->fromRgb(r, g, b, a);
    }

    Color::Color(const std::string& hexCode)
    {
        this->fromHex(hexCode);
    }

    void Color::fromRgb(const uint_fast8_t r, const uint_fast8_t g, const uint_fast8_t b,
        const uint_fast8_t a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    void Color::fromHsv(int H, double S, double V)
    {
        double C = S * V;
        double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
        double m = V - C;
        double Rs, Gs, Bs;

        if (H >= 0 && H < 60)
        {
            Rs = C;
            Gs = X;
            Bs = 0;
        }
        else if (H >= 60 && H < 120)
        {
            Rs = X;
            Gs = C;
            Bs = 0;
        }
        else if (H >= 120 && H < 180)
        {
            Rs = 0;
            Gs = C;
            Bs = X;
        }
        else if (H >= 180 && H < 240)
        {
            Rs = 0;
            Gs = X;
            Bs = C;
        }
        else if (H >= 240 && H < 300)
        {
            Rs = X;
            Gs = 0;
            Bs = C;
        }
        else
        {
            Rs = C;
            Gs = 0;
            Bs = X;
        }

        this->r = (Rs + m) * 255;
        this->g = (Gs + m) * 255;
        this->b = (Bs + m) * 255;
    }

    void Color::fromHex(std::string hexCode)
    {
        std::array<unsigned char, 3> rgb {};
        std::stringstream ss;
        std::string str;

        if (hexCode[0] == '#')
        {
            hexCode.erase(0, 1);
        }

        const int size = hexCode.size();

        for (unsigned int i = 0; i < 3; i++)
        {
            if (size == 3)
            {
                str = std::string(2, hexCode[i]);
            }
            else if (size == 6)
            {
                str = hexCode.substr(i * 2, 2);
            }
            else
            {
                break;
            }
            ss << std::hex << str;
            ss >> rgb[i];
            ss.clear();
        }

        this->r = rgb[0];
        this->g = rgb[1];
        this->b = rgb[2];
    }
} // namespace obe::Graphics