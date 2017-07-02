#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinates.hpp"
#include "Rect.hpp"
#include "Referencial.hpp"

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

			void setPosition(const Coord::UnitVector& position, Coord::Referencial ref = Coord::Referencial::TopLeft);
			void setPosition(double x, double y, Coord::Referencial ref = Coord::Referencial::TopLeft);
			void move(const Coord::UnitVector& position);
			void move(double x, double y);
			void setX(double x, Coord::Referencial ref = Coord::Referencial::TopLeft);
			void setY(double y, Coord::Referencial ref = Coord::Referencial::TopLeft);
			double getX(Coord::Referencial ref = Coord::Referencial::TopLeft) const;
			double getY(Coord::Referencial ref = Coord::Referencial::TopLeft) const;
			Coord::UnitVector getPosition(Coord::Referencial ref = Coord::Referencial::TopLeft) const;

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
