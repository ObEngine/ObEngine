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

namespace obe::graphics
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
        SizeHint m_size_hint;
        bool m_autoscaling = true;

        void render() const;

    public:
        SvgTexture(const std::string& filename);

        SvgTexture(const SvgTexture& texture);
        SvgTexture& operator=(const SvgTexture& texture);
        SvgTexture& operator=(SvgTexture&& texture) noexcept;

        [[nodiscard]] bool is_autoscaled() const;
        void set_autoscaling(bool autoscaling);
        void set_size_hint(unsigned int width, unsigned int height);

        [[nodiscard]] bool success() const;

        [[nodiscard]] const sf::Texture& get_texture() const;
        sf::Texture& get_texture();
    };

    using TextureWrapper
        = std::variant<sf::Texture, std::shared_ptr<sf::Texture>, const sf::Texture*, SvgTexture>;

    class Texture
    {
    private:
        TextureWrapper m_texture;

        sf::Texture& get_mutable_texture();
        const sf::Texture& get_texture() const;

    public:
        static Texture make_shared_texture();

        Texture();
        Texture(std::shared_ptr<sf::Texture> texture);
        Texture(const sf::Texture& texture);
        Texture(const Texture& copy);

        bool create(unsigned int width, unsigned int height);
        bool load_from_file(const std::string& filename);
        bool load_from_file(const std::string& filename, const Transform::Rect& rect);
        bool load_from_image(const sf::Image& image);

        [[nodiscard]] Transform::UnitVector get_size() const;

        void set_size_hint(unsigned int width, unsigned int height);
        [[nodiscard]] bool is_autoscaled() const;
        void set_autoscaling(bool autoscaling);

        void set_anti_aliasing(bool antiAliasing);
        [[nodiscard]] bool is_anti_aliased() const;

        void set_repeated(bool repeated);
        [[nodiscard]] bool is_repeated() const;

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
