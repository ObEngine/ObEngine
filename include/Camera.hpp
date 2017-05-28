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
			bool m_locked = false;
			sf::View m_view;

			Coord::ViewStruct* m_camera;

			Coord::UnitVector m_position;
			Coord::UnitVector m_size;

			double m_angle;

			void apply() const;
		public:
			Camera();

			void lock();
			void unlock();

			void setPosition(const Coord::UnitVector& position);
			void setPosition(double x, double y);
			void move(const Coord::UnitVector& position);
			void move(double x, double y);
			void setX(double x);
			void setY(double y);
			void setSize(double pSize);
			void scale(double pScale);
			void setAngle(double angle);
			void rotate(double angle);

			Coord::UnitVector getPosition() const;
			Coord::UnitVector getSize() const;

			double getX() const;
			double getY() const;
			double getWidth() const;
			double getHeight() const;
		};
	}
}
