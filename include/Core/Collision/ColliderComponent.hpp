#pragma once

#include <Collision/CapsuleCollider.hpp>
#include <Collision/CircleCollider.hpp>
#include <Collision/PolygonCollider.hpp>
#include <Collision/RectangleCollider.hpp>
#include <Component/Component.hpp>

#include <variant>

namespace obe::collision
{
    class ColliderComponent : public component::Component<ColliderComponent>
    {
    private:
        std::variant<CapsuleCollider, CircleCollider, PolygonCollider, RectangleCollider>
            m_collider;

        void load_capsule(const vili::node& data);
        void load_circle(const vili::node& data);
        void load_polygon(const vili::node& data);
        void load_rectangle(const vili::node& data);
    protected:
        [[nodiscard]] vili::node schema() const override;
    public:
        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;

        [[nodiscard]] ColliderType get_collider_type() const;
        [[nodiscard]] std::string_view type() const override;
    };
}