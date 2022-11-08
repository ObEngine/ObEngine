#pragma once

#include <SFML/Graphics/View.hpp>
#include <Transform/AABB.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::scene
{
    /**
     * \brief The Camera that views the Scene
     */
    class Camera : public transform::AABB
    {
    private:
        transform::ViewStruct* m_camera {};
        sf::View m_view;

        void apply() const;

    public:
        Camera();
        /**
         * \brief Moves the Camera
         * \param position Position to add to the Camera
         */
        void move(const transform::UnitVector& position);
        /**
         * \brief Scales the Camera
         * \param scale_ Factor used to multiply the current size
         * \param ref Referential used to resize the Camera
         */
        void scale(
            double scale_, const transform::Referential& ref = transform::Referential::Center);
        // void set_angle(double angle);
        /**
         * \brief Sets the Position of the Camera
         * \param position New Position of the Camera
         * \param ref Referential used to position the Camera
         */
        void set_position(const transform::UnitVector& position,
            const transform::Referential& ref = transform::Referential::TopLeft);
        /**
         * \brief Sets the size of the Camera
         * \param size Size of the Camera (1 = Normal Size meaning Screen
         *        Height = 2 SceneUnits)
         * \param ref Referential used to resize the Camera
         */
        void set_size(
            double size, const transform::Referential& ref = transform::Referential::Center);
    };
} // namespace obe::scene
