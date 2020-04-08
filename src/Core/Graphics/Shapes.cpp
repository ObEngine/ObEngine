#include <Graphics/Shapes.hpp>

namespace obe::Graphics::Shapes
{
    Rectangle::Rectangle(const sf::RectangleShape& shape)
    {
        this->shape = shape;
    }

    Rectangle::Rectangle(const Rectangle& rectangle)
    {
        this->shape = rectangle.shape;
    }

    Transform::UnitVector Rectangle::getSize() const
    {
        const sf::Vector2f pixelSize = shape.getSize();
        return Transform::UnitVector(
            pixelSize.x, pixelSize.y, Transform::Units::ScenePixels);
    }

    void Rectangle::setSize(Transform::UnitVector size)
    {
        const Transform::UnitVector pixelSize = size.to<Transform::Units::ScenePixels>();
        shape.setSize(sf::Vector2f(pixelSize.x, pixelSize.y));
    }

    Rectangle::operator sf::RectangleShape&()
    {
        return shape;
    }

    Rectangle::operator const sf::RectangleShape&() const
    {
        return shape;
    }

    Circle::Circle(const sf::CircleShape& shape)
    {
        this->shape = shape;
    }

    Circle::Circle(const Circle& circle)
    {
        this->shape = circle.shape;
    }

    Circle::operator sf::CircleShape&()
    {
        return shape;
    }

    Circle::operator const sf::CircleShape&() const
    {
        return shape;
    }

    void Circle::setRadius(float radius)
    {
        shape.setRadius(radius);
    }

    float Circle::getRadius() const
    {
        return shape.getRadius();
    }

    Polygon::Polygon(const sf::ConvexShape& shape)
    {
        this->shape = shape;
    }

    Polygon::Polygon(const Polygon& polygon)
    {
        this->shape = polygon.shape;
    }

    Polygon::operator sf::ConvexShape&()
    {
        return shape;
    }

    Polygon::operator const sf::ConvexShape&() const
    {
        return shape;
    }

    Text::Text(const RichText& shape)
    {
        this->shape = shape;
    }

    Text::Text(const Text& text)
    {
        this->shape = text.shape;
    }

    Text::operator RichText&()
    {
        return shape;
    }

    Text::operator const RichText&() const
    {
        return shape;
    }

    void Text::clear()
    {
        shape.clear();
    }

    void Text::append(const Graphics::Text& text)
    {
        shape.append(text);
    }

    const Font& Text::getFont() const
    {
        return shape.getFont();
    }

    void Text::setFont(const Font& font)
    {
        shape.setFont(font);
    }

    unsigned Text::getCharacterSize() const
    {
        return shape.getCharacterSize();
    }

    void Text::setCharacterSize(unsigned size)
    {
        shape.setCharacterSize(size);
    }
}
