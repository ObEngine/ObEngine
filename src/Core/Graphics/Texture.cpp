#include <Graphics/Exceptions.hpp>
#include <Graphics/Texture.hpp>

#include "Debug/Logger.hpp"
#include <iostream>

namespace obe::Graphics
{
    Texture::Texture()
    {
        m_texture = sf::Texture {};
    }

    Texture::Texture(std::shared_ptr<sf::Texture> texture)
    {
        m_texture = texture;
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
        else if (std::holds_alternative<std::shared_ptr<sf::Texture>>(copy.m_texture))
        {
            m_texture = std::get<std::shared_ptr<sf::Texture>>(copy.m_texture);
        }
        else if (std::holds_alternative<const sf::Texture*>(copy.m_texture))
        {
            m_texture = std::get<const sf::Texture*>(copy.m_texture);
        }
    }

    Texture::~Texture()
    {
    }

    bool Texture::create(unsigned width, unsigned height)
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).create(width, height);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->create(
                width, height);
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            throw Exceptions::ReadOnlyTexture("create", EXC_INFO);
        }
        return false;
    }

    bool Texture::loadFromFile(const std::string& filename)
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).loadFromFile(filename);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->loadFromFile(
                filename);
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            throw Exceptions::ReadOnlyTexture("loadFromFile", EXC_INFO);
        }
        return false;
    }

    bool Texture::loadFromFile(const std::string& filename, const Transform::Rect& rect)
    {
        const Transform::UnitVector position
            = rect.getPosition().to<Transform::Units::ScenePixels>();
        const Transform::UnitVector size
            = rect.getPosition().to<Transform::Units::ScenePixels>();
        const sf::IntRect sfRect(position.x, position.y, size.x, size.y);
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).loadFromFile(filename, sfRect);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->loadFromFile(
                filename, sfRect);
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            throw Exceptions::ReadOnlyTexture("loadFromFile", EXC_INFO);
        }
        return false;
    }

    bool Texture::loadFromImage(const sf::Image& image)
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).loadFromImage(image);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->loadFromImage(
                image);
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            throw Exceptions::ReadOnlyTexture("loadFromImage", EXC_INFO);
        }
        return false;
    }

    Transform::UnitVector Texture::getSize() const
    {
        sf::Vector2u textureSize;
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            textureSize = std::get<sf::Texture>(m_texture).getSize();
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            textureSize = std::get<std::shared_ptr<sf::Texture>>(m_texture)->getSize();
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            textureSize = std::get<const sf::Texture*>(m_texture)->getSize();
        }
        return Transform::UnitVector(
            textureSize.x, textureSize.y, Transform::Units::ScenePixels);
    }

    void Texture::setAntiAliasing(bool antiAliasing)
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).setSmooth(antiAliasing);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->setSmooth(
                antiAliasing);
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            throw Exceptions::ReadOnlyTexture("setAntiAliasing", EXC_INFO);
        }
    }

    bool Texture::isAntiAliased() const
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).isSmooth();
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->isSmooth();
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            return std::get<const sf::Texture*>(m_texture)->isSmooth();
        }
        return false;
    }

    void Texture::setRepeated(bool repeated)
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).setRepeated(repeated);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->setRepeated(
                repeated);
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            throw Exceptions::ReadOnlyTexture("setRepeated", EXC_INFO);
        }
    }

    bool Texture::isRepeated() const
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture).isRepeated();
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return std::get<std::shared_ptr<sf::Texture>>(m_texture)->isRepeated();
        }
        if (std::holds_alternative<const sf::Texture*>(m_texture))
        {
            return std::get<const sf::Texture*>(m_texture)->isRepeated();
        }
        return false;
    }

    void Texture::reset()
    {
        m_texture = sf::Texture {};
    }

    unsigned Texture::useCount()
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
        return false;
    }

    Texture::operator sf::Texture&()
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return *std::get<std::shared_ptr<sf::Texture>>(m_texture);
        }
        throw Exceptions::ReadOnlyTexture("operator sf::Texture&", EXC_INFO);
    }

    Texture::operator const sf::Texture&() const
    {
        if (std::holds_alternative<sf::Texture>(m_texture))
        {
            return std::get<sf::Texture>(m_texture);
        }
        if (std::holds_alternative<std::shared_ptr<sf::Texture>>(m_texture))
        {
            return *std::get<std::shared_ptr<sf::Texture>>(m_texture);
        }
        return *std::get<const sf::Texture*>(m_texture);
    }

    Texture& Texture::operator=(const Texture& copy)
    {
        if (std::holds_alternative<sf::Texture>(copy.m_texture))
        {
            m_texture = &std::get<sf::Texture>(copy.m_texture);
        }
        else if (std::holds_alternative<std::shared_ptr<sf::Texture>>(copy.m_texture))
        {
            m_texture = std::get<std::shared_ptr<sf::Texture>>(copy.m_texture);
        }
        else if (std::holds_alternative<const sf::Texture*>(copy.m_texture))
        {
            m_texture = std::get<const sf::Texture*>(copy.m_texture);
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
}
