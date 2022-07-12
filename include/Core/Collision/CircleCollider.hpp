#pragma once

#include <Collision/Collider.hpp>

namespace obe::collision
{
    class CircleCollider : public Collider
    {
    private:
        c2Circle m_shape = {};

    protected:
        [[nodiscard]] void* get_c2_shape() override;
        void update_shape();

    public:
        static constexpr ColliderType Type = ColliderType::Circle;
        [[nodiscard]] ColliderType get_collider_type() const override;

        CircleCollider();

        [[nodiscard]] transform::Rect get_bounding_box() const override;
        [[nodiscard]] transform::UnitVector get_position() const override;
        void set_position(const transform::UnitVector& position) override;
        void move(const transform::UnitVector& position) override;

        [[nodiscard]] float get_radius() const;
        void set_radius(float radius);
    };
}