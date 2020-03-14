#pragma once
#include <optional>
#include <string>

#include <Transform/Rect.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace obe::Graphics
{
    class Texture
    {
    private:
        sf::Texture m_texture;

    public:
        Texture();
        Texture(const sf::Texture& texture);
        Texture(const Texture& copy);

        bool create(unsigned int width, unsigned int height);
        bool loadFromFile(const std::string& filename);
        bool loadFromFile(const std::string& filename, const Transform::Rect& rect);
        bool loadFromImage(const sf::Image& image);

        [[nodiscard]] Transform::UnitVector getSize() const;

        void setAntiAliasing(bool antiAliasing);
        [[nodiscard]] bool isAntiAliased() const;

        void setRepeated(bool repeated);
        [[nodiscard]] bool isRepeated() const;
        Texture& operator=(const Texture& right);

        operator sf::Texture&();
        operator const sf::Texture&() const;
    };
}
