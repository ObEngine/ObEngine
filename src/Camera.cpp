#include "Camera.hpp"

namespace obe
{
    namespace World
    {
        Camera::Camera()
        {
            Coord::UnitVector::Init(m_camera);
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
            }
        }

        void Camera::setPosition(const Coord::UnitVector& position)
        {
            Coord::UnitVector pVec = position.to<Coord::WorldUnits>();
            if (!m_locked) this->setPosition(pVec.x, pVec.y);
        }

        void Camera::setPosition(double x, double y)
        {
            if (!m_locked) m_position.set(x, y);
            this->apply();
        }

        void Camera::move(const Coord::UnitVector& position)
        {
            if (!m_locked) m_position += position;
            this->apply();
        }

        void Camera::move(double x, double y)
        {
            if (!m_locked) m_position.add(x, y);
            this->apply();
        }

        void Camera::setX(double x)
        {
            if (!m_locked) m_position.x = x;
            this->apply();
        }

        void Camera::setY(double y)
        {
            if (!m_locked) m_position.y = y;
            this->apply();
        }

        void Camera::setSize(double pSize)
        {
            if (!m_locked) m_size.set(pSize * 2 * (Coord::UnitVector::Screen.w / Coord::UnitVector::Screen.h), pSize * 2);
            this->apply();
        }

        void Camera::scale(double pScale)
        {
            if (!m_locked) this->setSize((m_size.y / 2) + pScale);
        }

        void Camera::setAngle(double angle)
        {
            if (!m_locked) m_angle = angle;
        }

        void Camera::rotate(double angle)
        {
            if (!m_locked) m_angle += angle;
        }

        Coord::UnitVector Camera::getPosition() const
        {
            return m_position;
        }

        Coord::UnitVector Camera::getSize() const
        {
            return m_size;
        }

        double Camera::getX() const
        {
            return m_position.x;
        }

        double Camera::getY() const
        {
            return m_position.y;
        }

        double Camera::getWidth() const
        {
            return m_size.x;
        }

        double Camera::getHeight() const
        {
            return m_size.y;
        }
    }
}
