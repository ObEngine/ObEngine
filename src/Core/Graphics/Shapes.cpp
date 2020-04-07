#include <Graphics/Shapes.hpp>

namespace obe::Graphics::Shapes
{
    inline Rectangle::Rectangle()
    {
    }

    inline Rectangle::Rectangle(const sf::RectangleShape& shape)
    {
        this->shape = shape;
    }

    inline Rectangle::Rectangle(const Rectangle& rectangle)
    {
        this->shape = rectangle.shape;
    }

    inline Rectangle::operator sf::RectangleShape&()
    {
        return shape;
    }

    inline Rectangle::operator const sf::RectangleShape&() const
    {
        return shape;
    }

    inline Circle::Circle()
    {
    }

    inline Circle::Circle(const sf::CircleShape& shape)
    {
        this->shape = shape;
    }

    inline Circle::Circle(const Circle& circle)
    {
        this->shape = circle.shape;
    }

    inline Circle::operator sf::CircleShape&()
    {
        return shape;
    }

    inline Circle::operator const sf::CircleShape&() const
    {
        return shape;
    }

    inline Polygon::Polygon()
    {
    }

    inline Polygon::Polygon(const sf::ConvexShape& shape)
    {
        this->shape = shape;
    }

    inline Polygon::Polygon(const Polygon& polygon)
    {
        this->shape = polygon.shape;
    }

    inline Polygon::operator sf::ConvexShape&()
    {
        return shape;
    }

    inline Polygon::operator const sf::ConvexShape&() const
    {
        return shape;
    }
}