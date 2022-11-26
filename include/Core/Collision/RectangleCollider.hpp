#pragma once

#include <Collision/Collider.hpp>

namespace obe::collision
{
    class RectangleCollider : public Collider
    {
    private:
        c2AABB m_shape = {};
        transform::Vector2 m_size;

    protected:
        [[nodiscard]] const void* get_c2_shape() const override;
        [[nodiscard]] const c2x* get_c2_space_transform() const override;
        void update_shape();

    public:
        static constexpr ColliderType Type = ColliderType::Rectangle;
        [[nodiscard]] ColliderType get_collider_type() const override;

        RectangleCollider();
        explicit RectangleCollider(const transform::Vector2& size);
        RectangleCollider(const transform::Vector2& position, const transform::Vector2& size);

        [[nodiscard]] transform::AABB get_bounding_box() const override;
        [[nodiscard]] transform::Vector2 get_position() const override;
        void set_position(const transform::Vector2& position) override;
        void move(const transform::Vector2& position) override;

        [[nodiscard]] transform::Vector2 get_size() const;
        void set_size(const transform::Vector2& size);
    };
}