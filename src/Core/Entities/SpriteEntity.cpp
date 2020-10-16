#include <Entities/SpriteEntity.hpp>

namespace obe::Entities
{
    SpriteEntity::SpriteEntity(entt::registry& registry, const std::string& id)
        : Entity(registry, id)
    {
    }

    vili::node SpriteEntity::dump() const
    {
        vili::node result;

        // Texture attributes
        SpriteTexturePath& texturePath = m_registry.get<SpriteTexturePath>(m_entity);
        result.emplace("path", texturePath.texturePath);

        // Rect attributes
        Transform::Rect& rect = m_registry.get<Transform::Rect>(m_entity);
        result.emplace("rect",
            vili::object { { "x", rect.x() }, { "y", rect.y() },
                { "width", rect.width() }, { "height", rect.height() },
                { "unit", Transform::unitsToString(rect.getPosition().unit) } });

        result.emplace("rotation", rect.getRotation());

        // Drawable attributes
        Drawable& drawable = m_registry.get<Drawable>(m_entity);
        result.emplace("layer", drawable.layer);
        if (!drawable.visible)
            result.emplace("visible", drawable.visible);

        // Color attributes
        const Graphics::Color& color = m_registry.get<Graphics::Color>(m_entity);
        if (color != Graphics::Color::White)
        {
            result.emplace("color",
                vili::object { { "r", color.r }, { "g", color.g }, { "b", color.b },
                    { "a", color.a } });
        }

        // PositionTransformer attributes
        const Graphics::PositionTransformer& positionTransformer
            = m_registry.get<Graphics::PositionTransformer>(m_entity);
        result.emplace("transform",
            vili::object { { "x", positionTransformer.getXTransformerName() },
                { "y", positionTransformer.getYTransformerName() } });

        return result;
    }

    void SpriteEntity::load(const vili::node& data)
    {
    }
}
