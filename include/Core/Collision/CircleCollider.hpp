#pragma once

#include <Collision/Collider.hpp>

namespace obe::collision
{
    class CircleCollider : public Collider
    {
    private:
        c2Circle m_shape = {};

    protected:
        [[nodiscard]] const void* get_c2_shape() const override;
        [[nodiscard]] const c2x* get_c2_space_transform() const override;
        void update_shape();

    public:
        static constexpr ColliderType Type = ColliderType::Circle;
        [[nodiscard]] ColliderType get_collider_type() const override;

        CircleCollider();

        [[nodiscard]] transform::AABB get_bounding_box() const override;
        [[nodiscard]] transform::Vector2 get_position() const override;
        void set_position(const transform::Vector2& position) override;
        void move(const transform::Vector2& position) override;

        [[nodiscard]] float get_radius() const;
        void set_radius(float radius);
    };
}