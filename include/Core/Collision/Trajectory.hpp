#pragma once

#include <kaguya/kaguya.hpp>

#include <Transform/Units.hpp>
#include <Types/Togglable.hpp>

namespace obe::Collision
{
    class TrajectoryNode;

    /**
     * \brief A Trajectory makes a TrajectoryNode moves using angle, speed and
     * acceleration (Linear Trajectory)
     */
    class Trajectory : public Types::Togglable
    {
    private:
        double m_acceleration = 0;
        double m_angle = 0;
        std::vector<kaguya::LuaFunction> m_checks;
        kaguya::LuaFunction m_onCollideCallback;
        double m_speed = 0;
        bool m_static = false;
        Transform::Units m_unit;
        friend class TrajectoryNode;

    public:
        Trajectory(Transform::Units unit = Transform::Units::SceneUnits);
        Trajectory* addAcceleration(double acceleration);
        Trajectory* addAngle(double angle);
        void addCheck(const kaguya::LuaFunction& check);
        Trajectory* addSpeed(double speed);
        double getAcceleration() const;
        double getAngle() const;
        std::vector<kaguya::LuaFunction>& getChecks();
        kaguya::LuaFunction& getOnCollideCallback();
        double getSpeed() const;
        bool getStatic() const;
        Transform::Units getUnit() const;
        void onCollide(const kaguya::LuaFunction& callback);
        Trajectory* setAcceleration(double acceleration);
        Trajectory* setAngle(double angle);
        Trajectory* setSpeed(double speed);
        Trajectory* setStatic(bool tStatic);
    };
} // namespace obe::Collision
