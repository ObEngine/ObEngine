#include "Camera.hpp"

namespace obe
{
	namespace World
	{
		double Camera::transformHorizontal(const double& x, Units unit)
		{
			if (unit == Units::Pixels) {
				return (x * Functions::Coord::width) / worldWidth;
			}
			else if (unit == Units::WorldPercentage) {
				return (worldWidth * x) / 100.0;
			}
			else if (unit == Units::WorldUnits) {
				return x;
			}
		}

		double Camera::transformVertical(const double& y, Units unit)
		{
			if (unit == Units::Pixels) {
				return (y * Functions::Coord::height) / worldHeight;
			}
			else if (unit == Units::WorldPercentage) {
				return (worldHeight * y) / 100.0;
			}
			else if (unit == Units::WorldUnits) {
				return y;
			}
		}

		Camera::Camera()
		{
		}


		void Camera::setWorldSize(const double& worldWidth, const double& worldHeight)
		{
			this->worldWidth = worldWidth;
			this->worldHeight = worldHeight;
		}

		void Camera::setPosition(const double& x, const double& y, Units unit)
		{
			this->x = transformHorizontal(x, unit);
			this->y = transformVertical(y, unit);
		}

		void Camera::move(const double& x, const double& y, Units unit)
		{
			this->x += transformHorizontal(x, unit);
			this->y += transformVertical(y, unit);
		}

		void Camera::setX(const double& x, Units unit)
		{
			this->x = transformHorizontal(x, unit);
		}

		void Camera::setY(const double& y, Units unit)
		{
			this->y = transformVertical(y, unit);
		}

		void Camera::setSize(const double& width, const double& height, Units unit)
		{
			this->width = width;
			this->height = height;
		}

		void Camera::scale(const double& width, const double& height, Units unit)
		{
			this->width += width;
			this->height += height;
		}

		void Camera::setWidth(const double& width, Units unit)
		{
			this->width = transformHorizontal(width, unit);
		}

		void Camera::setHeight(const double& height, Units unit)
		{
			this->height = transformVertical(height, unit);
		}

		void Camera::setAngle(const double& angle)
		{
			this->angle = angle;
		}

		void Camera::rotate(const double& angle)
		{
			this->angle += angle;
		}
		std::pair<double, double> Camera::getPosition(Units unit)
		{
			return std::pair<double, double>(transformHorizontal(x, unit), transformVertical(y, unit));
		}
		double Camera::getX(Units unit)
		{
			return transformHorizontal(x, unit);
		}
		double Camera::getY(Units unit)
		{
			return transformVertical(y, unit);
		}
		double Camera::getWidth(Units unit)
		{
			return transformHorizontal(width, unit);
		}
		double Camera::getHeight(Units unit)
		{
			return transformVertical(height, unit);
		}
		double Camera::getWidthRatio()
		{
			return (width / worldWidth);
		}
		double Camera::getHeightRatio()
		{
			return (height / worldHeight);
		}
	}
}