#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace obe::Graphics::Shapes
{
    class Rectangle
    {
    private:
        sf::RectangleShape m_shape;

    public:
        Rectangle();
        Rectangle(const sf::RectangleShape& shape);
        Rectangle(const Rectangle& rectangle);

        operator sf::RectangleShape&();
        operator const sf::RectangleShape&() const;
    };

    inline Rectangle::Rectangle()
    {
    }

    inline Rectangle::Rectangle(const sf::RectangleShape& shape)
    {
        m_shape = shape;
    }

    inline Rectangle::Rectangle(const Rectangle& rectangle)
    {
        m_shape = rectangle.m_shape;
    }

    inline Rectangle::operator sf::RectangleShape&()
    {
        return m_shape;
    }

    inline Rectangle::operator const sf::RectangleShape&() const
    {
        return m_shape;
    }

    class Circle
    {
    private:
        sf::CircleShape m_shape;

    public:
        Circle();
        Circle(const sf::CircleShape& shape);
        Circle(const Circle& circle);

        operator sf::CircleShape&();
        operator const sf::CircleShape&() const;
    };

    inline Circle::Circle()
    {
    }

    inline Circle::Circle(const sf::CircleShape& shape)
    {
        m_shape = shape;
    }

    inline Circle::Circle(const Circle& circle)
    {
        m_shape = circle.m_shape;
    }

    inline Circle::operator sf::CircleShape&()
    {
        return m_shape;
    }

    inline Circle::operator const sf::CircleShape&() const
    {
        return m_shape;
    }

    class Polygon
    {
    private:
        sf::ConvexShape m_shape;

    public:
        Polygon();
        Polygon(const sf::ConvexShape& shape);
        Polygon(const Polygon& polygon);

        operator sf::ConvexShape&();
        operator const sf::ConvexShape&() const;
    };

    inline Polygon::Polygon()
    {
    }

    inline Polygon::Polygon(const sf::ConvexShape& shape)
    {
        m_shape = shape;
    }

    inline Polygon::Polygon(const Polygon& polygon)
    {
        m_shape = polygon.m_shape;
    }

    inline Polygon::operator sf::ConvexShape&()
    {
        return m_shape;
    }

    inline Polygon::operator const sf::ConvexShape&() const
    {
        return m_shape;
    }
}
