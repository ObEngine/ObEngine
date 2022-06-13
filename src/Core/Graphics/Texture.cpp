#include <lunasvg.h>

#include <Graphics/Exceptions.hpp>
#include <Graphics/Texture.hpp>
#include <Transform/Rect.hpp>
#include <Utils/Visitor.hpp>

namespace obe::graphics
{
    namespace
    {
        sf::IntRect toSfRect(const Transform::Rect& rect)
        {
            const Transform::UnitVector position
                = rect.getPosition().to<Transform::Units::ScenePixels>();
            const Transform::UnitVector size
                = rect.getPosition().to<Transform::Units::ScenePixels>();
            const sf::IntRect sfRect(position.x, position.y, size.x, size.y);
            return sfRect;
        }
    }

    void SvgTexture::render() const
    {
        if (!success())
        {
            return;
        }
        const auto bitmap = m_document->renderToBitmap(m_size_hint.width, m_size_hint.height);
        sf::Image image;
        image.create(bitmap.width(), bitmap.height(), bitmap.data());
        m_texture->loadFromImage(image);
    }

    SvgTexture::SvgTexture(const std::string& filename) : m_path(filename)
    {
        m_document = lunasvg::Document::loadFromFile(filename);
        m_texture = std::make_unique<sf::Texture>();
        render();
    }

    SvgTexture::SvgTexture(const SvgTexture& texture) : SvgTexture(texture.m_path)
    {
        m_size_hint.width = texture.m_size_hint.width;
        m_size_hint.height = texture.m_size_hint.height;
    }

    SvgTexture& SvgTexture::operator=(const SvgTexture& texture)
    {
        m_path = texture.m_path;
        m_document = lunasvg::Document::loadFromFile(m_path);
        m_size_hint.width = texture.m_size_hint.width;
        m_size_hint.height = texture.m_size_hint.height;
        render();

        return *this;
    }

    SvgTexture& SvgTexture::operator=(SvgTexture&& texture) noexcept
    {
        m_path = std::move(texture.m_path);
        m_document = std::move(texture.m_document);
        m_texture = std::move(texture.m_texture);
        m_size_hint.width = texture.m_size_hint.width;
        m_size_hint.height = texture.m_size_hint.height;
        render();

        return *this;
    }

    bool SvgTexture::is_autoscaled() const
    {
        return m_autoscaling;
    }

    void SvgTexture::set_autoscaling(const bool autoscaling)
    {
        m_autoscaling = autoscaling;
    }

    void SvgTexture::set_size_hint(unsigned width, unsigned height)
    {
        if (m_size_hint.width != width || m_size_hint.height != height)
        {
            m_size_hint.width = width;
            m_size_hint.height = height;
            if (m_autoscaling)
            {
                render();
            }
        }
    }

    bool SvgTexture::success() const
    {
        return static_cast<bool>(m_document);
    }

    const sf::Texture& SvgTexture::get_texture() const
    {
        return *m_texture;
    }

    sf::Texture& SvgTexture::get_texture()
    {
        return *m_texture;
    }

    sf::Texture& Texture::get_mutable_texture()
    {
        constexpr static obe::Utils::Visitor visitor {
            [](sf::Texture& texture) -> sf::Texture& { return texture; },
            [](std::shared_ptr<sf::Texture>& texture) -> sf::Texture& { return *texture; },
            [](const sf::Texture*) -> sf::Texture& {
                throw exceptions::ReadOnlyTexture("create", EXC_INFO);
            },
            [](SvgTexture& texture) -> sf::Texture& { return texture.get_texture(); }
        };
        return std::visit(visitor, m_texture);
    }

    const sf::Texture& Texture::get_texture() const
    {
        constexpr static obe::Utils::Visitor visitor {
            [](const sf::Texture& texture) -> const sf::Texture& { return texture; },
            [](const std::shared_ptr<sf::Texture>& texture) -> const sf::Texture& {
                return *texture;
            },
            [](const sf::Texture* texture) -> const sf::Texture& { return *texture; },
            [](const SvgTexture& texture) -> const sf::Texture& { return texture.get_texture(); }
        };
        return std::visit(visitor, m_texture);
    }

    Texture Texture::make_shared_texture()
    {
        const std::shared_ptr<sf::Texture> empty = std::make_shared<sf::Texture>();
        return Texture(empty);
    }

