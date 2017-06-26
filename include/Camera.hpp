#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinates.hpp"
#include "Rect.hpp"

namespace obe
{
    namespace World
    {
	    /**
         * \brief The Camera that views the Scene (World)
         * 
         * Example :
         * 
         * \code
         * Camera& camera = World.getCamera();
         * camera.setPosition(0, 0); //Set TopLeft Corner of the Camera at Position (0, 0)::WorldUnits
         * Coord::UnitVector newPosition(200, 1000, Coord::WorldPixels);
         * camera.setPosition(newPosition, Camera::Center); // Set Center of the Camera at Position(200, 100)::WorldPixels
         * camera.move(newPosition); // Move BottomRight Corner of the Camera to (400, 2000)::WorldPixels
         * \endcode
         */
        class Camera : Coord::Rect
        {
        private:
            bool m_locked = false;
            sf::View m_view;

            Coord::ViewStruct* m_camera;

            double m_angle = 0;

            void apply() const;
        public:
            Camera();

            void lock();
            void unlock();

			void setPosition(const Coord::UnitVector& position, Referencial ref = TopLeft);
			void setPosition(double x, double y, Referencial ref = TopLeft);
			void move(const Coord::UnitVector& position);
			void move(double x, double y);
			void setX(double x, Referencial ref = TopLeft);
			void setY(double y, Referencial ref = TopLeft);
			double getX(Referencial ref = TopLeft) const;
			double getY(Referencial ref = TopLeft) const;
			Coord::UnitVector getPosition(Referencial ref = TopLeft) const;

			void setSize(double pSize);
			void scale(double pSize);
			double getWidth() const;
			double getHeight() const;
			Coord::UnitVector getSize() const;

            void setAngle(double angle);
            void rotate(double angle);
        };
    }
}
