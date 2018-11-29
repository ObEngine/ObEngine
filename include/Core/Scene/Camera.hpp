#pragma once

#include <SFML/Graphics/View.hpp>

#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Scene
{
    /**
    * \brief The Camera that views the Scene
    * @Bind
    *
    * Example :
    *
    * \code
    * Camera& camera = scene.getCamera();
    * camera.setPosition(0, 0); //Set TopLeft Corner of the Camera at Position (0, 0)::SceneUnits
    * Transform::UnitVector newPosition(200, 1000, Transform::ScenePixels);
    * camera.setPosition(newPosition, Camera::Center); // Set Center of the Camera at Position(200, 100)::ScenePixels
    * camera.move(newPosition); // Move BottomRight Corner of the Camera to (400, 2000)::ScenePixels
    * \endcode
    */
    class Camera : public Transform::Rect
    {
    private:
        double m_angle = 0;
        Transform::ViewStruct* m_camera{};
        sf::View m_view;

        void apply() const;
    public:
        Camera();
        /**
        * \brief Gets the Position of the Camera
        * \param ref Referential used to get the Position of the Camera
        * \return The Position of the Camera
        */
        Transform::UnitVector getPosition(Transform::Referential ref = Transform::Referential::TopLeft) const override;
        /**
        * \brief Gets an UnitVector containing the size of the Camera (Width and Height)
        * \return An UnitVector containing the size of the Camera (Width and Height)
        */
        Transform::UnitVector getSize() const override;
        /**
        * \brief Moves the Camera
        * \param position Position to add to the Camera
        */
        void move(const Transform::UnitVector& position) override;
        //void rotate(double angle);
        /**
        * \brief Scales the Camera
        * \param pScale Factor used to multiply the current size
        * \param ref Referential used to resize the Camera
        */
        void scale(double pScale, Transform::Referential ref = Transform::Referential::Center);
        //void setAngle(double angle);
        /**
        * \brief Sets the Position of the Camera
        * \param position New Position of the Camera
        * \param ref Referential used to position the Camera
        */
        void setPosition(const Transform::UnitVector& position, Transform::Referential ref = Transform::Referential::TopLeft) override;
        /**
        * \brief Sets the size of the Camera
        * \param pSize Size of the Camera (1 = Normal Size meaning Screen Height = 2 SceneUnits)
        * \param ref Referential used to resize the Camera
        */
        void setSize(double pSize, Transform::Referential ref = Transform::Referential::Center);
    };
}