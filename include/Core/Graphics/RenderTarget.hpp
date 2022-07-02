#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Transform/UnitVector.hpp"

namespace obe::graphics
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
        void draw(const sf::Vertex* vertices, std::size_t vertex_count, sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default) const;

        [[nodiscard]] transform::UnitVector get_size() const;

        operator sf::RenderTarget&() const;
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

    inline void RenderTarget::draw(const sf::Vertex* vertices, std::size_t vertex_count,
        sf::PrimitiveType type, const sf::RenderStates& states) const
    {
        m_target.draw(vertices, vertex_count, type, states);
    }

    inline transform::UnitVector RenderTarget::get_size() const
    {
        const sf::Vector2u size = m_target.getSize();
        return transform::UnitVector(size.x, size.y, transform::Units::ScenePixels);
    }

    inline RenderTarget::operator sf::RenderTarget&() const
    {
        return m_target;
    }

    inline RenderTarget::operator const sf::RenderTarget&() const
    {
        return m_target;
    }
} // namespace obe::graphics
