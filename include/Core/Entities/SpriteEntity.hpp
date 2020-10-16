#pragma once

#include <entt/entt.hpp>
#include <vili/node.hpp>

#include <Entities/Entity.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/Texture.hpp>
#include <Transform/Rect.hpp>
#include <Graphics/PositionTransformers.hpp>


namespace obe::Entities
{
    struct Drawable
    {
        int layer;
        bool visible;
    };

    struct SpriteTexturePath
    {
        std::string texturePath;
    };
    
    class SpriteEntity
        : public Entity<Transform::Rect, Graphics::Texture, SpriteTexturePath,
              Drawable, Graphics::Color, Graphics::PositionTransformer>
    {
    public:
        SpriteEntity(entt::registry& registry, const std::string& id);
        ~SpriteEntity() override = default;

        [[nodiscard]] vili::node dump() const override;
        virtual void load(const vili::node& data);
    };
}
