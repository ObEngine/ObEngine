#include <Graphics/Shapes.hpp>

namespace obe::graphics::shapes
{
    Rectangle::Rectangle(const sf::RectangleShape& shape)
        : shape(shape)
    {
    }

    Rectangle::Rectangle(const Rectangle& rectangle)
        : shape(rectangle.shape)
    {
    }

    transform::Vector2 Rectangle::get_size() const
    {
        const sf::Vector2f pixel_size = shape.getSize();
        return transform::Vector2(pixel_size.x, pixel_size.y, transform::Units::ScenePixels);
    }

    void Rectangle::set_size(transform::Vector2 size)
    {
        const transform::Vector2 pixel_size = size.to<transform::Units::ScenePixels>();
        shape.setSize(sf::Vector2f(pixel_size.x, pixel_size.y));
    }

    Rectangle::operator sf::RectangleShape&()
    {
        return shape;
    }

    Rectangle::operator const sf::RectangleShape&() const
    {
        return shape;
    }

    void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }

    Circle::Circle(const sf::CircleShape& shape)
        : shape(shape)
    {
    }

    Circle::Circle(const Circle& circle)
        : shape(circle.shape)
    {
    }

    Circle::operator sf::CircleShape&()
    {
        return shape;
    }

    Circle::operator const sf::CircleShape&() const
    {
        return shape;
    }

    void Circle::set_radius(float radius)
    {
        shape.setRadius(radius);
    }

    float Circle::get_radius() const
    {
        return shape.getRadius();
    }

    void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }

    Polygon::Polygon(const sf::ConvexShape& shape)
        : shape(shape)
    {
    }

    Polygon::Polygon(const Polygon& polygon)
        : shape(polygon.shape)
    {
    }

    Polygon::operator sf::ConvexShape&()
    {
        return shape;
    }

    Polygon::operator const sf::ConvexShape&() const
    {
        return shape;
    }

    void Polygon::set_point_position(std::size_t index, const transform::Vector2& position)
    {
        const transform::Vector2 pixel_position = position.to<transform::Units::ScenePixels>();
        if (shape.getPointCount() <= index)
        {
            shape.setPointCount(index + 1);
        }
        shape.setPoint(index, sf::Vector2f(pixel_position.x, pixel_position.y));
    }

    transform::Vector2 Polygon::get_point_position(std::size_t index) const
    {
        const sf::Vector2f pixel_position = shape.getPoint(index);
        return transform::Vector2(
            pixel_position.x, pixel_position.y, transform::Units::ScenePixels);
    }

    void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }

    Text::Text(const RichText& shape)
        : shape(shape)
    {
    }

    Text::Text(const Text& text)
        : shape(text.shape)
    {
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

    void Text::append(const graphics::Text& text)
    {
        shape.append(text);
    }

    const Font& Text::get_font() const
    {
        return shape.get_font();
    }

    void Text::set_font(const Font& font)
    {
        shape.set_font(font);
    }

    unsigned Text::get_character_size() const
    {
        return shape.get_character_size();
    }

    void Text::set_character_size(unsigned size)
    {
        shape.set_character_size(size);
    }

    void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }

    void NinePatch::set_texture(const Texture& texture)
    {
        shape.set_texture(texture);
    }

    transform::Vector2 NinePatch::get_size() const
    {
        const sf::Vector2f pixel_size = shape.get_size();
        return transform::Vector2(pixel_size.x, pixel_size.y, transform::Units::ScenePixels);
    }

    void NinePatch::set_size(const transform::Vector2& size)
    {
        auto px_size = size.to<transform::Units::ScenePixels>();
        shape.set_size(sf::Vector2f(px_size.x, px_size.y));
    }

    void NinePatch::set_fill_color(const Color& color)
    {
        shape.set_color(color);
    }

    [[nodiscard]] Color NinePatch::get_fill_color() const
    {
        return shape.get_color();
    }

    void NinePatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }
}
