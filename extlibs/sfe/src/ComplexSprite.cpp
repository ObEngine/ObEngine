#include <array>
#include <cstdlib>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <ComplexSprite.hpp>


namespace sfe
{
    ComplexSprite::ComplexSprite() :
        m_texture(nullptr),
        m_textureRect()
    {
    }

    ComplexSprite::ComplexSprite(const sf::Texture& texture) :
        m_texture(nullptr),
        m_textureRect()
    {
        setTexture(texture);
    }

    ComplexSprite::ComplexSprite(const sf::Texture& texture, const sf::IntRect& rectangle) :
        m_texture(nullptr),
        m_textureRect()
    {
        setTexture(texture);
        setTextureRect(rectangle);
    }

    void ComplexSprite::copyFromSprite(const sf::Sprite& sprite)
    {
        m_texture = sprite.getTexture();
        m_textureRect = sprite.getTextureRect();
        sf::FloatRect bounds = sprite.getLocalBounds();
        m_vertices[0].position = sf::Vector2f(0, 0);
        m_vertices[1].position = sf::Vector2f(0, bounds.height);
        m_vertices[2].position = sf::Vector2f(bounds.width, 0);
        m_vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
        this->setPosition(sprite.getPosition());
        this->setRotation(sprite.getRotation());
        this->setScale(sprite.getScale());
        this->setColor(sprite.getColor());
        updateTexCoords();
    }

    void ComplexSprite::setTexture(const sf::Texture& texture, bool resetRect)
    {
        if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
            setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
        m_texture = &texture;
    }

    void ComplexSprite::setTextureRect(const sf::IntRect& rectangle)
    {
        if (rectangle != m_textureRect)
        {
            m_textureRect = rectangle;
            updatePositions();
            updateTexCoords();
        }
    }

    void ComplexSprite::setColor(const sf::Color& color)
    {
        m_vertices[0].color = color;
        m_vertices[1].color = color;
        m_vertices[2].color = color;
        m_vertices[3].color = color;
    }

    const sf::Texture* ComplexSprite::getTexture() const
    {
        return m_texture;
    }

    const sf::IntRect& ComplexSprite::getTextureRect() const
    {
        return m_textureRect;
    }

    const sf::Color& ComplexSprite::getColor() const
    {
        return m_vertices[0].color;
    }

    sf::FloatRect ComplexSprite::getLocalBounds() const
    {
        float width = static_cast<float>(abs(m_textureRect.width));
        float height = static_cast<float>(abs(m_textureRect.height));

        return sf::FloatRect(0.f, 0.f, width, height);
    }

    sf::FloatRect ComplexSprite::getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

    void ComplexSprite::setVertices(std::array<sf::Vertex, 4>& vertices)
    {
        m_vertices[0].position = vertices[0].position;
        m_vertices[1].position = vertices[1].position;
        m_vertices[2].position = vertices[2].position;
        m_vertices[3].position = vertices[3].position;
    }

    void ComplexSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (m_texture)
        {
            states.transform *= getTransform();
            states.texture = m_texture;
            target.draw(m_vertices, 4, sf::TrianglesStrip, states);
        }
    }

    void ComplexSprite::updatePositions()
    {
        sf::FloatRect bounds = getLocalBounds();

        m_vertices[0].position = sf::Vector2f(0, 0);
        m_vertices[1].position = sf::Vector2f(0, bounds.height);
        m_vertices[2].position = sf::Vector2f(bounds.width, 0);
        m_vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
    }

    void ComplexSprite::updateTexCoords()
    {
        float left = static_cast<float>(m_textureRect.left);
        float right = left + m_textureRect.width;
        float top = static_cast<float>(m_textureRect.top);
        float bottom = top + m_textureRect.height;

        m_vertices[0].texCoords = sf::Vector2f(left, top);
        m_vertices[1].texCoords = sf::Vector2f(left, bottom);
        m_vertices[2].texCoords = sf::Vector2f(right, top);
        m_vertices[3].texCoords = sf::Vector2f(right, bottom);
    }
}