    Texture::Texture()
    {
        m_texture = sf::Texture {};
        static_assert(std::is_same_v<decltype(m_texture), TextureWrapper>, "");
    }

    Texture::Texture(std::shared_ptr<sf::Texture> texture)
        : m_texture(texture)
    {
    }

    Texture::Texture(const sf::Texture& texture)
    {
        m_texture = &texture;
    }

    Texture::Texture(const Texture& copy)
    {
        if (std::holds_alternative<sf::Texture>(copy.m_texture))
        {
            m_texture = &std::get<sf::Texture>(copy.m_texture);
        }
        else
        {
            m_texture = copy.m_texture;
        }
    }

    bool Texture::create(unsigned width, unsigned height)
    {
        return get_mutable_texture().create(width, height);
    }

    bool Texture::load_from_file(const std::string& filename)
    {
        if (Utils::String::endsWith(filename, ".svg"))
        {
            m_texture = SvgTexture(filename);
            return std::get<SvgTexture>(m_texture).success();
        }
        return get_mutable_texture().loadFromFile(filename);
    }

    bool Texture::load_from_file(const std::string& filename, const Transform::Rect& rect)
    {
        const sf::IntRect sfRect = toSfRect(rect);
        if (Utils::String::endsWith(filename, ".svg"))
        {
            m_texture = SvgTexture(filename);
            // TODO: Implement load_from_file(path, rect)
            return std::get<SvgTexture>(m_texture).success();
        }
        return get_mutable_texture().loadFromFile(filename, sfRect);
    }

    bool Texture::load_from_image(const sf::Image& image)
    {
        return get_mutable_texture().loadFromImage(image);
    }

    Transform::UnitVector Texture::get_size() const
    {
        const sf::Vector2u textureSize = get_texture().getSize();
        return Transform::UnitVector(textureSize.x, textureSize.y, Transform::Units::ScenePixels);
    }

    void Texture::set_size_hint(unsigned width, unsigned height)
    {
        if (std::holds_alternative<SvgTexture>(m_texture))
        {
            std::get<SvgTexture>(m_texture).set_size_hint(width, height);
        }
    }

    bool Texture::is_autoscaled() const
    {
        if (std::holds_alternative<SvgTexture>(m_texture))
        {
            return std::get<SvgTexture>(m_texture).is_autoscaled();
        }
        return false;
    }

    void Texture::set_autoscaling(bool autoscaling)
    {
        if (std::holds_alternative<SvgTexture>(m_texture))
        {
            return std::get<SvgTexture>(m_texture).set_autoscaling(autoscaling);
        }
    }

    void Texture::set_anti_aliasing(bool antiAliasing)
    {
        get_mutable_texture().setSmooth(antiAliasing);
    }

    bool Texture::is_anti_aliased() const
    {
        return get_texture().isSmooth();
    }

    void Texture::set_repeated(bool repeated)
    {
        get_mutable_texture().setRepeated(repeated);
    }

    bool Texture::is_repeated() const
    {
        return get_texture().isRepeated();
    }

    void Texture::reset()
    {
        m_texture = sf::Texture {};
    }

    unsigned int Texture::useCount() const
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return 1;
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture).use_count();
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            return 0;
        }
        return 0;
    }

    bool Texture::isVector() const
    {
        return std::holds_alternative<SvgTexture>(m_texture);
    }

    bool Texture::isBitmap() const
    {
        return !isVector();
    }

    Texture::operator sf::Texture&()
    {
        return get_mutable_texture();
    }

    Texture::operator const sf::Texture&() const
    {
        return get_texture();
    }

    Texture& Texture::operator=(const Texture& copy)
    {
        if (std::holds_alternative<sf::Texture>(copy.m_texture))
        {
            m_texture = &std::get<sf::Texture>(copy.m_texture);
        }
        else
        {
            m_texture = copy.m_texture;
        }
        return *this;
    }

    Texture& Texture::operator=(const sf::Texture& texture)
    {
        m_texture = &texture;
        return *this;
    }

    Texture& Texture::operator=(std::shared_ptr<sf::Texture> texture)
    {
        m_texture = texture;
        return *this;
    }
} //namespace obe::graphics
