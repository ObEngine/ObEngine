#include <Scene/Camera.hpp>

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

        void Camera::setPosition(double x, double y, Transform::Referencial ref)
        {
			if (!m_locked)
			{
				Rect::setPosition(x, y, ref);
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

        void Camera::move(double x, double y)
        {
			if (!m_locked)
			{
				Rect::setPosition(x, y);
				this->apply();
			}
        }

        void Camera::setX(double x, Transform::Referencial ref)
        {
			if (!m_locked)
			{
				Rect::setX(x, ref);
				this->apply();
			}
        }

        void Camera::setY(double y, Transform::Referencial ref)
        {
			if (!m_locked)
			{
				Rect::setY(y, ref);
				this->apply();
			}
        }

        void Camera::setSize(double pSize)
        {
			if (!m_locked)
			{
				Rect::setSize(pSize * 2 * (Transform::UnitVector::Screen.w / Transform::UnitVector::Screen.h), pSize * 2);
				this->apply();
			}
        }

        void Camera::scale(double pScale)
        {
			if (!m_locked)
			{
				this->setSize((m_size.y / 2) * pScale);
				this->apply();
			}
        }

        void Camera::setAngle(double angle)
        {
            if (!m_locked) m_angle = angle;
        }

        void Camera::rotate(double angle)
        {
            if (!m_locked) m_angle += angle;
        }

        Transform::UnitVector Camera::getPosition(Transform::Referencial ref) const
        {
            return Rect::getPosition(ref);
        }

        Transform::UnitVector Camera::getSize() const
        {
            return m_size;
        }

        double Camera::getX(Transform::Referencial ref) const
        {
            return Rect::getX(ref);
        }

        double Camera::getY(Transform::Referencial ref) const
        {
            return Rect::getY(ref);
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
