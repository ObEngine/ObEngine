#include <Graphics/Color.hpp>

#include <array>
#include <cmath>
#include <sstream>
#include <unordered_map>

namespace obe::Graphics
{
    Color Color::AliceBlue(240, 248, 255);
    Color Color::AntiqueWhite(250, 235, 215);
    Color Color::Aqua(0, 255, 255);
    Color Color::Aquamarine(127, 255, 212);
    Color Color::Azure(240, 255, 255);
    Color Color::Beige(245, 245, 220);
    Color Color::Bisque(255, 228, 196);
    Color Color::Black(0, 0, 0);
    Color Color::BlanchedAlmond(255, 235, 205);
    Color Color::Blue(0, 0, 255);
    Color Color::BlueViolet(138, 43, 226);
    Color Color::Brown(165, 42, 42);
    Color Color::BurlyWood(222, 184, 135);
    Color Color::CadetBlue(95, 158, 160);
    Color Color::Chartreuse(127, 255, 0);
    Color Color::Chocolate(210, 105, 30);
    Color Color::Coral(255, 127, 80);
    Color Color::CornflowerBlue(100, 149, 237);
    Color Color::Cornsilk(255, 248, 220);
    Color Color::Crimson(220, 20, 60);
    Color Color::Cyan(0, 255, 255);
    Color Color::DarkBlue(0, 0, 139);
    Color Color::DarkCyan(0, 139, 139);
    Color Color::DarkGoldenrod(184, 134, 11);
    Color Color::DarkGray(169, 169, 169);
    Color Color::DarkGreen(0, 100, 0);
    Color Color::DarkKhaki(189, 183, 107);
    Color Color::DarkMagenta(139, 0, 139);
    Color Color::DarkOliveGreen(85, 107, 47);
    Color Color::DarkOrange(255, 140, 0);
    Color Color::DarkOrchid(153, 50, 204);
    Color Color::DarkRed(139, 0, 0);
    Color Color::DarkSalmon(233, 150, 122);
    Color Color::DarkSeaGreen(143, 188, 139);
    Color Color::DarkSlateBlue(72, 61, 139);
    Color Color::DarkSlateGray(47, 79, 79);
    Color Color::DarkTurquoise(0, 206, 209);
    Color Color::DarkViolet(148, 0, 211);
    Color Color::DeepPink(255, 20, 147);
    Color Color::DeepSkyBlue(0, 191, 255);
    Color Color::DimGray(105, 105, 105);
    Color Color::DodgerBlue(30, 144, 255);
    Color Color::FireBrick(178, 34, 34);
    Color Color::FloralWhite(255, 250, 240);
    Color Color::ForestGreen(34, 139, 34);
    Color Color::Fuchsia(255, 0, 255);
    Color Color::Gainsboro(220, 220, 220);
    Color Color::GhostWhite(248, 248, 255);
    Color Color::Gold(255, 215, 0);
    Color Color::Goldenrod(218, 165, 32);
    Color Color::Gray(128, 128, 128);
    Color Color::Green(0, 128, 0);
    Color Color::GreenYellow(173, 255, 47);
    Color Color::HoneyDew(240, 255, 240);
    Color Color::HotPink(255, 105, 180);
    Color Color::IndianRed(205, 92, 92);
    Color Color::Indigo(75, 0, 130);
    Color Color::Ivory(255, 255, 240);
    Color Color::Khaki(240, 230, 140);
    Color Color::Lavender(230, 230, 250);
    Color Color::LavenderBlush(255, 240, 245);
    Color Color::LawnGreen(124, 252, 0);
    Color Color::LemonChiffon(255, 250, 205);
    Color Color::LightBlue(173, 216, 230);
    Color Color::LightCoral(240, 128, 128);
    Color Color::LightCyan(224, 255, 255);
    Color Color::LightGoldenrodYellow(250, 250, 210);
    Color Color::LightGray(211, 211, 211);
    Color Color::LightGreen(144, 238, 144);
    Color Color::LightPink(255, 182, 193);
    Color Color::LightSalmon(255, 160, 122);
    Color Color::LightSeaGreen(32, 178, 170);
    Color Color::LightSkyBlue(135, 206, 250);
    Color Color::LightSlateGray(119, 136, 153);
    Color Color::LightSteelBlue(176, 196, 222);
    Color Color::LightYellow(255, 255, 224);
    Color Color::Lime(0, 255, 0);
    Color Color::LimeGreen(50, 205, 50);
    Color Color::Linen(250, 240, 230);
    Color Color::Magenta(255, 0, 255);
    Color Color::Maroon(128, 0, 0);
    Color Color::MediumAquamarine(102, 205, 170);
    Color Color::MediumBlue(0, 0, 205);
    Color Color::MediumOrchid(186, 85, 211);
    Color Color::MediumPurple(147, 112, 219);
    Color Color::MediumSeaGreen(60, 179, 113);
    Color Color::MediumSlateBlue(123, 104, 238);
    Color Color::MediumSpringGreen(0, 250, 154);
    Color Color::MediumTurquoise(72, 209, 204);
    Color Color::MediumVioletRed(199, 21, 133);
    Color Color::MidnightBlue(25, 25, 112);
    Color Color::MintCream(245, 255, 250);
    Color Color::MistyRose(255, 228, 225);
    Color Color::Moccasin(255, 228, 181);
    Color Color::NavajoWhite(255, 222, 173);
    Color Color::Navy(0, 0, 128);
    Color Color::OldLace(253, 245, 230);
    Color Color::Olive(128, 128, 0);
    Color Color::OliveDrab(107, 142, 35);
    Color Color::Orange(255, 165, 0);
    Color Color::OrangeRed(255, 69, 0);
    Color Color::Orchid(218, 112, 214);
    Color Color::PaleGoldenrod(238, 232, 170);
    Color Color::PaleGreen(152, 251, 152);
    Color Color::PaleTurquoise(175, 238, 238);
    Color Color::PaleVioletRed(219, 112, 147);
    Color Color::PapayaWhip(255, 239, 213);
    Color Color::PeachPuff(255, 218, 185);
    Color Color::Peru(205, 133, 63);
    Color Color::Pink(255, 192, 203);
    Color Color::Plum(221, 160, 221);
    Color Color::PowderBlue(176, 224, 230);
    Color Color::Purple(128, 0, 128);
    Color Color::RebeccaPurple(102, 51, 153);
    Color Color::Red(255, 0, 0);
    Color Color::RosyBrown(188, 143, 143);
    Color Color::RoyalBlue(65, 105, 225);
    Color Color::SaddleBrown(139, 69, 19);
    Color Color::Salmon(250, 128, 114);
    Color Color::SandyBrown(244, 164, 96);
    Color Color::SeaGreen(46, 139, 87);
    Color Color::SeaShell(255, 245, 238);
    Color Color::Sienna(160, 82, 45);
    Color Color::Silver(192, 192, 192);
    Color Color::SkyBlue(135, 206, 235);
    Color Color::SlateBlue(106, 90, 205);
    Color Color::SlateGray(112, 128, 144);
    Color Color::Snow(255, 250, 250);
    Color Color::SpringGreen(0, 255, 127);
    Color Color::SteelBlue(70, 130, 180);
    Color Color::Tan(210, 180, 140);
    Color Color::Teal(0, 128, 128);
    Color Color::Thistle(216, 191, 216);
    Color Color::Tomato(255, 99, 71);
    Color Color::Turquoise(64, 224, 208);
    Color Color::Violet(238, 130, 238);
    Color Color::Wheat(245, 222, 179);
    Color Color::White(255, 255, 255);
    Color Color::WhiteSmoke(245, 245, 245);
    Color Color::Yellow(255, 255, 0);
    Color Color::YellowGreen(154, 205, 50);

