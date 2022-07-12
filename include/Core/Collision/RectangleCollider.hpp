#pragma once

#include <Collision/Collider.hpp>

namespace obe::collision
{
    class RectangleCollider : public Collider
    {
    private:
        c2AABB m_shape = {};
        transform::UnitVector m_size;
    protected:
        [[nodiscard]] void* get_c2_shape() override;
        void update_shape();
    public:
        static constexpr ColliderType Type = ColliderType::Rectangle;
        [[nodiscard]] ColliderType get_collider_type() const override;

        RectangleCollider();
        explicit RectangleCollider(const transform::UnitVector& size);
        RectangleCollider(const transform::UnitVector& position, const transform::UnitVector& size);

        [[nodiscard]] transform::Rect get_bounding_box() const override;
        [[nodiscard]] transform::UnitVector get_position() const override;
        void set_position(const transform::UnitVector& position) override;
        void move(const transform::UnitVector& position) override;

        [[nodiscard]] transform::UnitVector get_size() const;
        void set_size(const transform::UnitVector& size);
    };
}