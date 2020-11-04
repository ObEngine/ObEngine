#include <set>

#include <Tiles/Exceptions.hpp>
#include <Tiles/Layer.hpp>

namespace obe::Tiles
{
    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    TileLayer::TileLayer(const TilesetCollection& tilesets, const std::string& id,
        int32_t layer, uint32_t x, uint32_t y, uint32_t width, uint32_t height,
        const std::vector<uint32_t>& data)
        : m_tilesets(tilesets)
        , m_id(id)
        , m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_data(data)
    {
        m_layer = layer;
    }

    void TileLayer::build()
    {
        m_cache.clear();
        std::unordered_map<uint32_t, uint32_t> differentTilesets;
        std::unordered_map<uint32_t, uint32_t> quadCounters;

        for (auto tile : m_data)
        {
            tile &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG
                | FLIPPED_DIAGONALLY_FLAG);
            if (tile)
            {
                const uint32_t firstTileId
                    = m_tilesets.tilesetFromTileId(tile).getFirstTileId();
                if (differentTilesets.count(firstTileId))
                {
                    differentTilesets[firstTileId]++;
                }
                else
                {
                    m_cache[firstTileId] = sf::VertexArray {};
                    differentTilesets.emplace(firstTileId, 1);
                    quadCounters.emplace(firstTileId, 0);
                }
            }
        }

        for (auto& [firstTileId, vertices] : m_cache)
        {
            vertices.setPrimitiveType(sf::Quads);
            vertices.resize(differentTilesets[firstTileId] * 4 + 1);
        }

        for (unsigned int x = 0; x < m_width; ++x)
        {
            for (unsigned int y = 0; y < m_height; ++y)
            {
                uint32_t tileId = m_data[x + y * m_width];
                if (tileId)
                {
                    const bool flipped_horizontally
                        = (tileId & FLIPPED_HORIZONTALLY_FLAG);
                    const bool flipped_vertically = (tileId & FLIPPED_VERTICALLY_FLAG);
                    const bool flipped_diagonally = (tileId & FLIPPED_DIAGONALLY_FLAG);

                    tileId &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG
                        | FLIPPED_DIAGONALLY_FLAG);

                    const Tileset& tileset = m_tilesets.tilesetFromTileId(tileId);
                    const uint32_t firstTileId = tileset.getFirstTileId();
                    sf::VertexArray& vertices = m_cache[tileset.getFirstTileId()];
                    sf::Vertex* quad = &vertices[quadCounters[firstTileId] * 4];
                    m_positions[TilePosition { x, y }] = quad;

                    const uint32_t tileWidth = tileset.getTileWidth();
                    const uint32_t tileHeight = tileset.getTileHeight();

                    const int textureX
                        = (tileId - firstTileId) % (tileset.getImageWidth() / tileWidth);
                    const int textureY
                        = (tileId - firstTileId) / (tileset.getImageWidth() / tileWidth);

                    uint8_t quad0 = 0;
                    uint8_t quad1 = 1;
                    uint8_t quad2 = 2;
                    uint8_t quad3 = 3;

                    if (flipped_diagonally)
                    {
                        std::swap(quad0, quad2);
                    }
                    if (flipped_horizontally)
                    {
                        std::swap(quad0, quad1);
                        std::swap(quad2, quad3);
                    }
                    if (flipped_vertically)
                    {
                        std::swap(quad0, quad3);
                        std::swap(quad1, quad2);
                    }

                    quad[0].position = sf::Vector2f(x * tileWidth, y * tileHeight);
                    quad[1].position = sf::Vector2f((x + 1) * tileWidth, y * tileHeight);
                    quad[2].position
                        = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
                    quad[3].position = sf::Vector2f(x * tileWidth, (y + 1) * tileHeight);

                    quad[quad0].texCoords
                        = sf::Vector2f(textureX * tileWidth, textureY * tileHeight);
                    quad[quad1].texCoords
                        = sf::Vector2f((textureX + 1) * tileWidth, textureY * tileHeight);
                    quad[quad2].texCoords = sf::Vector2f(
                        (textureX + 1) * tileWidth, (textureY + 1) * tileHeight);
                    quad[quad3].texCoords
                        = sf::Vector2f(textureX * tileWidth, (textureY + 1) * tileHeight);

                    quadCounters[firstTileId]++;
                }
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
        if (x > m_width || y > m_height)
        {
            throw Exceptions::TilePositionOutsideLayer(x, y, m_width, m_height, EXC_INFO);
        }
        m_data[x + y * m_width] = tileId;
        this->build(); // TODO: Optimize this
    }

    uint32_t TileLayer::getTile(uint32_t x, uint32_t y)
    {
        return m_data[x + y * m_width];
    }
}