    std::unordered_map<std::string, Color> ColorNames = { { "AliceBlue",
                                                              Color::AliceBlue },
        { "AntiqueWhite", Color::AntiqueWhite }, { "Aqua", Color::Aqua },
        { "Aquamarine", Color::Aquamarine }, { "Azure", Color::Azure },
        { "Beige", Color::Beige }, { "Bisque", Color::Bisque }, { "Black", Color::Black },
        { "BlanchedAlmond", Color::BlanchedAlmond }, { "Blue", Color::Blue },
        { "BlueViolet", Color::BlueViolet }, { "Brown", Color::Brown },
        { "BurlyWood", Color::BurlyWood }, { "CadetBlue", Color::CadetBlue },
        { "Chartreuse", Color::Chartreuse }, { "Chocolate", Color::Chocolate },
        { "Coral", Color::Coral }, { "CornflowerBlue", Color::CornflowerBlue },
        { "Cornsilk", Color::Cornsilk }, { "Crimson", Color::Crimson },
        { "Cyan", Color::Cyan }, { "DarkBlue", Color::DarkBlue },
        { "DarkCyan", Color::DarkCyan }, { "DarkGoldenrod", Color::DarkGoldenrod },
        { "DarkGray", Color::DarkGray }, { "DarkGreen", Color::DarkGreen },
        { "DarkKhaki", Color::DarkKhaki }, { "DarkMagenta", Color::DarkMagenta },
        { "DarkOliveGreen", Color::DarkOliveGreen }, { "DarkOrange", Color::DarkOrange },
        { "DarkOrchid", Color::DarkOrchid }, { "DarkRed", Color::DarkRed },
        { "DarkSalmon", Color::DarkSalmon }, { "DarkSeaGreen", Color::DarkSeaGreen },
        { "DarkSlateBlue", Color::DarkSlateBlue },
        { "DarkSlateGray", Color::DarkSlateGray },
        { "DarkTurquoise", Color::DarkTurquoise }, { "DarkViolet", Color::DarkViolet },
        { "DeepPink", Color::DeepPink }, { "DeepSkyBlue", Color::DeepSkyBlue },
        { "DimGray", Color::DimGray }, { "DodgerBlue", Color::DodgerBlue },
        { "FireBrick", Color::FireBrick }, { "FloralWhite", Color::FloralWhite },
        { "ForestGreen", Color::ForestGreen }, { "Fuchsia", Color::Fuchsia },
        { "Gainsboro", Color::Gainsboro }, { "GhostWhite", Color::GhostWhite },
        { "Gold", Color::Gold }, { "Goldenrod", Color::Goldenrod },
        { "Gray", Color::Gray }, { "Green", Color::Green },
        { "GreenYellow", Color::GreenYellow }, { "HoneyDew", Color::HoneyDew },
        { "HotPink", Color::HotPink }, { "IndianRed", Color::IndianRed },
        { "Indigo", Color::Indigo }, { "Ivory", Color::Ivory }, { "Khaki", Color::Khaki },
        { "Lavender", Color::Lavender }, { "LavenderBlush", Color::LavenderBlush },
        { "LawnGreen", Color::LawnGreen }, { "LemonChiffon", Color::LemonChiffon },
        { "LightBlue", Color::LightBlue }, { "LightCoral", Color::LightCoral },
        { "LightCyan", Color::LightCyan },
        { "LightGoldenrodYellow", Color::LightGoldenrodYellow },
        { "LightGray", Color::LightGray }, { "LightGreen", Color::LightGreen },
        { "LightPink", Color::LightPink }, { "LightSalmon", Color::LightSalmon },
        { "LightSalmon", Color::LightSalmon }, { "LightSeaGreen", Color::LightSeaGreen },
        { "LightSkyBlue", Color::LightSkyBlue },
        { "LightSlateGray", Color::LightSlateGray },
        { "LightSteelBlue", Color::LightSteelBlue },
        { "LightYellow", Color::LightYellow }, { "Lime", Color::Lime },
        { "LimeGreen", Color::LimeGreen }, { "Linen", Color::Linen },
        { "Magenta", Color::Magenta }, { "Maroon", Color::Maroon },
        { "MediumAquamarine", Color::MediumAquamarine },
        { "MediumBlue", Color::MediumBlue }, { "MediumOrchid", Color::MediumOrchid },
        { "MediumPurple", Color::MediumPurple },
        { "MediumSeaGreen", Color::MediumSeaGreen },
        { "MediumSlateBlue", Color::MediumSlateBlue },
        { "MediumSlateBlue", Color::MediumSlateBlue },
        { "MediumSpringGreen", Color::MediumSpringGreen },
        { "MediumTurquoise", Color::MediumTurquoise },
        { "MediumVioletRed", Color::MediumVioletRed },
        { "MidnightBlue", Color::MidnightBlue }, { "MintCream", Color::MintCream },
        { "MistyRose", Color::MistyRose }, { "Moccasin", Color::Moccasin },
        { "NavajoWhite", Color::NavajoWhite }, { "Navy", Color::Navy },
        { "OldLace", Color::OldLace }, { "Olive", Color::Olive },
        { "OliveDrab", Color::OliveDrab }, { "Orange", Color::Orange },
        { "OrangeRed", Color::OrangeRed }, { "Orchid", Color::Orchid },
        { "PaleGoldenrod", Color::PaleGoldenrod }, { "PaleGreen", Color::PaleGreen },
        { "PaleTurquoise", Color::PaleTurquoise },
        { "PaleVioletRed", Color::PaleVioletRed }, { "PapayaWhip", Color::PapayaWhip },
        { "PeachPuff", Color::PeachPuff }, { "Peru", Color::Peru },
        { "Pink", Color::Pink }, { "Plum", Color::Plum },
        { "PowderBlue", Color::PowderBlue }, { "Purple", Color::Purple },
        { "RebeccaPurple", Color::RebeccaPurple }, { "Red", Color::Red },
        { "RosyBrown", Color::RosyBrown }, { "RoyalBlue", Color::RoyalBlue },
        { "SaddleBrown", Color::SaddleBrown }, { "Salmon", Color::Salmon },
        { "SandyBrown", Color::SandyBrown }, { "SeaGreen", Color::SeaGreen },
        { "SeaShell", Color::SeaShell }, { "Sienna", Color::Sienna },
        { "Silver", Color::Silver }, { "SkyBlue", Color::SkyBlue },
        { "SlateBlue", Color::SlateBlue }, { "SlateGray", Color::SlateGray },
        { "Snow", Color::Snow }, { "SpringGreen", Color::SpringGreen },
        { "SteelBlue", Color::SteelBlue }, { "Tan", Color::Tan }, { "Teal", Color::Teal },
        { "Thistle", Color::Thistle }, { "Tomato", Color::Tomato },
        { "Turquoise", Color::Turquoise }, { "Violet", Color::Violet },
        { "Wheat", Color::Wheat }, { "White", Color::White },
        { "WhiteSmoke", Color::WhiteSmoke }, { "Yellow", Color::Yellow },
        { "YellowGreen", Color::YellowGreen } };

