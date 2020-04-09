#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>

namespace obe::Collision
{
    Trajectory::Trajectory(const Transform::Units unit)
        : Togglable(true)
    {
        m_unit = unit;
    }

    Trajectory& Trajectory::setAngle(const double angle)
    {
        m_angle = angle;
        return *this;
    }

    Trajectory& Trajectory::setSpeed(const double speed)
    {
        m_speed = speed;
        return *this;
    }

    Trajectory& Trajectory::setAcceleration(const double acceleration)
    {
        m_acceleration = acceleration;
        return *this;
    }

    Trajectory& Trajectory::addAngle(const double angle)
    {
        m_angle += angle;
        return *this;
    }

    Trajectory& Trajectory::addSpeed(const double speed)
    {
        m_speed += speed;
        return *this;
    }

    Trajectory& Trajectory::addAcceleration(const double acceleration)
    {
        m_acceleration = acceleration;
        return *this;
    }

    Trajectory& Trajectory::setStatic(const bool tStatic)
    {
        m_static = tStatic;
        return *this;
    }

    double Trajectory::getAngle() const
    {
        return m_angle;
    }

    double Trajectory::getSpeed() const
    {
        return m_speed;
    }

    double Trajectory::getAcceleration() const
    {
        return m_acceleration;
    }

    bool Trajectory::getStatic() const
    {
        return m_static;
    }

    Transform::Units Trajectory::getUnit() const
    {
        return m_unit;
    }

    void Trajectory::addCheck(const TrajectoryCheckFunction& check)
    {
        m_checks.push_back(check);
    }

    std::vector<TrajectoryCheckFunction>& Trajectory::getChecks()
    {
        return m_checks;
    }

    void Trajectory::onCollide(const OnCollideCallback& callback)
    {
        m_onCollideCallback = callback;
    }

    OnCollideCallback& Trajectory::getOnCollideCallback()
    {
        return m_onCollideCallback;
    }
} // namespace obe::Collision