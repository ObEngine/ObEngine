#include <Graphics/DrawUtils.hpp>
#include <Scene/Scene.hpp>
#include <Tiles/Exceptions.hpp>
#include <Tiles/Layer.hpp>

const std::string_view fragSource = "\
#version 130\n\
uniform sampler2D m;\n\
uniform sampler2D t;\n\
uniform vec2 w;\n\
uniform vec2 z;\n\
void main()\n\
{\n\
    vec4 c=texture2D(m,gl_TexCoord[0].xy/32.0);\n\
    float i=floor(c.r*255.0+c.g*65280);\n\
    vec2 a=vec2(mod(i,w.x),floor(i/w.x))/w;\n\
    vec2 b=mod((gl_TexCoord[0].xy*z)/32.0,1.0);\n\
    gl_FragColor=texture2D(t,a+b/w);\n\
    gl_FragColor.a*=c.a;\n\
}";
const std::string_view vertSource = "\
#version 130\n\
void main()\n\
{\n\
    gl_Position=gl_ModelViewProjectionMatrix*gl_Vertex;\n\
    gl_TexCoord[0]=gl_TextureMatrix[0]*gl_MultiTexCoord0;\n\
    gl_FrontColor=gl_Color;\n\
}";

namespace obe::Tiles
{
    void drawCollider(Graphics::RenderTarget& surface, const Scene::Camera& camera,
        const Collision::PolygonalCollider& collider)
    {
        if (collider.getPointsAmount() >= 3)
        {
            const Transform::UnitVector offset
                = camera.getPosition().to<Transform::Units::ScenePixels>();
            /*const Transform::UnitVector pMaster
                = this->getCentroid().to<Transform::Units::ScenePixels>();*/

            const float r = 6.f;
            // TODO: Refactor using C++20 designated initializers
            const Graphics::Utils::DrawPolygonOptions drawOptions { true, false, r };

            std::vector<Transform::UnitVector> lDrawPoints;

            for (int i = 0; i < collider.getPointsAmount(); i++)
            {
                const Transform::UnitVector point
                    = collider.get(i).to<Transform::Units::ScenePixels>();

                lDrawPoints.emplace_back(point.x - offset.x, point.y - offset.y,
                    Transform::Units::ScenePixels);
            }

            Graphics::Utils::drawPolygon(surface, lDrawPoints, drawOptions);
        }
    }