    Color::Color()
    {
    }

    Color::Color(const uint_fast8_t r, const uint_fast8_t g, const uint_fast8_t b,
        const uint_fast8_t a)
    {
        this->fromRgb(r, g, b, a);
    }

    Color::Color(const std::string& nameOrHex)
    {
        this->fromString(nameOrHex);
    }

    Color::Color(const Color& color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }

    Color::Color(const sf::Color& color)
    {
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
        this->a = color.a;
    }

    void Color::fromString(std::string string)
    {
        if (const auto& color = ColorNames.find(string); color != ColorNames.end())
        {
            this->fromName(string);
        }
        else
        {
            this->fromHex(string);
        }
    }

    void Color::fromName(std::string name)
    {
        if (const auto& color = ColorNames.find(name); color != ColorNames.end())
        {
            this->r = color->second.r;
            this->g = color->second.g;
            this->b = color->second.b;
            this->a = color->second.a;
        }
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
        const double C = S * V;
        const double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
        const double m = V - C;
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

    uint32_t Color::toInteger() const
    {
        return (r << 24) + (g << 16) + (b << 8) + (a);
    }

    void Color::fromHex(std::string hexCode)
    {
        std::array<unsigned short, 3> rgb {};
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

    Color Color::operator+(const Color& color) const
    {

        return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    }

    void Color::operator+=(const Color& color)
    {

        r += color.r;
        g += color.g;
        b += color.b;
        a += color.a;
    }

    Color Color::operator-(const Color& color) const
    {

        return Color(r - color.r, g - color.g, b - color.b, a - color.a);
    }

    void Color::operator-=(const Color& color)
    {

        r -= color.r;
        g -= color.g;
        b -= color.b;
        a -= color.a;
    }

    Color Color::operator*(const Color& color) const
    {

        return Color(r * color.r, g * color.g, b * color.b, a * color.a);
    }

    Color Color::operator*(double value) const
    {

        return Color(static_cast<double>(r) * value, static_cast<double>(g) * value,
            static_cast<double>(b) * value, static_cast<double>(a) * value);
    }

    void Color::operator*=(const Color& color)
    {

        r = r * color.r;
        g = g * color.g;
        b = b * color.b;
        a = a * color.a;
    }

    void Color::operator*=(double value)
    {

        r = static_cast<double>(r) * value;
        g = static_cast<double>(g) * value;
        b = static_cast<double>(b) * value;
        a = static_cast<double>(a) * value;
    }

    Color Color::operator/(const Color& color) const
    {

        return Color(r / color.r, g / color.g, b / color.b, a / color.a);
    }

    Color Color::operator/(double value) const
    {

        return Color(static_cast<double>(r) / value, static_cast<double>(g) / value,
            static_cast<double>(b) / value, static_cast<double>(a) / value);
    }

    void Color::operator/=(const Color& color)
    {

        r = static_cast<float>(r) / static_cast<float>(color.r);
        g = static_cast<float>(g) / static_cast<float>(color.g);
        b = static_cast<float>(b) / static_cast<float>(color.b);
        a = static_cast<float>(a) / static_cast<float>(color.a);
    }

    void Color::operator/=(double value)
    {

        if (value != 0)
        {
            r = static_cast<double>(r) / value;
            g = static_cast<double>(g) / value;
            b = static_cast<double>(b) / value;
            a = static_cast<double>(a) / value;
        }
        else
        {
            r = 1;
            g = 1;
            b = 1;
            a = 1;
        }
    };

    Color Color::operator-() const
    {

        return Color(255 - r, 255 - g, 255 - b, 255 - a);
    }

    Color::operator sf::Color() const
    {
        return sf::Color(r, g, b, a);
    }

    std::ostream& operator<<(std::ostream& os, const Color& color)
    {
        os << "Color(" << int(color.r) << ", " << int(color.g) << ", " << int(color.b)
           << ", " << int(color.a) << ")";
        return os;
    }
} // namespace obe::Graphics
