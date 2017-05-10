#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinates.hpp"

namespace obe
{
	namespace World
	{
		class Camera
		{
		private:
			sf::View m_view;

			Coord::ViewStruct* m_camera;

			Coord::UnitVector m_position;
			Coord::UnitVector m_size;

			double m_angle;

			void apply() const;
		public:
			Camera();

			void setPosition(const Coord::UnitVector& position);
			void setPosition(const double& x, const double& y);
			void move(Coord::UnitVector position);
			void move(const double& x, const double& y);
			void setX(const double& x);
			void setY(const double& y);
			void setSize(const double& pSize);
			void scale(const double& pScale);
			void setAngle(const double& angle);
			void rotate(const double& angle);

			Coord::UnitVector getPosition() const;
			Coord::UnitVector getSize() const;

			double getX() const;
			double getY() const;
			double getWidth() const;
			double getHeight() const;

			Coord::UnitVector getPosition();
		};
	}
}
