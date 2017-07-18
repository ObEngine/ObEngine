#pragma once

#include <SFML/Graphics/View.hpp>

#include <Transform/Rect.hpp>
#include <Transform/Referencial.hpp>
#include <Transform/UnitVector.hpp>

namespace obe
{
    namespace Scene
    {
	    /**
         * \brief The Camera that views the Scene (World)
         * @Bind
         * 
         * Example :
         * 
         * \code
         * Camera& camera = World.getCamera();
         * camera.setPosition(0, 0); //Set TopLeft Corner of the Camera at Position (0, 0)::WorldUnits
         * Transform::UnitVector newPosition(200, 1000, Transform::WorldPixels);
         * camera.setPosition(newPosition, Camera::Center); // Set Center of the Camera at Position(200, 100)::WorldPixels
         * camera.move(newPosition); // Move BottomRight Corner of the Camera to (400, 2000)::WorldPixels
         * \endcode
         */
        class Camera : Transform::Rect
        {
        private:
            bool m_locked = false;
            sf::View m_view;

            Transform::ViewStruct* m_camera;

            double m_angle = 0;

            void apply() const;
        public:
            Camera();

            void lock();
            void unlock();

			void setPosition(const Transform::UnitVector& position, Transform::Referencial ref = Transform::Referencial::TopLeft);
			void setPosition(double x, double y, Transform::Referencial ref = Transform::Referencial::TopLeft);
			void move(const Transform::UnitVector& position);
			void move(double x, double y);
			void setX(double x, Transform::Referencial ref = Transform::Referencial::TopLeft);
			void setY(double y, Transform::Referencial ref = Transform::Referencial::TopLeft);
			double getX(Transform::Referencial ref = Transform::Referencial::TopLeft) const;
			double getY(Transform::Referencial ref = Transform::Referencial::TopLeft) const;
			Transform::UnitVector getPosition(Transform::Referencial ref = Transform::Referencial::TopLeft) const;

			void setSize(double pSize);
			void scale(double pSize);
			double getWidth() const;
			double getHeight() const;
			Transform::UnitVector getSize() const;

            void setAngle(double angle);
            void rotate(double angle);
        };
    }
}