    void TileLayer::buildTile(uint32_t x, uint32_t y, uint32_t tileId)
    {
        if (!tileId)
            return;

        const uint32_t tileIndex = x + y * m_width;

        const TileInfo tileInfo = getTileInfo(tileId);

        const Tileset& tileset = m_scene.getTilesets().tilesetFromTileId(tileInfo.tileId);
        const uint32_t firstTileId = tileset.getFirstTileId();
        sf::VertexArray& vertices = m_cache[tileset.getFirstTileId()];
        sf::Vertex* quad = &vertices[(x + y * m_width) * 4];
        for (auto& animation : m_scene.getAnimatedTiles())
        {
            if (animation->getId() == tileInfo.tileId)
            {
                animation->attachQuad(quad, tileInfo);
                break;
            }
        }
        for (auto& collider : m_scene.getColliderModels())
        {
            if (collider->getId() == std::to_string(tileInfo.tileId))
            {
                m_colliders[tileIndex] = &m_scene.getScene().createCollider();
                (*m_colliders[tileIndex]) = *collider;
                m_colliders[tileIndex]->setParentId("tile_" + std::to_string(tileInfo.tileId));
                const Transform::Rect boundingBox
                    = m_colliders.at(tileIndex)->getBoundingBox();
                Transform::UnitVector offset
                    = m_colliders.at(tileIndex)->get(0) - boundingBox.getPosition();
                offset += boundingBox.getPosition();
                // TODO: Fix this horrible code
                // TODO: I mean, really, fix this
                auto cameraSizeBackup = m_scene.getScene().getCamera().getSize().y / 2;
                m_scene.getScene().getCamera().setSize(1);
                m_colliders.at(tileIndex)->setPosition(
                    Transform::UnitVector(x * tileset.getTileWidth(),
                        y * tileset.getTileHeight(), Transform::Units::ScenePixels)
                    + offset);
                m_scene.getScene().getCamera().setSize(cameraSizeBackup);
            }
        }
        for (const auto& gameObject : m_scene.getGameObjectsModels())
        {
            if (gameObject.at("tileId").as<vili::integer>() == tileInfo.tileId)
            {
                std::string gameObjectId = Utils::String::replace(gameObject.at("id"), "{index}", std::to_string(m_scene.getScene().getGameObjectAmount()));
                vili::node requirements = gameObject.at("Requires");
                Transform::UnitVector gameObjectPosition(x * tileset.getTileWidth(),
                    y * tileset.getTileHeight(), Transform::Units::ScenePixels);
                requirements["x"] = requirements["x"].as_number() + gameObjectPosition.x;
                requirements["y"] = requirements["y"].as_number() + gameObjectPosition.y;
                m_scene.getScene()
                    .createGameObject(gameObject.at("type"), gameObjectId)
                    .initFromVili(requirements);
            }
        }
        m_positions[tileIndex] = quad;

        const uint32_t tileWidth = tileset.getTileWidth();
        const uint32_t tileHeight = tileset.getTileHeight();

        const int textureX
            = (tileInfo.tileId - firstTileId) % (tileset.getImageWidth() / tileWidth);
        const int textureY
            = (tileInfo.tileId - firstTileId) / (tileset.getImageWidth() / tileWidth);

        TextureQuadsIndex quads;
        quads.transform(tileInfo);

        quad[0].position = sf::Vector2f(x * tileWidth, y * tileHeight);
        quad[1].position = sf::Vector2f((x + 1) * tileWidth, y * tileHeight);
        quad[2].position = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
        quad[3].position = sf::Vector2f(x * tileWidth, (y + 1) * tileHeight);

        quad[quads.q0].texCoords
            = sf::Vector2f(textureX * tileWidth, textureY * tileHeight);
        quad[quads.q1].texCoords
            = sf::Vector2f((textureX + 1) * tileWidth, textureY * tileHeight);
        quad[quads.q2].texCoords
            = sf::Vector2f((textureX + 1) * tileWidth, (textureY + 1) * tileHeight);
        quad[quads.q3].texCoords
            = sf::Vector2f(textureX * tileWidth, (textureY + 1) * tileHeight);
    }

    void TileLayer::clearTile(uint32_t x, uint32_t y)
    {
        const uint32_t tileIndex = x + y * m_width;
        sf::Vertex* quad = m_positions[tileIndex];
        const uint32_t oldTileId = m_data[tileIndex];
        for (auto& animation : m_scene.getAnimatedTiles())
        {
            if (animation->getId() == oldTileId)
            {
                animation->dettachQuad(quad);
                break;
            }
        }
        if (const auto tileCollision = m_colliders.find(tileIndex); tileCollision != m_colliders.end())
        {
            m_scene.getScene().removeCollider(tileCollision->second->getId());
            m_colliders.erase(tileCollision);
        }
        
        // TODO: Clear GameObjects when necessary
        this->clearQuad(quad);
        m_positions.erase(tileIndex);
    }

    void TileLayer::updateQuad(sf::Vertex* quad, uint32_t tileId) const
    {
        if (!tileId)
            return;

        const TileInfo tileInfo = getTileInfo(tileId);
        const Tileset& tileset = m_scene.getTilesets().tilesetFromTileId(tileInfo.tileId);

        const uint32_t firstTileId = tileset.getFirstTileId();

        const uint32_t tileWidth = tileset.getTileWidth();
        const uint32_t tileHeight = tileset.getTileHeight();

        const int textureX
            = (tileId - firstTileId) % (tileset.getImageWidth() / tileWidth);
        const int textureY
            = (tileId - firstTileId) / (tileset.getImageWidth() / tileWidth);

        TextureQuadsIndex quads;
        quads.transform(tileInfo);

        quad[quads.q0].texCoords
            = sf::Vector2f(textureX * tileWidth, textureY * tileHeight);
        quad[quads.q1].texCoords
            = sf::Vector2f((textureX + 1) * tileWidth, textureY * tileHeight);
        quad[quads.q2].texCoords
            = sf::Vector2f((textureX + 1) * tileWidth, (textureY + 1) * tileHeight);
        quad[quads.q3].texCoords
            = sf::Vector2f(textureX * tileWidth, (textureY + 1) * tileHeight);
    }

