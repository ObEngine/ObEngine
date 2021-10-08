#include <System/Path.hpp>
#include <Tiles/Exceptions.hpp>
#include <Tiles/Tileset.hpp>

namespace obe::Tiles
{
    Tileset::Tileset(const std::string& id, uint32_t firstTileId, uint32_t tileCount,
        const std::string& imagePath, uint32_t columns, uint32_t tileWidth, uint32_t tileHeight,
        uint32_t margin, uint32_t spacing)
        : Identifiable(id)
    {
        m_imagePath = imagePath;
        m_columns = columns;
        m_tileWidth = tileWidth;
        m_tileHeight = tileHeight;
        m_firstTileId = firstTileId;
        m_count = tileCount;
        m_margin = margin;
        m_spacing = spacing;

        m_image.loadFromFile(System::Path(m_imagePath).find());
        // m_image.setAntiAliasing(true);
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

    TilesetCollection::TilesetCollection()
    {
    }

    void TilesetCollection::addTileset(uint32_t firstTileId, const std::string& id,
        const std::string& source, uint32_t columns, uint32_t width, uint32_t height,
        uint32_t count)
    {
        m_tilesets.push_back(
            std::make_unique<Tileset>(id, firstTileId, count, source, columns, width, height));
        std::sort(m_tilesets.begin(), m_tilesets.end(),
            [](const std::unique_ptr<Tileset>& tileset1, const std::unique_ptr<Tileset>& tileset2)
            { return tileset1->getFirstTileId() > tileset2->getFirstTileId(); });
    }

    const Tileset& TilesetCollection::tilesetFromId(const std::string& id) const
    {
        for (const auto& tileset : m_tilesets)
        {
            if (tileset->getId() == id)
            {
                return *tileset;
            }
        }
        std::vector<std::string> tilesetsIds;
        tilesetsIds.reserve(m_tilesets.size());
        for (const auto& tileset : m_tilesets)
        {
            tilesetsIds.push_back(tileset->getId());
        }
        throw Exceptions::UnknownTileset(id, tilesetsIds, EXC_INFO);
    }

    const Tileset& TilesetCollection::tilesetFromTileId(uint32_t tileId) const
    {
        Tileset* lastTileset = nullptr;
        for (const auto& tileset : m_tilesets)
        {
            if (tileId >= tileset->getFirstTileId())
            {
                return *tileset;
            }
            lastTileset = tileset.get();
        }
        uint32_t maxTileId = 0;
        if (lastTileset)
        {
            maxTileId = lastTileset->getLastTileId();
        }
        std::map<std::string, std::pair<uint32_t, uint32_t>> tilesetIds;
        for (const auto& tileset : m_tilesets)
        {
            tilesetIds[tileset->getId()]
                = std::make_pair(tileset->getFirstTileId(), tileset->getLastTileId());
        }
        throw Exceptions::UnknownTileId(tileId, maxTileId, tilesetIds, EXC_INFO);
    }

    const size_t TilesetCollection::size() const
    {
        return m_tilesets.size();
    }

    std::vector<uint32_t> TilesetCollection::getTilesetsFirstTilesIds() const
    {
        std::vector<uint32_t> firstTilesIds;
        for (const auto& tileset : m_tilesets)
        {
            firstTilesIds.push_back(tileset->getFirstTileId());
        }
        return firstTilesIds;
    }

    void TilesetCollection::clear()
    {
        m_tilesets.clear();
    }
}
