#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Texture.hpp>
#include <Transform/Rect.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Graphics::Shapes
{
    template <class T> class BaseShape : public sf::Drawable
    {
    public:
        void setPosition(Transform::UnitVector position);
        [[nodiscard]] Transform::Rect getLocalBounds() const;
        [[nodiscard]] Transform::Rect getGlobalBounds() const;
        void setRotation(float angle);
        void setScale(const Transform::UnitVector& factors);
        void setOrigin(const Transform::UnitVector& origin);
        [[nodiscard]] Transform::UnitVector getPosition() const;
        [[nodiscard]] float getRotation() const;
        [[nodiscard]] Transform::UnitVector getScale() const;
        [[nodiscard]] Transform::UnitVector getOrigin() const;
        void move(const Transform::UnitVector& offset);
        void rotate(float angle);
        void scale(const Transform::UnitVector& factor);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    };

    template <class T> class Shape : public sf::Drawable
    {
    public:
        void setTexture(const Texture& texture);
        void setTextureRect(const Transform::Rect& rect);
        void setPosition(Transform::UnitVector position);
        void setFillColor(const Color& color);
        void setOutlineColor(const Color& color);
        void setOutlineThickness(float thickness);
        [[nodiscard]] Color getFillColor() const;
        [[nodiscard]] Color getOutlineColor() const;
        [[nodiscard]] float getOutlineThickness() const;
        [[nodiscard]] std::size_t getPointCount() const;
        [[nodiscard]] Transform::UnitVector getPoint(std::size_t index) const;
        [[nodiscard]] Transform::Rect getLocalBounds() const;
        [[nodiscard]] Transform::Rect getGlobalBounds() const;
        void setRotation(float angle);
        void setScale(const Transform::UnitVector& factors);
        void setOrigin(const Transform::UnitVector& origin);
        [[nodiscard]] Transform::UnitVector getPosition() const;
        [[nodiscard]] float getRotation() const;
        [[nodiscard]] Transform::UnitVector getScale() const;
        [[nodiscard]] Transform::UnitVector getOrigin() const;
        void move(const Transform::UnitVector& offset);
        void rotate(float angle);
        void scale(const Transform::UnitVector& factor);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    };

    // BaseShape methods
    template <class T> void BaseShape<T>::setPosition(Transform::UnitVector position)
    {
        const Transform::UnitVector pixelPosition
            = position.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setPosition(
            sf::Vector2f(pixelPosition.x, pixelPosition.y));
    }

    template <class T> Transform::Rect BaseShape<T>::getLocalBounds() const
    {
        const sf::FloatRect bounds = static_cast<const T&>(*this).shape.getLocalBounds();
        const auto position = Transform::UnitVector(
            bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size = Transform::UnitVector(
            bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T> Transform::Rect BaseShape<T>::getGlobalBounds() const
    {
        sf::FloatRect bounds = static_cast<const T&>(*this).shape.getGlobalBounds();
        const auto position = Transform::UnitVector(
            bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size = Transform::UnitVector(
            bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T> void BaseShape<T>::setRotation(float angle)
    {
        static_cast<T&>(*this).shape.setRotation(angle);
    }

    template <class T> void BaseShape<T>::setScale(const Transform::UnitVector& factors)
    {
        const auto pixelScale = factors.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setScale(sf::Vector2f(pixelScale.x, pixelScale.y));
    }

    template <class T> void BaseShape<T>::setOrigin(const Transform::UnitVector& origin)
    {
        const Transform::UnitVector pixelOrigin
            = origin.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setOrigin(
            sf::Vector2f(pixelOrigin.x, pixelOrigin.y));
    }

    template <class T> Transform::UnitVector BaseShape<T>::getPosition() const
    {
        const sf::Vector2f position = static_cast<const T&>(*this).shape.getPosition();
        return Transform::UnitVector(
            position.x, position.y, Transform::Units::ScenePixels);
    }

    template <class T> float BaseShape<T>::getRotation() const
    {
        return static_cast<const T&>(*this).shape.getRotation();
    }

    template <class T> Transform::UnitVector BaseShape<T>::getScale() const
    {
        const sf::Vector2f scale = static_cast<const T&>(*this).shape.getScale();
        return Transform::UnitVector(scale.x, scale.y, Transform::Units::ScenePixels);
    }

    template <class T> Transform::UnitVector BaseShape<T>::getOrigin() const
    {
        const sf::Vector2f origin = static_cast<const T&>(*this).shape.getOrigin();
        return Transform::UnitVector(origin.x, origin.y, Transform::Units::ScenePixels);
    }

    template <class T> void BaseShape<T>::move(const Transform::UnitVector& offset)
    {
        const Transform::UnitVector pixelOffset
            = offset.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.move(sf::Vector2f(pixelOffset.x, pixelOffset.y));
    }

    template <class T> void BaseShape<T>::rotate(float angle)
    {
        static_cast<T&>(*this).shape.rotate(angle);
    }

    template <class T> void BaseShape<T>::scale(const Transform::UnitVector& factor)
    {
        static_cast<T&>(*this).shape.scale(sf::Vector2f(factor.x, factor.y));
    }

    // Shape methods
    template <class T> void Shape<T>::setTexture(const Texture& texture)
    {
        static_cast<T&>(*this).shape.setTexture(
            &texture.operator const sf::Texture&(), true);
    }

    template <class T> void Shape<T>::setTextureRect(const Transform::Rect& rect)
    {
        const Transform::UnitVector pixelPosition
            = rect.getPosition().to<Transform::Units::ScenePixels>();
        const Transform::UnitVector pixelSize
            = rect.getSize().to<Transform::Units::ScenePixels>();
        const sf::IntRect pixelRect(
            pixelPosition.x, pixelPosition.y, pixelSize.x, pixelSize.y);
        static_cast<T&>(*this).shape.setTextureRect(pixelRect);
    }

    template <class T> void Shape<T>::setPosition(Transform::UnitVector position)
    {
        const Transform::UnitVector pixelPosition
            = position.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setPosition(
            sf::Vector2f(pixelPosition.x, pixelPosition.y));
    }

    template <class T> void Shape<T>::setFillColor(const Color& color)
    {
        static_cast<T&>(*this).shape.setFillColor(color);
    }

    template <class T> void Shape<T>::setOutlineColor(const Color& color)
    {
        static_cast<T&>(*this).shape.setOutlineColor(color);
    }

    template <class T> void Shape<T>::setOutlineThickness(float thickness)
    {
        static_cast<T&>(*this).shape.setOutlineThickness(thickness);
    }

    template <class T> Color Shape<T>::getFillColor() const
    {
        return static_cast<const T&>(*this).shape.getFillColor();
    }

    template <class T> Color Shape<T>::getOutlineColor() const
    {
        return static_cast<const T&>(*this).shape.getOutlineColor();
    }

    template <class T> float Shape<T>::getOutlineThickness() const
    {
        return static_cast<const T&>(*this).shape.getOutlineThickness();
    }

    template <class T> std::size_t Shape<T>::getPointCount() const
    {
        return static_cast<const T&>(*this).shape.getPointCount();
    }

    template <class T> Transform::UnitVector Shape<T>::getPoint(std::size_t index) const
    {
        const sf::Vector2f pointPosition
            = static_cast<const T&>(*this).shape.getPoint(index);
        return Transform::UnitVector(
            pointPosition.x, pointPosition.y, Transform::Units::ScenePixels);
    }

    template <class T> Transform::Rect Shape<T>::getLocalBounds() const
    {
        const sf::FloatRect bounds = static_cast<const T&>(*this).shape.getLocalBounds();
        const auto position = Transform::UnitVector(
            bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size = Transform::UnitVector(
            bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T> Transform::Rect Shape<T>::getGlobalBounds() const
    {
        sf::FloatRect bounds = static_cast<const T&>(*this).shape.getGlobalBounds();
        const auto position = Transform::UnitVector(
            bounds.left, bounds.top, Transform::Units::ScenePixels);
        const auto size = Transform::UnitVector(
            bounds.width, bounds.height, Transform::Units::ScenePixels);
        return Transform::Rect(position, size);
    }

    template <class T> void Shape<T>::setRotation(float angle)
    {
        static_cast<T&>(*this).shape.setRotation(angle);
    }

    template <class T> void Shape<T>::setScale(const Transform::UnitVector& factors)
    {
        const auto pixelScale = factors.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setScale(sf::Vector2f(pixelScale.x, pixelScale.y));
    }

    template <class T> void Shape<T>::setOrigin(const Transform::UnitVector& origin)
    {
        const Transform::UnitVector pixelOrigin
            = origin.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.setOrigin(
            sf::Vector2f(pixelOrigin.x, pixelOrigin.y));
    }

    template <class T> Transform::UnitVector Shape<T>::getPosition() const
    {
        const sf::Vector2f position = static_cast<const T&>(*this).shape.getPosition();
        return Transform::UnitVector(
            position.x, position.y, Transform::Units::ScenePixels);
    }

    template <class T> float Shape<T>::getRotation() const
    {
        return static_cast<const T&>(*this).shape.getRotation();
    }

    template <class T> Transform::UnitVector Shape<T>::getScale() const
    {
        const sf::Vector2f scale = static_cast<const T&>(*this).shape.getScale();
        return Transform::UnitVector(scale.x, scale.y, Transform::Units::ScenePixels);
    }

    template <class T> Transform::UnitVector Shape<T>::getOrigin() const
    {
        const sf::Vector2f origin = static_cast<const T&>(*this).shape.getOrigin();
        return Transform::UnitVector(origin.x, origin.y, Transform::Units::ScenePixels);
    }

    template <class T> void Shape<T>::move(const Transform::UnitVector& offset)
    {
        const Transform::UnitVector pixelOffset
            = offset.to<Transform::Units::ScenePixels>();
        static_cast<T&>(*this).shape.move(sf::Vector2f(pixelOffset.x, pixelOffset.y));
    }

    template <class T> void Shape<T>::rotate(float angle)
    {
        static_cast<T&>(*this).shape.rotate(angle);
    }

    template <class T> void Shape<T>::scale(const Transform::UnitVector& factor)
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

        Transform::UnitVector getSize() const;
        void setSize(Transform::UnitVector size);

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

        void setRadius(float radius);
        float getRadius() const;

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

        void setPointPosition(std::size_t index, const Transform::UnitVector& position);
        Transform::UnitVector getPointPosition(std::size_t index) const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    /**
     * \brief Text Shape
     * \copyparentitems
     */
    class Text : public BaseShape<Text>
    {
    public:
        obe::Graphics::RichText shape;

        Text() = default;
        Text(const RichText& shape);
        Text(const Text& text);

        operator RichText&();
        operator const RichText&() const;

        void clear();

        void append(const Graphics::Text& text);

        const Font& getFont() const;
        void setFont(const Font& font);

        unsigned int getCharacterSize() const;
        void setCharacterSize(unsigned int size);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
