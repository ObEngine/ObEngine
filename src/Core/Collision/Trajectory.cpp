#include <Collision/Trajectory.hpp>

namespace obe::collision
{
    Trajectory::Trajectory(const transform::Units unit)
        : Togglable(true)
        , m_unit(unit)
    {
    }

    Trajectory& Trajectory::set_angle(const double angle)
    {
        m_angle = angle;
        return *this;
    }

    Trajectory& Trajectory::set_speed(const double speed)
    {
        m_speed = speed;
        return *this;
    }

    Trajectory& Trajectory::set_acceleration(const double acceleration)
    {
        m_acceleration = acceleration;
        return *this;
    }

    Trajectory& Trajectory::add_angle(const double angle)
    {
        m_angle += angle;
        return *this;
    }

    Trajectory& Trajectory::add_speed(const double speed)
    {
        m_speed += speed;
        return *this;
    }

    Trajectory& Trajectory::add_acceleration(const double acceleration)
    {
        m_acceleration = acceleration;
        return *this;
    }

    Trajectory& Trajectory::set_static(const bool static_)
    {
        m_static = static_;
        return *this;
    }

    double Trajectory::get_angle() const
    {
        return m_angle;
    }

    double Trajectory::get_speed() const
    {
        return m_speed;
    }

    double Trajectory::get_acceleration() const
    {
        return m_acceleration;
    }

    bool Trajectory::is_static() const
    {
        return m_static;
    }

    transform::Units Trajectory::get_unit() const
    {
        return m_unit;
    }

    void Trajectory::add_check(const TrajectoryCheckFunction& check)
    {
        m_checks.push_back(check);
    }

    std::vector<TrajectoryCheckFunction>& Trajectory::get_checks()
    {
        return m_checks;
    }

    void Trajectory::on_collide(const OnCollideCallback& callback)
    {
        m_on_collide_callback = callback;
    }

    OnCollideCallback& Trajectory::get_on_collide_callback()
    {
        return m_on_collide_callback;
    }
} // namespace obe::collision
