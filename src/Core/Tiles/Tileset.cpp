#include <System/Path.hpp>
#include <Tiles/Exceptions.hpp>
#include <Tiles/Tileset.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Units.hpp>

namespace obe::tiles
{
    Tileset::Tileset(const std::string& id, uint32_t first_tile_id, uint32_t tile_count,
        const std::string& image_path, uint32_t columns, uint32_t tile_width, uint32_t tile_height,
        uint32_t margin, uint32_t spacing)
        : Identifiable(id)
        , m_first_tile_id(first_tile_id)
        , m_columns(columns)
        , m_count(tile_count)
        , m_margin(margin)
        , m_spacing(spacing)
        , m_tile_width(tile_width)
        , m_tile_height(tile_height)
        , m_image_path(image_path)
    {
        m_image.load_from_file(system::Path(m_image_path).find());
        // m_image.set_anti_aliasing(true);
        m_image_width = m_image.get_size().to<transform::Units::ScenePixels>().x;
        m_image_height = m_image.get_size().to<transform::Units::ScenePixels>().y;
    }

    uint32_t Tileset::get_first_tile_id() const
    {
        return m_first_tile_id;
    }

    uint32_t Tileset::get_last_tile_id() const
    {
        return m_first_tile_id + m_count - 1;
    }

    uint32_t Tileset::get_tile_count() const
    {
        return m_count;
    }

    uint32_t Tileset::get_margin() const
    {
        return m_margin;
    }

    uint32_t Tileset::get_spacing() const
    {
        return m_spacing;
    }

    uint32_t Tileset::get_tile_width() const
    {
        return m_tile_width;
    }

    uint32_t Tileset::get_tile_height() const
    {
        return m_tile_height;
    }

    uint32_t Tileset::get_image_width() const
    {
        return m_image_width;
    }

    uint32_t Tileset::get_image_height() const
    {
        return m_image_height;
    }

    std::string Tileset::get_image_path() const
    {
        return m_image_path;
    }

    graphics::Texture Tileset::get_texture() const
    {
        return m_image;
    }

    void TilesetCollection::add_tileset(uint32_t first_tile_id, const std::string& id,
        const std::string& source, uint32_t columns, uint32_t width, uint32_t height,
        uint32_t count)
    {
        m_tilesets.push_back(
            std::make_unique<Tileset>(id, first_tile_id, count, source, columns, width, height));
        std::sort(m_tilesets.begin(), m_tilesets.end(),
            [](const std::unique_ptr<Tileset>& tileset1, const std::unique_ptr<Tileset>& tileset2) {
                return tileset1->get_first_tile_id() > tileset2->get_first_tile_id();
            });
    }

    const Tileset& TilesetCollection::tileset_from_id(const std::string& id) const
    {
        for (const auto& tileset : m_tilesets)
        {
            if (tileset->get_id() == id)
            {
                return *tileset;
            }
        }
        std::vector<std::string> tilesets_ids;
        tilesets_ids.reserve(m_tilesets.size());
        for (const auto& tileset : m_tilesets)
        {
            tilesets_ids.push_back(tileset->get_id());
        }
        throw exceptions::UnknownTileset(id, tilesets_ids);
    }

    const Tileset& TilesetCollection::tileset_from_tile_id(uint32_t tile_id) const
    {
        Tileset* last_tileset = nullptr;
        for (const auto& tileset : m_tilesets)
        {
            if (tile_id >= tileset->get_first_tile_id())
            {
                return *tileset;
            }
            last_tileset = tileset.get();
        }
        uint32_t max_tile_id = 0;
        if (last_tileset)
        {
            max_tile_id = last_tileset->get_last_tile_id();
        }
        std::map<std::string, std::pair<uint32_t, uint32_t>> tileset_ids;
        for (const auto& tileset : m_tilesets)
        {
            tileset_ids[tileset->get_id()]
                = std::make_pair(tileset->get_first_tile_id(), tileset->get_last_tile_id());
        }
        throw exceptions::UnknownTileId(tile_id, max_tile_id, tileset_ids);
    }

    size_t TilesetCollection::size() const
    {
        return m_tilesets.size();
    }

    std::vector<uint32_t> TilesetCollection::get_tilesets_first_tiles_ids() const
    {
        std::vector<uint32_t> first_tiles_ids;
        for (const auto& tileset : m_tilesets)
        {
            first_tiles_ids.push_back(tileset->get_first_tile_id());
        }
        return first_tiles_ids;
    }

    void TilesetCollection::clear()
    {
        m_tilesets.clear();
    }
}
