#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>

namespace obe::Graphics
{
    /**
     * \brief A class to handle colors
     * \bind{Color}
     */
    class Color : public sf::Color
    {
    public:
        Color(uint_fast8_t r, uint_fast8_t g, uint_fast8_t b, uint_fast8_t a = 255);
        Color(const std::string& hexCode);
        void fromHex(std::string hexCode);
        void fromRgb(uint_fast8_t r, uint_fast8_t g, uint_fast8_t b, uint_fast8_t = 255);
        void fromHsv(int H, double S, double V);
    };
} // namespace obe::Graphics