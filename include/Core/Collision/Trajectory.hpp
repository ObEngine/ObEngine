#pragma once

#include <functional>
#include <optional>
#include <vector>

#include <Collision/Collider.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Units.hpp>
#include <Types/Togglable.hpp>

namespace obe::animation
{
    template <class T>
    class TweenImpl;
}

namespace obe::collision
{
    class TrajectoryNode;
    class Trajectory;

    using OnCollideCallback
        = std::function<void(Trajectory&, transform::UnitVector, const Collider*)>;
    using TrajectoryCheckFunction
        = std::function<void(Trajectory&, transform::UnitVector&, const Collider*)>;
    using OnChangeCallback = std::function<void(Trajectory&, std::string)>;
    using ReachableColliderAcceptor = std::function<bool(Trajectory&, const Collider*)>;

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
        ReachableColliderAcceptor m_reachable_collider_acceptor;
        double m_speed = 0;
        bool m_static = false;
        transform::Units m_unit;
        friend class TrajectoryNode;

    public:
        Trajectory(transform::Units unit = transform::Units::SceneUnits);
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
        [[nodiscard]] transform::Units get_unit() const;
        void on_collide(const OnCollideCallback& callback);
        void on_change(const OnChangeCallback& callback);
        Trajectory& set_acceleration(double acceleration);
        Trajectory& set_angle(double angle);
        Trajectory& set_speed(double speed);
        Trajectory& set_static(bool static_);

        const ReachableColliderAcceptor& get_reachable_collider_acceptor() const;
        void set_reachable_collider_acceptor(const ReachableColliderAcceptor& acceptor);
    };
} // namespace obe::collision
