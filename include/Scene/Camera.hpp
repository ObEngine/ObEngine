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
         * \brief The Camera that views the Scene
         * @Bind
         * 
         * Example :
         * 
         * \code
         * Camera& camera = scene.getCamera();
         * camera.setPosition(0, 0); //Set TopLeft Corner of the Camera at Position (0, 0)::WorldUnits
         * Transform::UnitVector newPosition(200, 1000, Transform::WorldPixels);
         * camera.setPosition(newPosition, Camera::Center); // Set Center of the Camera at Position(200, 100)::WorldPixels
         * camera.move(newPosition); // Move BottomRight Corner of the Camera to (400, 2000)::WorldPixels
         * \endcode
         */
        class Camera : Transform::Rect
        {
        private:
            sf::View m_view;

            Transform::ViewStruct* m_camera;

            double m_angle = 0;

            void apply() const;
        public:
            Camera();

            /**
             * \brief Sets the Position of the Camera
             * \param position New Position of the Camera
             * \param ref Referencial used to position the Camera
             */
            void setPosition(const Transform::UnitVector& position, Transform::Referencial ref = Transform::Referencial::TopLeft);
            /**
             * \brief Moves the Camera
             * \param position Position to add to the Camera
             */
            void move(const Transform::UnitVector& position);
            /**
             * \brief Gets the Position of the Camera
             * \param ref Referencial used to get the Position of the Camera
             * \return The Position of the Camera
             */
            Transform::UnitVector getPosition(Transform::Referencial ref = Transform::Referencial::TopLeft) const;

            /**
             * \brief Sets the size of the Camera
             * \param pSize Size of the Camera (1 = Normal Size meaning Screen Height = 2 WorldUnits)
             * \param ref Referencial used to resize the Camera
             */
            void setSize(double pSize, Transform::Referencial ref = Transform::Referencial::TopLeft);
            /**
             * \brief Scales the Camera
             * \param pSize Factor used to multiply the current size
             * \param ref Referencial used to resize the Camera
             */
            void scale(double pSize, Transform::Referencial ref = Transform::Referencial::TopLeft);
            /**
             * \brief Gets an UnitVector containing the size of the Camera (Width and Height)
             * \return An UnitVector containing the size of the Camera (Width and Height)
             */
            Transform::UnitVector getSize() const;

            /*void setAngle(double angle);
            void rotate(double angle);*/
        };
    }
}
