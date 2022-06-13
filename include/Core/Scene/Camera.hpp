#pragma once

#include <SFML/Graphics/View.hpp>

#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::scene
{
    /**
     * \brief The Camera that views the Scene
     */
    class Camera : public Transform::Rect
    {
    private:
        Transform::ViewStruct* m_camera {};
        sf::View m_view;

        void apply() const;

    public:
        Camera();
        /**
         * \brief Gets the Position of the Camera
         * \param ref Referential used to get the Position of the Camera
         * \return The Position of the Camera
         */
        Transform::UnitVector get_position(
            const Transform::Referential& ref = Transform::Referential::TopLeft) const override;
        /**
         * \brief Gets an UnitVector containing the size of the Camera (Width
         *        and Height)
         * \return An UnitVector containing the size of the Camera (Width and Height)
         */
        Transform::UnitVector get_size() const override;
        /**
         * \brief Moves the Camera
         * \param position Position to add to the Camera
         */
        void move(const Transform::UnitVector& position) override;
        // void rotate(double angle);
        /**
         * \brief Scales the Camera
         * \param scale_ Factor used to multiply the current size
         * \param ref Referential used to resize the Camera
         */
        void scale(
            double scale_, const Transform::Referential& ref = Transform::Referential::Center);
        // void set_angle(double angle);
        /**
         * \brief Sets the Position of the Camera
         * \param position New Position of the Camera
         * \param ref Referential used to position the Camera
         */
        void set_position(const Transform::UnitVector& position,
            const Transform::Referential& ref = Transform::Referential::TopLeft) override;
        /**
         * \brief Sets the size of the Camera
         * \param size Size of the Camera (1 = Normal Size meaning Screen
         *        Height = 2 SceneUnits)
         * \param ref Referential used to resize the Camera
         */
        void set_size(
            double size, const Transform::Referential& ref = Transform::Referential::Center);
    };
} // namespace obe::scene
