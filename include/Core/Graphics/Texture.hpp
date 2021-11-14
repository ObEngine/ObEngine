#pragma once
#include <memory>
#include <string>
#include <variant>

#include <SFML/Graphics/Texture.hpp>

namespace obe
{
    namespace Transform
    {
        class Rect;
        class UnitVector;
    }
}

namespace obe::Graphics
{
    using TextureWrapper
        = std::variant<sf::Texture, std::shared_ptr<sf::Texture>, const sf::Texture*>;

    class Texture
    {
    private:
        TextureWrapper m_texture;

        sf::Texture& getMutableTexture();
        const sf::Texture& getTexture() const;

    public:
        Texture();
        Texture(std::shared_ptr<sf::Texture> texture);
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

        void reset();

        unsigned int useCount();

        operator sf::Texture&();
        operator const sf::Texture&() const;

        Texture& operator=(const Texture& copy);
        Texture& operator=(const sf::Texture& texture);
        Texture& operator=(std::shared_ptr<sf::Texture> texture);
    };
}
