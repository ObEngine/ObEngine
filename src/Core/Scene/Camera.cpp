#include <Scene/Camera.hpp>

namespace obe::Scene
{
    Camera::Camera()
    {
        Transform::UnitVector::Init(m_camera);
    }

    void Camera::apply() const
    {
        m_camera->x = m_position.x;
        m_camera->y = m_position.y;
        m_camera->w = m_size.x;
        m_camera->h = m_size.y;
    }

    void Camera::setPosition(const Transform::UnitVector& position, const Transform::Referential ref)
    {
        Rect::setPosition(position, ref);
        this->apply();
    }

    void Camera::move(const Transform::UnitVector& position)
    {
        Rect::move(position);
        this->apply();
    }

    void Camera::setSize(const double pSize, const Transform::Referential ref)
    {
        Rect::setSize(
            Transform::UnitVector(
                pSize * 2 * (Transform::UnitVector::Screen.w / Transform::UnitVector::Screen.h), 
                pSize * 2, m_size.unit
            )
        , ref);
        this->apply();
    }

    void Camera::scale(const double pScale, const Transform::Referential ref)
    {
        this->setSize((m_size.y / 2) * pScale, ref);
        this->apply();
    }

    /*void Camera::setAngle(double angle)
    {
        if (!m_locked) m_angle = angle;
    }

    void Camera::rotate(double angle)
    {
        if (!m_locked) m_angle += angle;
    }*/

    Transform::UnitVector Camera::getPosition(const Transform::Referential ref) const
    {
        return Rect::getPosition(ref);
    }

    Transform::UnitVector Camera::getSize() const
    {
        return m_size;
    }
}