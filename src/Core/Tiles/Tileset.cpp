#include <Tiles/Exceptions.hpp>
#include <Tiles/Tileset.hpp>

namespace obe::Tiles
{
    Tileset::Tileset(const std::string& id, const std::string& imagePath,
        uint32_t columns, uint32_t tileWidth, uint32_t tileHeight, uint32_t margin,
        uint32_t spacing)
        : Identifiable(id)
    {
        m_imagePath = imagePath;
        m_columns = columns;
        m_tileWidth = tileWidth;
        m_tileHeight = tileHeight;
        m_margin = margin;
        m_spacing = spacing;

        m_image.loadFromFile(m_imagePath);
        m_imageWidth = m_image.getSize().to<Transform::Units::ScenePixels>().x;
        m_imageHeight = m_image.getSize().to<Transform::Units::ScenePixels>().y;
    }

    uint32_t Tileset::getFirstTileId() const
    {
        return m_firstTileId;
    }

    uint32_t Tileset::getLastTileId() const
    {
        return m_firstTileId + m_count - 1;
    }

    uint32_t Tileset::getTileCount() const
    {
        return m_count;
    }

    uint32_t Tileset::getMargin() const
    {
        return m_margin;
    }

    uint32_t Tileset::getSpacing() const
    {
        return m_spacing;
    }

    uint32_t Tileset::getTileWidth() const
    {
        return m_tileWidth;
    }

    uint32_t Tileset::getTileHeight() const
    {
        return m_tileHeight;
    }

    uint32_t Tileset::getImageWidth() const
    {
        return m_imageWidth;
    }

    uint32_t Tileset::getImageHeight() const
    {
        return m_imageHeight;
    }

    std::string Tileset::getImagePath() const
    {
        return m_imagePath;
    }

    Graphics::Texture Tileset::getTexture() const
    {
        return m_image;
    }

    TileLayer::TileLayer(const std::string& id, uint32_t x, uint32_t y, uint32_t width,
        uint32_t height, const std::vector<uint32_t>& data)
        : id(id)
        , x(x)
        , y(y)
        , width(width)
        , height(height)
        , data(data)
    {
    }

    void TileScene::buildCache()
    {
        m_cache.clear();
        for (const auto& layer : m_layers)
        {
            m_cache.push_back(buildLayer(*layer));
        }
    }

    sf::VertexArray TileScene::buildLayer(const TileLayer& layer)
    {
        sf::VertexArray vertices;
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(layer.width * layer.height * 4);

        for (unsigned int x = 0; x < layer.width; ++x)
        {
            for (unsigned int y = 0; y < layer.height; ++y)
            {
                const uint32_t tileId = layer.data[x + y * layer.width];
                sf::Vertex* quad = &vertices[(x + y * layer.width) * 4];
                if (tileId)
                {
                    const Tileset& tileset = this->tilesetFromTileId(tileId);

                    const uint32_t tileWidth = tileset.getTileWidth();
                    const uint32_t tileHeight = tileset.getTileHeight();

                    const int textureX
                        = (tileId - 1) % (tileset.getImageWidth() / tileWidth);
                    const int textureY
                        = (tileId - 1) / (tileset.getImageWidth() / tileWidth);

                    quad[0].position = sf::Vector2f(x * tileWidth, y * tileHeight);
                    quad[1].position = sf::Vector2f((x + 1) * tileWidth, y * tileHeight);
                    quad[2].position
                        = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
                    quad[3].position = sf::Vector2f(x * tileWidth, (y + 1) * tileHeight);

                    quad[0].texCoords
                        = sf::Vector2f(textureX * tileWidth, textureY * tileHeight);
                    quad[1].texCoords
                        = sf::Vector2f((textureX + 1) * tileWidth, textureY * tileHeight);
                    quad[2].texCoords = sf::Vector2f(
                        (textureX + 1) * tileWidth, (textureY + 1) * tileHeight);
                    quad[3].texCoords
                        = sf::Vector2f(textureX * tileWidth, (textureY + 1) * tileHeight);
                }
                else
                {
                    quad[0].position = sf::Vector2f(x * m_tileWidth, y * m_tileHeight);
                    quad[1].position
                        = sf::Vector2f((x + 1) * m_tileWidth, y * m_tileHeight);
                    quad[2].position
                        = sf::Vector2f((x + 1) * m_tileWidth, (y + 1) * m_tileHeight);
                    quad[3].position
                        = sf::Vector2f(x * m_tileWidth, (y + 1) * m_tileHeight);

                    quad[0].color = sf::Color::Transparent;
                    quad[1].color = sf::Color::Transparent;
                    quad[2].color = sf::Color::Transparent;
                    quad[3].color = sf::Color::Transparent;
                }
            }
        }
        return vertices;
    }

    Tileset& TileScene::tilesetFromTileId(uint32_t tileId) const
    {
        Tileset* lastTileset = nullptr;
        for (const auto& [key, value] : m_tilesets)
        {
            if (tileId > key)
            {
                return *value;
            }
            lastTileset = value.get();
        }
        uint32_t maxTileId = 0;
        if (lastTileset)
        {
            maxTileId = lastTileset->getLastTileId();
        }
        std::map<std::string, std::pair<uint32_t, uint32_t>> tilesetIds;
        for (const auto& [key, value] : m_tilesets)
        {
            tilesetIds[value->getId()]
                = std::make_pair(value->getFirstTileId(), value->getLastTileId());
        }
        throw Exceptions::UnknownTileId(tileId, maxTileId, tilesetIds, EXC_INFO);
    }

    vili::node TileScene::dump() const
    {
        return vili::object {};
    }

    void TileScene::load(const vili::node& data)
    {
        m_tileWidth = data["tileWidth"];
        m_tileHeight = data["tileHeight"];
        const vili::node& layers = data["layers"];
        for (const auto& [layerId, layer] : layers.items())
        {
            std::vector<uint32_t> tiles;
            tiles.reserve(layer["tiles"].size());
            for (const uint32_t tile : layer["tiles"])
            {
                tiles.push_back(tile);
            }
            m_layers.push_back(std::make_unique<TileLayer>(
                layerId, layer["x"], layer["y"], layer["width"], layer["height"], tiles));
        }
        const vili::node& tilesets = data["sources"];
        for (const auto& [tilesetId, tileset] : tilesets.items())
        {
            m_tilesets[tileset["firstTileId"]] = std::make_unique<Tileset>(tilesetId,
                tileset["image"]["path"], tileset["columns"], tileset["tile"]["width"],
                tileset["tile"]["height"]);
        }
        this->buildCache();
    }

    void TileScene::draw(Graphics::RenderTarget surface, const Scene::Camera& camera)
    {
        sf::RenderStates states;

        for (const auto& layer : m_cache)
        {
            states.transform = sf::Transform::Identity;

            const Transform::UnitVector pixelCamera
                = camera.getPosition().to<Transform::Units::ScenePixels>();
            states.transform.translate(-pixelCamera.x, -pixelCamera.y);
            const Transform::UnitVector cameraSize = camera.getSize();
            states.transform.scale(cameraSize.y / 2, cameraSize.y / 2);

            states.texture = &m_tilesets.begin()->second->getTexture().
                              operator const sf::Texture &();

            surface.draw(layer, states);
        }
    }
}
