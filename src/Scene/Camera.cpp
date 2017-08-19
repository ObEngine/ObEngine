#include <Scene/Camera.hpp>
#include <iostream>

namespace obe
{
    namespace Scene
    {
        Camera::Camera()
        {
            Transform::UnitVector::Init(m_camera);
        }

        void Camera::lock()
        {
            m_locked = true;
        }

        void Camera::unlock()
        {
            m_locked = false;
        }

        void Camera::apply() const
        {
            if (!m_locked)
            {
                m_camera->x = m_position.x;
                m_camera->y = m_position.y;
                m_camera->w = m_size.x;
                m_camera->h = m_size.y;
                //Transform::UnitVector pixelPos = m_position.to<Transform::Units::WorldPixels>();
                Transform::UnitVector pixelSize = m_size.to<Transform::Units::WorldPixels>();
                //std::cout << "Set Camera Size : " << pixelSize << std::endl;
                //m_view.setSize(pixelSize.x, pixelSize.y);
                //m_view.setCenter(pixelPos.x + pixelSize.x / 2, pixelPos.y + pixelSize.y / 2);
            }
        }

        void Camera::setPosition(const Transform::UnitVector& position, Transform::Referencial ref)
        {
            if (!m_locked)
            {
                Rect::setPosition(position, ref);
                this->apply();
            }
        }

        void Camera::move(const Transform::UnitVector& position)
        {
            if (!m_locked)
            {
                Rect::move(position);
                this->apply();
            }
        }

        void Camera::setSize(double pSize, Transform::Referencial ref)
        {
            if (!m_locked)
            {
                Rect::setSize(pSize * 2 * (Transform::UnitVector::Screen.w / Transform::UnitVector::Screen.h), pSize * 2, ref);
                this->apply();
            }
        }

        void Camera::scale(double pScale, Transform::Referencial ref)
        {
            if (!m_locked)
            {
                this->setSize((m_size.y / 2) * pScale, ref);
                this->apply();
            }
        }

        /*void Camera::setAngle(double angle)
        {
            if (!m_locked) m_angle = angle;
        }

        void Camera::rotate(double angle)
        {
            if (!m_locked) m_angle += angle;
        }*/

        Transform::UnitVector Camera::getPosition(Transform::Referencial ref) const
        {
            return Rect::getPosition(ref);
        }

        Transform::UnitVector Camera::getSize() const
        {
            return m_size;
        }
    }
}
