#pragma once

#include <Transform/Units.hpp>
#include <Types/Togglable.hpp>

namespace obe
{
    namespace Collision
    {
        class TrajectoryNode;

        /**
         * \brief A Trajectory makes a TrajectoryNode moves using angle, speed and acceleration (Linear Trajectory)
         */
        class Trajectory : public Types::Togglable
        {
        private:
            double m_angle = 0;
            double m_speed = 0;
            double m_acceleration = 0;
            bool m_static = false;
            Transform::Units m_unit;
            friend class TrajectoryNode;
        public:
            Trajectory(Transform::Units unit = Transform::Units::WorldUnits);
            Trajectory* setAngle(double angle);
            Trajectory* setSpeed(double speed);
            Trajectory* setAcceleration(double acceleration);
            Trajectory* addAngle(double angle);
            Trajectory* addSpeed(double speed);
            Trajectory* addAcceleration(double acceleration);
            Trajectory* setStatic(bool tStatic);
            double getAngle() const;
            double getSpeed() const;
            double getAcceleration() const;
            bool getStatic() const;
            Transform::Units getUnit() const;
        };
    }
}
