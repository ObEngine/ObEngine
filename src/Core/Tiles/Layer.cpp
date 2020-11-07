#include <set>

#include <Debug/Logger.hpp>
#include <Tiles/Exceptions.hpp>
#include <Tiles/Layer.hpp>

namespace obe::Tiles
{
    void TextureQuadsIndex::transform(const TileInfo& info)
    {
        if (info.flippedDiagonally)
        {
            std::swap(q0, q2);
        }
        if (info.flippedHorizontally)
        {
            std::swap(q0, q1);
            std::swap(q2, q3);
        }
        if (info.flippedVertically)
        {
            std::swap(q0, q3);
            std::swap(q1, q2);
        }
    }

    void applyTextureQuadsTransforms(const TileInfo& info, TextureQuadsIndex& quads)
    {
        if (info.flippedDiagonally)
        {
            std::swap(quads.q0, quads.q2);
        }
        if (info.flippedHorizontally)
        {
            std::swap(quads.q0, quads.q1);
            std::swap(quads.q2, quads.q3);
        }
        if (info.flippedVertically)
        {
            std::swap(quads.q0, quads.q3);
            std::swap(quads.q1, quads.q2);
        }
    }

    void TileLayer::buildTile(uint32_t x, uint32_t y, uint32_t tileId)
    {
        if (!tileId)
            return;

        const uint32_t tileIndex = x + y * m_width;

        const TileInfo tileInfo = getTileInfo(tileId);

        const Tileset& tileset = m_tilesets.tilesetFromTileId(tileInfo.tileId);
        const uint32_t firstTileId = tileset.getFirstTileId();
        sf::VertexArray& vertices = m_cache[tileset.getFirstTileId()];
        sf::Vertex* quad = &vertices[(x + y * m_width) * 4];
        for (auto& animation : m_animations)
        {
            if (animation->getId() == tileInfo.tileId)
            {
                animation->attachQuad(quad);
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

    void TileLayer::updateQuad(sf::Vertex* quad, uint32_t tileId) const
    {
        if (!tileId)
            return;

        const TileInfo tileInfo = getTileInfo(tileId);
        const Tileset& tileset = m_tilesets.tilesetFromTileId(tileInfo.tileId);

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

    TileLayer::TileLayer(const TilesetCollection& tilesets,
        const AnimatedTiles animations, const std::string& id, int32_t layer, uint32_t x,
        uint32_t y, uint32_t width, uint32_t height, const std::vector<uint32_t>& data)
        : m_tilesets(tilesets)
        , m_animations(animations)
        , m_id(id)
        , m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_data(data)
    {
        m_layer = layer;
    }

    std::string TileLayer::getId() const
    {
        return m_id;
    }

    void TileLayer::build()
    {
        Debug::Log->info("<TileLayer> Building Layer '{}' @{} with animation @{}", m_id,
            fmt::ptr(this), fmt::ptr(&m_animations));
        m_cache.clear();
        for (const uint32_t firstTileId : m_tilesets.getTilesetsFirstTilesIds())
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
            const int64_t translateX
                = -(middleCamera.x * (Transform::UnitVector::Screen.h / 2))
                + (Transform::UnitVector::Screen.w / 2);
            const int64_t translateY
                = -(middleCamera.y * (Transform::UnitVector::Screen.h / 2))
                + (Transform::UnitVector::Screen.h / 2);

            states.transform.translate(translateX, translateY);

            const Tileset& tileset = m_tilesets.tilesetFromTileId(firstTileId);
            states.texture = &tileset.getTexture().operator const sf::Texture &();

            surface.draw(layer, states);
        }
    }

    void TileLayer::setTile(uint32_t x, uint32_t y, uint32_t tileId)
    {
        Debug::Log->info("<TileLayer> Set Tile at Layer '{}' @{} with animation @{}",
            m_id, fmt::ptr(this), fmt::ptr(&m_animations));
        if (x > m_width || y > m_height)
        {
            throw Exceptions::TilePositionOutsideLayer(x, y, m_width, m_height, EXC_INFO);
        }
        const uint32_t tileIndex = x + y * m_width;
        const uint32_t oldTileId = m_data[tileIndex];
        m_data[tileIndex] = tileId;
        if (!oldTileId)
        {
            this->buildTile(x, y, tileId);
            return;
        }
        sf::Vertex* quad = m_positions[tileIndex];
        for (auto& animation : m_animations)
        {
            if (animation->getId() == oldTileId)
            {
                animation->dettachQuad(quad);
            }
        }
        if (oldTileId && !tileId)
        {
            return;
        }
        this->updateQuad(quad, tileId);
    }

    uint32_t TileLayer::getTile(uint32_t x, uint32_t y)
    {
        return m_data[x + y * m_width];
    }
}
