#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace obe::Graphics
{
    class RenderTarget
    {
    private:
        sf::RenderTarget& m_target;

    public:
        RenderTarget(sf::RenderTarget& target);
        RenderTarget(sf::RenderWindow& window);

        void draw(const sf::Drawable& drawable,
            const sf::RenderStates& states = sf::RenderStates::Default) const;
        void draw(const sf::Vertex* vertices, std::size_t vertexCount,
            sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default) const;

        operator sf::RenderTarget&();
        operator const sf::RenderTarget&() const;
    };

    inline RenderTarget::RenderTarget(sf::RenderTarget& target)
        : m_target(target)
    {
    }

    inline RenderTarget::RenderTarget(sf::RenderWindow& window)
        : m_target(window)
    {
    }

    inline void RenderTarget::draw(
        const sf::Drawable& drawable, const sf::RenderStates& states) const
    {
        m_target.draw(drawable, states);
    }

    inline void RenderTarget::draw(const sf::Vertex* vertices, std::size_t vertexCount,
        sf::PrimitiveType type, const sf::RenderStates& states) const
    {
        m_target.draw(vertices, vertexCount, type, states);
    }

    inline RenderTarget::operator sf::RenderTarget&()
    {
        return m_target;
    }

    inline RenderTarget::operator const sf::RenderTarget&() const
    {
        return m_target;
    }
}
