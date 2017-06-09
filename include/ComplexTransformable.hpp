#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>


namespace sfe
{
    class ComplexTransformable
    {
    public:
        ComplexTransformable();
        virtual ~ComplexTransformable();
        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& position);
        void setRotation(float angle);
        void setScale(float factorX, float factorY);
        void setScale(const sf::Vector2f& factors);
        void setTranslationOrigin(float x, float y);
        void setTranslationOrigin(const sf::Vector2f& origin);
        void setRotationOrigin(float x, float y);
        void setRotationOrigin(const sf::Vector2f& origin);
        void setScalingOrigin(float x, float y);
        void setScalingOrigin(const sf::Vector2f& origin);
        const sf::Vector2f& getPosition() const;
        float getRotation() const;
        const sf::Vector2f& getScale() const;
        const sf::Vector2f& getTranslationOrigin() const;
        const sf::Vector2f& getRotationOrigin() const;
        const sf::Vector2f& getScalingOrigin() const;
        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f& offset);
        void rotate(float angle);
        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f& factor);
        const sf::Transform& getTransform() const;
        const sf::Transform& getInverseTransform() const;

    private:
        sf::Vector2f m_tra_origin; ///< Origin of translation/scaling of the object
        sf::Vector2f m_rot_origin; ///< Origin of rotation of the object
        sf::Vector2f m_sca_origin;
        sf::Vector2f m_position; ///< Position of the object in the 2D world
        float m_rotation; ///< Orientation of the object, in degrees
        sf::Vector2f m_scale; ///< Scale of the object
        mutable sf::Transform m_transform; ///< Combined transformation of the object
        mutable bool m_transformNeedUpdate; ///< Does the transform need to be recomputed?
        mutable sf::Transform m_inverseTransform; ///< Combined transformation of the object
        mutable bool m_inverseTransformNeedUpdate; ///< Does the transform need to be recomputed?
    };
}
