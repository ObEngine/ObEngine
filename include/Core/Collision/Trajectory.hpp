#pragma once

#include <Collision/Collider.hpp>
#include <Transform/Vector2.hpp>
#include <Types/Togglable.hpp>
#include <functional>
#include <vector>


namespace obe::animation
{
    template <class T>
    class TweenImpl;
}

namespace obe::collision
{
    class TrajectoryNode;
    class Trajectory;
    class PolygonalCollider;

    using OnCollideCallback
        = std::function<void(Trajectory&, transform::Vector2, collision::Collider*)>;
    using TrajectoryCheckFunction
        = std::function<void(Trajectory&, transform::Vector2&, collision::Collider*)>;
    using OnChangeCallback = std::function<void(Trajectory&, std::string)>;

    /**
     * \brief A Trajectory makes a TrajectoryNode moves using angle, speed and
     *        acceleration (Linear Trajectory)
     */
    class Trajectory : public types::Togglable
    {
        friend class animation::TweenImpl<Trajectory>;

    private:
        double m_acceleration = 0;
        double m_angle = 0;
        std::vector<TrajectoryCheckFunction> m_checks {};
        OnCollideCallback m_on_collide_callback;
        OnChangeCallback m_on_change_callback;
        double m_speed = 0;
        bool m_static = false;
        friend class TrajectoryNode;

    public:
        Trajectory() = default;
        Trajectory& add_acceleration(double acceleration);
        Trajectory& add_angle(double angle);
        void add_check(const TrajectoryCheckFunction& check);
        Trajectory& add_speed(double speed);
        [[nodiscard]] double get_acceleration() const;
        [[nodiscard]] double get_angle() const;
        std::vector<TrajectoryCheckFunction>& get_checks();
        OnCollideCallback& get_on_collide_callback();
        [[nodiscard]] double get_speed() const;
        [[nodiscard]] bool is_static() const;
        void on_collide(const OnCollideCallback& callback);
        void on_change(const OnChangeCallback& callback);
        Trajectory& set_acceleration(double acceleration);
        Trajectory& set_angle(double angle);
        Trajectory& set_speed(double speed);
        Trajectory& set_static(bool static_);
    };
} // namespace obe::collision
