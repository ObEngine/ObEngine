#include <Scene/Camera.hpp>

namespace obe::scene
{
    Camera::Camera()
    {
    }

    void Camera::set_position(
        const transform::Vector2& position, const transform::Referential& ref)
    {
        AABB::set_position(position, ref);
    }

    void Camera::move(const transform::Vector2& position)
    {
        AABB::move(position);
    }

    void Camera::set_size(const double size, const transform::Referential& ref)
    {
        // TOCHECK
        AABB::set_size(transform::Vector2(size, size), ref);
    }

    void Camera::scale(const double scale_, const transform::Referential& ref)
    {
        // TOCHECK
        this->set_size((m_size.y / 2) * scale_, ref);
    }
} // namespace obe::scene
