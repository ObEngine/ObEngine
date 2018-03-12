#include <ComplexTransformable.hpp>

namespace sfe
{
    ComplexTransformable::ComplexTransformable() :
        m_tra_origin(0, 0),
        m_rot_origin(0, 0),
        m_sca_origin(0, 0),
        m_position(0, 0),
        m_rotation(0),
        m_scale(1, 1),
        m_transform(),
        m_transformNeedUpdate(true),
        m_inverseTransform(),
        m_inverseTransformNeedUpdate(true)
    {
    }

    ComplexTransformable::~ComplexTransformable()
    {
    }

    void ComplexTransformable::setPosition(float x, float y)
    {
        m_position.x = x;
        m_position.y = y;
        m_transformNeedUpdate = true;
        m_inverseTransformNeedUpdate = true;
    }

    void ComplexTransformable::setPosition(const sf::Vector2f& position)
    {
        setPosition(position.x, position.y);
    }

    void ComplexTransformable::setRotation(float angle)
    {
        m_rotation = static_cast<float>(fmod(angle, 360));
        if (m_rotation < 0)
            m_rotation += 360.f;

        m_transformNeedUpdate = true;
        m_inverseTransformNeedUpdate = true;
    }

    void ComplexTransformable::setScale(float factorX, float factorY)
    {
        m_scale.x = factorX;
        m_scale.y = factorY;
        m_transformNeedUpdate = true;
        m_inverseTransformNeedUpdate = true;
    }

    void ComplexTransformable::setScale(const sf::Vector2f& factors)
    {
        setScale(factors.x, factors.y);
    }

    void ComplexTransformable::setTranslationOrigin(float x, float y)
    {
        m_tra_origin.x = x;
        m_tra_origin.y = y;
        m_transformNeedUpdate = true;
        m_inverseTransformNeedUpdate = true;
    }

    void ComplexTransformable::setTranslationOrigin(const sf::Vector2f& origin)
    {
        setTranslationOrigin(origin.x, origin.y);
    }

    void ComplexTransformable::setRotationOrigin(float x, float y)
    {
        m_rot_origin.x = x;
        m_rot_origin.y = y;
        m_transformNeedUpdate = true;
        m_inverseTransformNeedUpdate = true;
    }

    void ComplexTransformable::setRotationOrigin(const sf::Vector2f& origin)
    {
        setRotationOrigin(origin.x, origin.y);
    }

    void ComplexTransformable::setScalingOrigin(float x, float y)
    {
        m_sca_origin.x = x;
        m_sca_origin.y = y;
        m_transformNeedUpdate = true;
        m_inverseTransformNeedUpdate = true;
    }

    void ComplexTransformable::setScalingOrigin(const sf::Vector2f& origin)
    {
        setScalingOrigin(origin.x, origin.y);
    }

    const sf::Vector2f& ComplexTransformable::getPosition() const
    {
        return m_position;
    }

    float ComplexTransformable::getRotation() const
    {
        return m_rotation;
    }

    const sf::Vector2f& ComplexTransformable::getScale() const
    {
        return m_scale;
    }

    const sf::Vector2f& ComplexTransformable::getTranslationOrigin() const
    {
        return m_tra_origin;
    }

    const sf::Vector2f& ComplexTransformable::getRotationOrigin() const
    {
        return m_rot_origin;
    }

    const sf::Vector2f& ComplexTransformable::getScalingOrigin() const
    {
        return m_sca_origin;
    }

    void ComplexTransformable::move(float offsetX, float offsetY)
    {
        setPosition(m_position.x + offsetX, m_position.y + offsetY);
    }

    void ComplexTransformable::move(const sf::Vector2f& offset)
    {
        setPosition(m_position.x + offset.x, m_position.y + offset.y);
    }

    void ComplexTransformable::rotate(float angle)
    {
        setRotation(m_rotation + angle);
    }

    void ComplexTransformable::scale(float factorX, float factorY)
    {
        setScale(m_scale.x * factorX, m_scale.y * factorY);
    }

    void ComplexTransformable::scale(const sf::Vector2f& factor)
    {
        setScale(m_scale.x * factor.x, m_scale.y * factor.y);
    }

    const sf::Transform& ComplexTransformable::getTransform() const
    {
        // Recompute the combined transform if needed
        if (m_transformNeedUpdate)
        {
            /*m_transform = sf::Transform::Identity;
            m_transform.scale(m_scale);
            m_transform.translate(m_position.x - m_tra_origin.x, m_position.y - m_tra_origin.y);
            m_transform.rotate(m_rotation, m_rot_origin);
            m_transform.scale(m_scale);*/

            m_transform = sf::Transform::Identity;
            m_transform.translate(m_position.x - m_tra_origin.x, m_position.y - m_tra_origin.y);
            m_transform.scale(m_scale.x, m_scale.y, m_sca_origin.x, m_sca_origin.y);
            m_transform.rotate(m_rotation, m_rot_origin);

            m_transformNeedUpdate = false;
        }

        return m_transform;
    }

    const sf::Transform& ComplexTransformable::getInverseTransform() const
    {
        // Recompute the inverse transform if needed
        if (m_inverseTransformNeedUpdate)
        {
            m_inverseTransform = getTransform().getInverse();
            m_inverseTransformNeedUpdate = false;
        }

        return m_inverseTransform;
    }
}
