#include "Camera.hpp"

namespace obe
{
	namespace World
	{
		Camera::Camera()
		{
			Coord::UnitVector::Init(m_camera);
		}

		void Camera::apply() const
		{
			m_camera->x = m_position.x;
			m_camera->y = m_position.y;
			m_camera->w = m_size.x;
			m_camera->h = m_size.y;
		}

		void Camera::setPosition(const Coord::UnitVector& position)
		{
			this->setPosition(position.x, position.y);
		}

		void Camera::setPosition(const double& x, const double& y)
		{
			m_position.set(x, y);
			this->apply();
		}

		void Camera::move(Coord::UnitVector position)
		{
			m_position += position;
			this->apply();
		}

		void Camera::move(const double& x, const double& y)
		{
			m_position.add(x, y);
			this->apply();
		}

		void Camera::setX(const double& x)
		{
			m_position.x = x;
			this->apply();
		}

		void Camera::setY(const double& y)
		{
			m_position.y = y;
			this->apply();
		}

		void Camera::setSize(const double& pSize)
		{
			m_size.set(pSize * 2 * (Coord::UnitVector::Screen.w / Coord::UnitVector::Screen.h), pSize * 2);
			this->apply();
		}

		void Camera::setAngle(const double& angle)
		{
			m_angle = angle;
		}

		void Camera::rotate(const double& angle)
		{
			m_angle += angle;
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

		Coord::UnitVector Camera::getPosition()
		{
			return m_position;
		}
	}
}
