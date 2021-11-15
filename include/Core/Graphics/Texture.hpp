#pragma once
#include <memory>
#include <string>
#include <variant>

#include <lunasvg.h>

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
    class SvgTexture
    {
    private:
        std::string m_path;
        std::unique_ptr<lunasvg::Document> m_document;
        std::unique_ptr<sf::Texture> m_texture;
        struct SizeHint
        {
            int width = 0;
            int height = 0;
        };
        SizeHint m_sizeHint;
        bool m_autoscaling = true;

        void render() const;

    public:
        SvgTexture(const std::string& filename);

        SvgTexture(const SvgTexture& texture);
        SvgTexture& operator=(const SvgTexture& texture);
        SvgTexture& operator=(SvgTexture&& texture);

        [[nodiscard]] bool getAutoscaling() const;
        void setAutoscaling(bool autoscaling);
        void setSizeHint(unsigned int width, unsigned int height);

        bool success() const;

        const sf::Texture& getTexture() const;
        sf::Texture& getTexture();
    };

    using TextureWrapper
        = std::variant<sf::Texture, std::shared_ptr<sf::Texture>, const sf::Texture*, SvgTexture>;

    class Texture
    {
    private:
        TextureWrapper m_texture;

        sf::Texture& getMutableTexture();
        const sf::Texture& getTexture() const;

    public:
        static Texture MakeSharedTexture();

        Texture();
        Texture(std::shared_ptr<sf::Texture> texture);
        Texture(const sf::Texture& texture);
        Texture(const Texture& copy);

        bool create(unsigned int width, unsigned int height);
        bool loadFromFile(const std::string& filename);
        bool loadFromFile(const std::string& filename, const Transform::Rect& rect);
        bool loadFromImage(const sf::Image& image);

        [[nodiscard]] Transform::UnitVector getSize() const;

        void setSizeHint(unsigned int width, unsigned int height);
        [[nodiscard]] bool getAutoscaling() const;
        void setAutoscaling(bool autoscaling);

        void setAntiAliasing(bool antiAliasing);
        [[nodiscard]] bool isAntiAliased() const;

        void setRepeated(bool repeated);
        [[nodiscard]] bool isRepeated() const;

        void reset();

        unsigned int useCount() const;

        bool isVector() const;
        bool isBitmap() const;

        operator sf::Texture&();
        operator const sf::Texture&() const;

        Texture& operator=(const Texture& copy);
        Texture& operator=(const sf::Texture& texture);
        Texture& operator=(std::shared_ptr<sf::Texture> texture);
    };
}
