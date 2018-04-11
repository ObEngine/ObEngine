#pragma once

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "ComplexTransformable.hpp"


namespace sfe
{
    class Texture;

    class ComplexSprite : public sf::Drawable, public ComplexTransformable
    {
    public:
        ComplexSprite();
        explicit ComplexSprite(const sf::Texture& texture);
        ComplexSprite(const sf::Texture& texture, const sf::IntRect& rectangle);
        void copyFromSprite(const sf::Sprite& sprite);
        void setTexture(const sf::Texture& texture, bool resetRect = false);
        void setTextureRect(const sf::IntRect& rectangle);
        void setColor(const sf::Color& color);
        const sf::Texture* getTexture() const;
        const sf::IntRect& getTextureRect() const;
        const sf::Color& getColor() const;
        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;
        void setVertices(std::array<sf::Vertex, 4>& vertices);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void updatePositions();
        void updateTexCoords();
        sf::Vertex m_vertices[4]; ///< Vertices defining the sprite's geometry
        const sf::Texture* m_texture; ///< Texture of the sprite
        sf::IntRect m_textureRect; ///< Rectangle defining the area of the source texture to display
    };
}
