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
        const bool trigger_change = (m_angle != angle);
        m_angle = angle;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "angle");
        }
        return *this;
    }

    Trajectory& Trajectory::set_speed(const double speed)
    {
        const bool trigger_change = (m_speed != speed);
        m_speed = speed;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "speed");
        }
        return *this;
    }

    Trajectory& Trajectory::set_acceleration(const double acceleration)
    {
        const bool trigger_change = (m_acceleration != acceleration);
        m_acceleration = acceleration;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "acceleration");
        }
        return *this;
    }

    Trajectory& Trajectory::add_angle(const double angle)
    {
        const bool trigger_change = (angle != 0);
        m_angle += angle;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "angle");
        }
        return *this;
    }

    Trajectory& Trajectory::add_speed(const double speed)
    {
        const bool trigger_change = (speed != 0);
        m_speed += speed;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "speed");
        }
        return *this;
    }

    Trajectory& Trajectory::add_acceleration(const double acceleration)
    {
        const bool trigger_change = (acceleration != 0);
        m_acceleration = acceleration;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "acceleration");
        }
        return *this;
    }

    Trajectory& Trajectory::set_static(const bool static_)
    {
        const bool trigger_change = (m_static != static_);
        m_static = static_;
        if (m_on_change_callback && trigger_change)
        {
            m_on_change_callback(*this, "static");
        }
        return *this;
    }

    std::optional<std::string> Trajectory::get_tag() const
    {
        return m_tag;
    }

    void Trajectory::set_tag(const std::string& tag)
    {
        m_tag = tag;
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

    void Trajectory::on_change(const OnChangeCallback& callback)
    {
        m_on_change_callback = callback;
    }

    OnCollideCallback& Trajectory::get_on_collide_callback()
    {
        return m_on_collide_callback;
    }
} // namespace obe::collision
