#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Texture.hpp>
#include <Transform/Rect.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::graphics::shapes
{
    template <class T>
    class BaseShape : public sf::Drawable
    {
    public:
        void set_position(Transform::UnitVector position);
        [[nodiscard]] Transform::Rect get_local_bounds() const;
        [[nodiscard]] Transform::Rect get_global_bounds() const;
        void set_rotation(float angle);
        void set_scale(const Transform::UnitVector& factors);
        void set_origin(const Transform::UnitVector& origin);
        [[nodiscard]] Transform::UnitVector get_position() const;
        [[nodiscard]] float get_rotation() const;
        [[nodiscard]] Transform::UnitVector get_scale() const;
        [[nodiscard]] Transform::UnitVector get_origin() const;
        void move(const Transform::UnitVector& offset);
        void rotate(float angle);
        void scale(const Transform::UnitVector& factor);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    };

    template <class T>
    class Shape : public sf::Drawable
    {
    public:
        void set_texture(const Texture& texture);
        void set_texture_rect(const Transform::Rect& rect);
        void set_position(Transform::UnitVector position);
        void set_fill_color(const Color& color);
        void set_outline_color(const Color& color);
        void set_outline_thickness(float thickness);
        [[nodiscard]] Color get_fill_color() const;
        [[nodiscard]] Color get_outline_color() const;
        [[nodiscard]] float get_outline_thickness() const;
        [[nodiscard]] std::size_t get_point_count() const;
        [[nodiscard]] Transform::UnitVector get_point(std::size_t index) const;
        [[nodiscard]] Transform::Rect get_local_bounds() const;
        [[nodiscard]] Transform::Rect get_global_bounds() const;
        void set_rotation(float angle);
        void set_scale(const Transform::UnitVector& factors);
        void set_origin(const Transform::UnitVector& origin);
        [[nodiscard]] Transform::UnitVector get_position() const;
        [[nodiscard]] float get_rotation() const;
        [[nodiscard]] Transform::UnitVector get_scale() const;
        [[nodiscard]] Transform::UnitVector get_origin() const;
        void move(const Transform::UnitVector& offset);
        void rotate(float angle);
        void scale(const Transform::UnitVector& factor);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    };

    // BaseShape methods
    template <class T>
    void BaseShape<T>::set_position(Transform::UnitVector position)
    {
        const Transform::UnitVector pixel_position = position.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setPosition(sf::Vector2f(pixel_position.x, pixel_position.y));
    }

    template <class T>
    Transform::Rect BaseShape<T>::get_local_bounds() const
    {
        const sf::FloatRect bounds = static_cast<const T&>(*this).shape.getLocalBounds();
        const auto position
            = Transform::UnitVector(bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size
            = Transform::UnitVector(bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T>
    Transform::Rect BaseShape<T>::get_global_bounds() const
    {
        const sf::FloatRect bounds = static_cast<const T&>(*this).shape.getGlobalBounds();
        const auto position
            = Transform::UnitVector(bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size
            = Transform::UnitVector(bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T>
    void BaseShape<T>::set_rotation(float angle)
    {
        static_cast<T&>(*this).shape.setRotation(angle);
    }

    template <class T>
    void BaseShape<T>::set_scale(const Transform::UnitVector& factors)
    {
        const auto pixel_scale = factors.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setScale(sf::Vector2f(pixel_scale.x, pixel_scale.y));
    }

    template <class T>
    void BaseShape<T>::set_origin(const Transform::UnitVector& origin)
    {
        const Transform::UnitVector pixel_origin = origin.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setOrigin(sf::Vector2f(pixel_origin.x, pixel_origin.y));
    }

    template <class T>
    Transform::UnitVector BaseShape<T>::get_position() const
    {
        const sf::Vector2f position = static_cast<const T&>(*this).shape.getPosition();
        return Transform::UnitVector(position.x, position.y, Transform::Units::ScenePixels);
    }

    template <class T>
    float BaseShape<T>::get_rotation() const
    {
        return static_cast<const T&>(*this).shape.getRotation();
    }

    template <class T>
    Transform::UnitVector BaseShape<T>::get_scale() const
    {
        const sf::Vector2f scale = static_cast<const T&>(*this).shape.getScale();
        return Transform::UnitVector(scale.x, scale.y, Transform::Units::ScenePixels);
    }

    template <class T>
    Transform::UnitVector BaseShape<T>::get_origin() const
    {
        const sf::Vector2f origin = static_cast<const T&>(*this).shape.getOrigin();
        return Transform::UnitVector(origin.x, origin.y, Transform::Units::ScenePixels);
    }

    template <class T>
    void BaseShape<T>::move(const Transform::UnitVector& offset)
    {
        const Transform::UnitVector pixel_offset = offset.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.move(sf::Vector2f(pixel_offset.x, pixel_offset.y));
    }

    template <class T>
    void BaseShape<T>::rotate(float angle)
    {
        static_cast<T&>(*this).shape.rotate(angle);
    }

    template <class T>
    void BaseShape<T>::scale(const Transform::UnitVector& factor)
    {
        static_cast<T&>(*this).shape.scale(sf::Vector2f(factor.x, factor.y));
    }

    // Shape methods
    template <class T>
    void Shape<T>::set_texture(const Texture& texture)
    {
        static_cast<T&>(*this).shape.setTexture(&texture.operator const sf::Texture&(), true);
    }

    template <class T>
    void Shape<T>::set_texture_rect(const Transform::Rect& rect)
    {
        const Transform::UnitVector pixel_position
            = rect.getPosition().to<Transform::Units::ScenePixels>();
        const Transform::UnitVector pixel_size = rect.getSize().to<Transform::Units::ScenePixels>();
        const sf::IntRect pixel_rect(pixel_position.x, pixel_position.y, pixel_size.x, pixel_size.y);
        static_cast<T&>(*this).shape.setTextureRect(pixel_rect);
    }

    template <class T>
    void Shape<T>::set_position(Transform::UnitVector position)
    {
        const Transform::UnitVector pixel_position = position.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setPosition(sf::Vector2f(pixel_position.x, pixel_position.y));
    }

    template <class T>
    void Shape<T>::set_fill_color(const Color& color)
    {
        static_cast<T&>(*this).shape.setFillColor(color);
    }

    template <class T>
    void Shape<T>::set_outline_color(const Color& color)
    {
        static_cast<T&>(*this).shape.setOutlineColor(color);
    }

    template <class T>
    void Shape<T>::set_outline_thickness(float thickness)
    {
        static_cast<T&>(*this).shape.setOutlineThickness(thickness);
    }

    template <class T>
    Color Shape<T>::get_fill_color() const
    {
        return static_cast<const T&>(*this).shape.getFillColor();
    }

    template <class T>
    Color Shape<T>::get_outline_color() const
    {
        return static_cast<const T&>(*this).shape.getOutlineColor();
    }

    template <class T>
    float Shape<T>::get_outline_thickness() const
    {
        return static_cast<const T&>(*this).shape.getOutlineThickness();
    }

    template <class T>
    std::size_t Shape<T>::get_point_count() const
    {
        return static_cast<const T&>(*this).shape.getPointCount();
    }

    template <class T>
    Transform::UnitVector Shape<T>::get_point(std::size_t index) const
    {
        const sf::Vector2f point_position = static_cast<const T&>(*this).shape.getPoint(index);
        return Transform::UnitVector(
            point_position.x, point_position.y, Transform::Units::ScenePixels);
    }

    template <class T>
    Transform::Rect Shape<T>::get_local_bounds() const
    {
        const sf::FloatRect bounds = static_cast<const T&>(*this).shape.getLocalBounds();
        const auto position
            = Transform::UnitVector(bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size
            = Transform::UnitVector(bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T>
    Transform::Rect Shape<T>::get_global_bounds() const
    {
        const sf::FloatRect bounds = static_cast<const T&>(*this).shape.getGlobalBounds();
        const auto position
            = Transform::UnitVector(bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size
            = Transform::UnitVector(bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T>
    void Shape<T>::set_rotation(float angle)
    {
        static_cast<T&>(*this).shape.setRotation(angle);
    }

    template <class T>
    void Shape<T>::set_scale(const Transform::UnitVector& factors)
    {
        const auto pixel_scale = factors.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setScale(sf::Vector2f(pixel_scale.x, pixel_scale.y));
    }

    template <class T>
    void Shape<T>::set_origin(const Transform::UnitVector& origin)
    {
        const Transform::UnitVector pixel_origin = origin.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setOrigin(sf::Vector2f(pixel_origin.x, pixel_origin.y));
    }

    template <class T>
    Transform::UnitVector Shape<T>::get_position() const
    {
        const sf::Vector2f position = static_cast<const T&>(*this).shape.getPosition();
        return Transform::UnitVector(position.x, position.y, Transform::Units::ScenePixels);
    }

    template <class T>
    float Shape<T>::get_rotation() const
    {
        return static_cast<const T&>(*this).shape.getRotation();
    }

    template <class T>
    Transform::UnitVector Shape<T>::get_scale() const
    {
        const sf::Vector2f scale = static_cast<const T&>(*this).shape.getScale();
        return Transform::UnitVector(scale.x, scale.y, Transform::Units::ScenePixels);
    }

    template <class T>
    Transform::UnitVector Shape<T>::get_origin() const
    {
        const sf::Vector2f origin = static_cast<const T&>(*this).shape.getOrigin();
        return Transform::UnitVector(origin.x, origin.y, Transform::Units::ScenePixels);
    }

    template <class T>
    void Shape<T>::move(const Transform::UnitVector& offset)
    {
        const Transform::UnitVector pixel_offset = offset.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.move(sf::Vector2f(pixel_offset.x, pixel_offset.y));
    }

    template <class T>
    void Shape<T>::rotate(float angle)
    {
        static_cast<T&>(*this).shape.rotate(angle);
    }

    template <class T>
    void Shape<T>::scale(const Transform::UnitVector& factor)
    {
        static_cast<T&>(*this).shape.scale(sf::Vector2f(factor.x, factor.y));
    }

    /**
     * \brief Rectangle Shape
     * \copyparentitems
     */
    class Rectangle : public Shape<Rectangle>
    {
    public:
        sf::RectangleShape shape;

        Rectangle() = default;
        Rectangle(const sf::RectangleShape& shape);
        Rectangle(const Rectangle& rectangle);

        [[nodiscard]] Transform::UnitVector get_size() const;
        void set_size(Transform::UnitVector size);

        operator sf::RectangleShape&();
        operator const sf::RectangleShape&() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    /**
     * \brief Circle Shape
     * \copyparentitems
     */
    class Circle : public Shape<Circle>
    {
    public:
        sf::CircleShape shape;

        Circle() = default;
        Circle(const sf::CircleShape& shape);
        Circle(const Circle& circle);

        operator sf::CircleShape&();
        operator const sf::CircleShape&() const;

        void set_radius(float radius);
        float get_radius() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    /**
     * \brief Polygon Shape
     * \copyparentitems
     */
    class Polygon : public Shape<Polygon>
    {
    public:
        sf::ConvexShape shape;

        Polygon() = default;
        Polygon(const sf::ConvexShape& shape);
        Polygon(const Polygon& polygon);

        operator sf::ConvexShape&();
        operator const sf::ConvexShape&() const;

        void set_point_position(std::size_t index, const Transform::UnitVector& position);
        Transform::UnitVector get_point_position(std::size_t index) const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    /**
     * \brief Text Shape
     * \copyparentitems
     */
    class Text : public BaseShape<Text>
    {
    public:
        obe::graphics::RichText shape;

        Text() = default;
        Text(const RichText& shape);
        Text(const Text& text);

        operator RichText&();
        operator const RichText&() const;

        void clear();

        void append(const graphics::Text& text);

        const Font& get_font() const;
        void set_font(const Font& font);

        unsigned int get_character_size() const;
        void set_character_size(unsigned int size);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
