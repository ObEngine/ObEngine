#pragma once

#include <entt/entt.hpp>
#include <vili/node.hpp>

#include <Entities/Entity.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Texture.hpp>
#include <Transform/Rect.hpp>

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
        : public Entity<Transform::Rect, Graphics::Texture, SpriteTexturePath, Drawable,
              Graphics::Color, Graphics::PositionTransformer>
    {
    public:
        SpriteEntity(entt::registry& registry, const std::string& id);
        ~SpriteEntity() override = default;

        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;
    };

    void drawSystem(const entt::registry& registry, const Scene::Camera& camera,
        Graphics::RenderTarget& surface);
}
