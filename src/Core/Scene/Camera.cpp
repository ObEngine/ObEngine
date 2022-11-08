#include <Scene/Camera.hpp>

namespace obe::scene
{
    Camera::Camera()
    {
        transform::UnitVector::init(m_camera);
    }

    void Camera::apply() const
    {
        m_camera->x = m_position.x;
        m_camera->y = m_position.y;
        m_camera->w = m_size.x;
        m_camera->h = m_size.y;
    }

    void Camera::set_position(
        const transform::UnitVector& position, const transform::Referential& ref)
    {
        AABB::set_position(position, ref);
        this->apply();
    }

    void Camera::move(const transform::UnitVector& position)
    {
        AABB::move(position);
        this->apply();
    }

    void Camera::set_size(const double size, const transform::Referential& ref)
    {
        AABB::set_size(
            transform::UnitVector(
                size * 2 * (transform::UnitVector::Screen.w / transform::UnitVector::Screen.h),
                size * 2, m_size.unit),
            ref);
        this->apply();
    }

    void Camera::scale(const double scale_, const transform::Referential& ref)
    {
        this->set_size((m_size.y / 2) * scale_, ref);
        this->apply();
    }
} // namespace obe::scene