    void TileLayer::clearQuad(sf::Vertex* quad) const
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            quad[i].position = sf::Vector2f(0, 0);
            quad[i].texCoords = sf::Vector2f(0, 0);
        }
    }

    TileLayer::TileLayer(const TileScene& scene, const std::string& id, int32_t layer,
        uint32_t x, uint32_t y, uint32_t width, uint32_t height,
        std::vector<uint32_t> data)
        : m_scene(scene)
        , m_id(id)
        , m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_data(std::move(data))
    {
        m_layer = layer;
        m_visible = true;
    }

    std::string TileLayer::getId() const
    {
        return m_id;
    }

    void TileLayer::build()
    {
        m_cache.clear();
        for (const uint32_t firstTileId :
            m_scene.getTilesets().getTilesetsFirstTilesIds())
        {
            m_cache[firstTileId] = sf::VertexArray {};
            m_cache[firstTileId].setPrimitiveType(sf::Quads);
            m_cache[firstTileId].resize(m_width * m_height * 4);
        }

        for (unsigned int x = 0; x < m_width; ++x)
        {
            for (unsigned int y = 0; y < m_height; ++y)
            {
                const uint32_t tileIndex = x + y * m_width;
                const uint32_t tileId = m_data[tileIndex];
                buildTile(x, y, tileId);
            }
        }
    }

    void TileLayer::draw(Graphics::RenderTarget& surface, const Scene::Camera& camera)
    {
        for (const auto& [firstTileId, layer] : m_cache)
        {
            sf::RenderStates states;
            states.transform = sf::Transform::Identity;

            const Transform::UnitVector middleCamera
                = camera.getPosition(Transform::Referential::Center)
                      .to<Transform::Units::SceneUnits>();
            const Transform::UnitVector cameraSize = camera.getSize();
            const float middleX = Transform::UnitVector::Screen.w / 2.0;
            const float middleY = Transform::UnitVector::Screen.h / 2.0;
            const double cameraScale = 1.0 / (cameraSize.y / 2.0);

            states.transform.scale(cameraScale, cameraScale, middleX, middleY);
            float translateX
                = -(middleCamera.x * (Transform::UnitVector::Screen.h / 2.f))
                + (Transform::UnitVector::Screen.w / 2);
            float translateY
                = -(middleCamera.y * (Transform::UnitVector::Screen.h / 2.f))
                + (Transform::UnitVector::Screen.h / 2);

            if (!m_scene.isSmooth())
            {
                translateX = std::round(translateX);
                translateY = std::round(translateY);
            }

            states.transform.translate(translateX, translateY);

            const Tileset& tileset = m_scene.getTilesets().tilesetFromTileId(firstTileId);
            states.texture = &tileset.getTexture().operator const sf::Texture &();

            surface.draw(layer, states);
        }
        /*for (const auto& collider : m_colliders)
        {
            drawCollider(surface, camera, *collider.second);
        }*/
    }

    void TileLayer::setTile(uint32_t x, uint32_t y, uint32_t tileId)
    {
        if (x >= m_width || y >= m_height || x < 0 || y < 0)
        {
            throw Exceptions::TilePositionOutsideLayer(x, y, m_width, m_height, EXC_INFO);
        }
        const uint32_t tileIndex = x + y * m_width;
        const uint32_t oldTileId = m_data[tileIndex];
        if (oldTileId)
        {
            this->clearTile(x, y);
        }
        m_data[tileIndex] = tileId;
        this->buildTile(x, y, tileId);
    }

    uint32_t TileLayer::getTile(uint32_t x, uint32_t y)
    {
        if (x >= m_width || y >= m_height || x < 0 || y < 0)
        {
            throw Exceptions::TilePositionOutsideLayer(x, y, m_width, m_height, EXC_INFO);
        }
        return m_data[x + y * m_width];
    }
}
