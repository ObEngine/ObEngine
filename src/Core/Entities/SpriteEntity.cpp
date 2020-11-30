#include "Graphics/Exceptions.hpp"

#include <Scene/Scene.hpp>

#include <Entities/SpriteEntity.hpp>

#include <sfe/ComplexSprite.hpp>

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
        Graphics::Texture& texture = m_registry.get<Graphics::Texture>(m_entity);
        if (data.contains("path"))
        {
            texture.loadFromFile(System::Path(data.at("path")).find().path());
        }

        if (data.contains("antiAliasing"))
        {
            texture.setAntiAliasing(data.at("antiAliasing"));
        }

        Transform::Rect& rect = m_registry.get<Transform::Rect>(m_entity);
        if (data.contains("rect"))
        {
            obe::Transform::Referential referentialPos;
            Transform::UnitVector spritePos(0, 0);
            Transform::UnitVector spriteSize(1, 1);
            const vili::node& dataRect = data.at("rect");
            Transform::Units unit = Transform::Units::SceneUnits;
            if (dataRect.contains("unit"))
            {
                unit = Transform::stringToUnits(dataRect.at("unit"));
            }
            spritePos.unit = unit;
            spritePos.x = dataRect.at("x");
            spritePos.y = dataRect.at("y");
            spriteSize.unit = unit;
            spriteSize.x = dataRect.at("width");
            spriteSize.y = dataRect.at("height");
            spritePos = spritePos.to<Transform::Units::SceneUnits>();
            spriteSize = spriteSize.to<Transform::Units::SceneUnits>();
            if (dataRect.contains("referential"))
                referentialPos
                    = obe::Transform::Referential::FromString(dataRect.at("referential"));

            rect.setPosition(spritePos, referentialPos);
            rect.setSize(spriteSize, referentialPos);
        }

        if (data.contains("rotation"))
        {
            rect.setRotation(
                data.at("rotation"), rect.getPosition(Transform::Referential::Center));
        }

        Drawable& drawable = m_registry.get<Drawable>(m_entity);
        if (data.contains("layer"))
        {
            drawable.layer = data.at("layer");
        }

        if (data.contains("visible"))
        {
            drawable.visible = data.at("visible");
        }

        if (data.contains("transform"))
        {
            std::string spriteXTransformer = "Camera";
            std::string spriteYTransformer = "Camera";
            const vili::node& transform = data.at("transform");
            if (transform.contains("x"))
            {
                spriteXTransformer = transform.at("x");
            }
            if (transform.contains("y"))
            {
                spriteYTransformer = transform.at("y");
            }

            m_registry.replace<Graphics::PositionTransformer>(
                m_entity, spriteXTransformer, spriteYTransformer);
        }

        if (data.contains("color"))
        {
            Graphics::Color spriteColor = Graphics::Color::White;
            const vili::node& dataColor = data.at("color");
            if (dataColor.is<vili::object>() && dataColor.contains("r"))
            {
                const double r = dataColor.at("r").as<vili::number>();
                const double g = dataColor.at("g").as<vili::number>();
                const double b = dataColor.at("b").as<vili::number>();
                const double a = dataColor.contains("a")
                    ? dataColor.at("a").as<vili::number>()
                    : 255.f;
                spriteColor.fromRgb(r, g, b, a);
            }
            else if (dataColor.is<vili::object>() && dataColor.contains("H"))
            {
                const int H = dataColor.at("H").as<vili::integer>();
                const double S = dataColor.at("S").as<vili::number>();
                const double V = dataColor.at("V").as<vili::number>();
                spriteColor.fromHsv(H, S, V);
            }
            else if (dataColor.is<vili::string>())
            {
                spriteColor.fromString(dataColor);
            }
            else
            {
                throw Graphics::Exceptions::InvalidSpriteColorType(
                    vili::to_string(dataColor.type()), dataColor.dump(), EXC_INFO);
            }

            m_registry.replace<Graphics::Color>(m_entity, spriteColor);
        }
    }

    sf::Vertex toSfVertex(const Transform::UnitVector& uv)
    {
        return sf::Vertex(sf::Vector2f(uv.x, uv.y));
    }

    void drawSystem(const entt::registry& registry, const Scene::Camera& camera,
        Graphics::RenderTarget& surface)
    {
        /*registry.sort<Drawable>(
            [](const auto& lhs, const auto& rhs) { return lhs.layer < rhs.layer; });*/
        registry
            .view<const Types::Identifiable, const Drawable, const Transform::Rect,
                const Graphics::Texture, const Graphics::PositionTransformer>()
            .each([&camera, &surface](const Types::Identifiable& identifiable,
                      const Drawable& drawable, const Transform::Rect& rect,
                      const Graphics::Texture& texture,
                      const Graphics::PositionTransformer& transformer) {
                Debug::Log->info("Displaying element '{}'", identifiable.getId());
                if (!drawable.visible)
                {
                    return;
                }
                std::array<sf::Vertex, 4> vertices;

                const Transform::UnitVector cameraPosition = camera.getPosition();
                vertices[0] = toSfVertex(
                    transformer(rect.getPosition(Transform::Referential::TopLeft),
                        cameraPosition, drawable.layer)
                        .to<Transform::Units::ScenePixels>());
                vertices[1] = toSfVertex(
                    transformer(rect.getPosition(Transform::Referential::BottomLeft),
                        cameraPosition, drawable.layer)
                        .to<Transform::Units::ScenePixels>());
                vertices[2] = toSfVertex(
                    transformer(rect.getPosition(Transform::Referential::TopRight),
                        cameraPosition, drawable.layer)
                        .to<Transform::Units::ScenePixels>());
                vertices[3] = toSfVertex(
                    transformer(rect.getPosition(Transform::Referential::BottomRight),
                        cameraPosition, drawable.layer)
                        .to<Transform::Units::ScenePixels>());

                sfe::ComplexSprite sprite;

                sprite.setTexture(texture);
                sprite.setVertices(vertices);

                surface.draw(sprite);
            });
    }
}
