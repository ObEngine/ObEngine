#include <Graphics/Texture.hpp>

namespace obe::Graphics
{
    Texture::Texture()
    {
    }

    Texture::Texture(const sf::Texture& texture)
    {
        m_texture = texture;
    }

    Texture::Texture(const Texture& copy)
    {
        m_texture = copy.m_texture;
    }

    bool Texture::create(unsigned width, unsigned height)
    {
        return m_texture.create(width, height);
    }

    bool Texture::loadFromFile(const std::string& filename)
    {
        return m_texture.loadFromFile(filename);
    }

    bool Texture::loadFromFile(const std::string& filename, const Transform::Rect& rect)
    {
        const Transform::UnitVector position
            = rect.getPosition().to<Transform::Units::ScenePixels>();
        const Transform::UnitVector size
            = rect.getPosition().to<Transform::Units::ScenePixels>();
        const sf::IntRect sfRect(position.x, position.y, size.x, size.y);
        return m_texture.loadFromFile(filename, sfRect);
    }

    bool Texture::loadFromImage(const sf::Image& image)
    {
        return m_texture.loadFromImage(image);
    }

    Transform::UnitVector Texture::getSize() const
    {
        const sf::Vector2u textureSize = m_texture.getSize();
        return Transform::UnitVector(
            textureSize.x, textureSize.y, Transform::Units::ScenePixels);
    }

    void Texture::setAntiAliasing(bool antiAliasing)
    {
        m_texture.setSmooth(antiAliasing);
    }

    bool Texture::isAntiAliased() const
    {
        return m_texture.isSmooth();
    }

    void Texture::setRepeated(bool repeated)
    {
        m_texture.setRepeated(repeated);
    }

    bool Texture::isRepeated() const
    {
        return m_texture.isRepeated();
    }

    Texture& Texture::operator=(const Texture& right)
    {
        m_texture.operator=(right.m_texture);
        return *this;
    }

    Texture::operator sf::Texture&()
    {
        return m_texture;
    }

    Texture::operator const sf::Texture&() const
    {
        return m_texture;
    }
}
