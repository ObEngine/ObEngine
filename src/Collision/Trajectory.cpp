#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>
#include <Utils/MathUtils.hpp>

namespace obe
{
    namespace Collision
    {
        Trajectory::Trajectory(Transform::Units unit) : Togglable(true)
        {
            m_unit = unit;
        }

        Trajectory* Trajectory::setAngle(double angle)
        {
            m_angle = angle;
            return this;
        }

        Trajectory* Trajectory::setSpeed(double speed)
        {
            m_speed = speed;
            return this;
        }

        Trajectory* Trajectory::setAcceleration(double acceleration)
        {
            m_acceleration = acceleration;
            return this;
        }

        Trajectory* Trajectory::addAngle(double angle)
        {
            m_angle += angle;
            return this;
        }

        Trajectory* Trajectory::addSpeed(double speed)
        {
            m_speed += speed;
            return this;
        }

        Trajectory* Trajectory::addAcceleration(double acceleration)
        {
            m_acceleration = acceleration;
            return this;
        }

        Trajectory* Trajectory::setStatic(bool tStatic)
        {
            m_static = tStatic;
            return this;
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
    }
}