#include <Collision/ColliderComponent.hpp>
#include <Collision/Exceptions.hpp>

namespace obe::collision
{
    void ColliderComponent::load_capsule(const vili::node& data)
    {
    }

    void ColliderComponent::load_circle(const vili::node& data)
    {
        auto new_collider = CircleCollider();
        new_collider.set_radius(data.at("radius").as<vili::number>());
        m_collider = new_collider;
    }

    void ColliderComponent::load_polygon(const vili::node& data)
    {
        auto new_collider = PolygonCollider();
        for (const auto& point : data.at("points").as<vili::array>())
        {
            const transform::UnitVector point_position(point.at("x"), point.at("y"), m_unit);
            new_collider.add_point(point_position);
        }
        m_collider = new_collider;
    }

    void ColliderComponent::load_rectangle(const vili::node& data)
    {
        /* auto new_collider = RectangleCollider();
        const transform::UnitVector size(data.at("width"), data.at("height"), m_unit);
        new_collider.set_size(size);
        m_collider = new_collider;*/
        const double width = data.at("width");
        const double height = data.at("height");
        auto new_collider = ComplexPolygonCollider();
        new_collider.add_point(transform::UnitVector(0, 0, m_unit));
        new_collider.add_point(transform::UnitVector(width, 0, m_unit));
        new_collider.add_point(transform::UnitVector(width, height, m_unit));
        new_collider.add_point(transform::UnitVector(0, height, m_unit));
        m_collider = new_collider;
    }

    void ColliderComponent::load_complex_polygon(const vili::node& data)
    {
        auto new_collider = ComplexPolygonCollider();
        for (const auto& point : data.at("points").as<vili::array>())
        {
            const transform::UnitVector point_position(point.at("x"), point.at("y"), m_unit);
            new_collider.add_point(point_position);
        }
        m_collider = new_collider;
    }

    vili::node ColliderComponent::dump_capsule() const
    {
        return vili::object {};
    }

    vili::node ColliderComponent::dump_circle() const
    {
        const float radius = std::get<CircleCollider>(m_collider).get_radius();
        return vili::object { { "type", "Circle" }, { "radius", radius } };
    }

    vili::node ColliderComponent::dump_polygon() const
    {
        const transform::Polygon polygon = std::get<PolygonCollider>(m_collider).get_polygon();
        const auto points = polygon.get_all_points();
        vili::array points_dump = {};
        for (const auto& point : points)
        {
            points_dump.push_back(vili::object { { "x", point.x }, { "y", point.y } });
        }
        return vili::object { { "type", "Polygon" }, { "points", points_dump } };
    }

    vili::node ColliderComponent::dump_rectangle() const
    {
        const transform::UnitVector size = std::get<RectangleCollider>(m_collider).get_size();
        return vili::object { { "type", "Rectangle" }, { "width", size.x }, { "height", size.y } };
    }

    vili::node ColliderComponent::dump_complex_polygon() const
    {
        const transform::Polygon polygon = std::get<PolygonCollider>(m_collider).get_polygon();
        const auto points = polygon.get_all_points();
        vili::array points_dump = {};
        for (const auto& point : points)
        {
            points_dump.push_back(vili::object { { "x", point.x }, { "y", point.y } });
        }
        return vili::object { { "type", "ComplexPolygon" }, { "points", points_dump } };
    }

    vili::node ColliderComponent::schema() const
    {
        return vili::object { { "x", vili::object { { "type", vili::number_typename } } },
            { "y", vili::object { { "type", vili::number_typename } } },
            { "unit",
                vili::object { { "type", vili::number_typename },
                    { "values", vili::array { "SceneUnits", "ScenePixels" } } } },
            { "type",
                vili::object { { "type", vili::string_typename },
                    { "values",
                        vili::array {
                            "Capsule", "Circle", "Polygon", "Rectangle", "ComplexPolygon" } } } } };
    }

    ColliderComponent::ColliderComponent(const std::string& id)
        : Component(id)
    {
    }

    vili::node ColliderComponent::dump() const
    {
        vili::node collider_dump;
        if (std::holds_alternative<CapsuleCollider>(m_collider))
        {
            collider_dump = dump_capsule();
        }
        else if (std::holds_alternative<CircleCollider>(m_collider))
        {
            collider_dump = dump_circle();
        }
        else if (std::holds_alternative<PolygonCollider>(m_collider))
        {
            collider_dump = dump_polygon();
        }
        else if (std::holds_alternative<RectangleCollider>(m_collider))
        {
            collider_dump = dump_rectangle();
        }
        else
        {
            throw exceptions::InvalidColliderComponentType(m_id, "?");
        }

        std::visit(
            [&collider_dump](auto&& collider)
            {
                const auto& position = collider.get_position();
                const std::string& tag = collider.get_tag();
                collider_dump.insert("x", position.x);
                collider_dump.insert("y", position.y);
                collider_dump.insert("tag", tag);
            },
            m_collider);

        return collider_dump;
    }

    void ColliderComponent::load(const vili::node& data)
    {
        const double x = data.at("x");
        const double y = data.at("y");
        transform::Units unit;
        if (data.contains("unit"))
        {
            m_unit = transform::UnitsMeta::from_string(data.at("unit"));
        }
        std::string tag;
        if (data.contains("tag"))
        {
            tag = data.at("tag");
        }
        const std::string collider_type_str = data.at("type");

        switch (ColliderTypeMeta::from_string(collider_type_str))
        {
        case ColliderType::Capsule:
            load_capsule(data);
            break;
        case ColliderType::Circle:
            load_circle(data);
            break;
        case ColliderType::Rectangle:
            load_rectangle(data);
            break;
        case ColliderType::Polygon:
            load_polygon(data);
            break;
        case ColliderType::Collider:
            throw exceptions::InvalidColliderComponentType(m_id, collider_type_str);
        }
        std::visit(
            [this, x, y, tag](auto&& collider)
            {
                collider.set_position(transform::UnitVector(x, y, m_unit));
                collider.set_tag(tag);
            },
            m_collider);
    }

    ColliderType ColliderComponent::get_collider_type() const
    {
        if (std::holds_alternative<CapsuleCollider>(m_collider))
        {
            return ColliderType::Capsule;
        }
        else if (std::holds_alternative<CircleCollider>(m_collider))
        {
            return ColliderType::Circle;
        }
        else if (std::holds_alternative<PolygonCollider>(m_collider))
        {
            return ColliderType::Polygon;
        }
        else if (std::holds_alternative<RectangleCollider>(m_collider))
        {
            return ColliderType::Rectangle;
        }
        return ColliderType::Collider;
    }

    std::string_view ColliderComponent::type() const
    {
        return ColliderComponent::ComponentType;
    }

    Collider* ColliderComponent::get_inner_collider()
    {
        Collider* collider = std::visit(
            [](auto& collider_variant) -> Collider*
            {
                return &collider_variant;
            },
            m_collider);
        return collider;
    }

    const Collider* ColliderComponent::get_inner_collider() const
    {
        const Collider* collider = std::visit(
            [](auto& collider_variant) -> const Collider*
            {
                return &collider_variant;
            },
            m_collider);
        return collider;
    }
}
