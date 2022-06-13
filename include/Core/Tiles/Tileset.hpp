#pragma once

#include <Graphics/Texture.hpp>
#include <Types/Identifiable.hpp>

namespace obe::tiles
{
    class Tileset : public Types::Identifiable
    {
    private:
        uint32_t m_first_tile_id;
        uint32_t m_columns;
        uint32_t m_count;
        uint32_t m_margin;
        uint32_t m_spacing;
        uint32_t m_tile_width;
        uint32_t m_tile_height;
        uint32_t m_image_width;
        uint32_t m_image_height;
        std::string m_image_path;
        graphics::Texture m_image;

    public:
        Tileset(const std::string& id, uint32_t first_tile_id, uint32_t count,
            const std::string& image_path, uint32_t columns, uint32_t tile_width, uint32_t tile_height,
            uint32_t margin = 0, uint32_t spacing = 0);
        uint32_t get_first_tile_id() const;
        uint32_t get_last_tile_id() const;
        uint32_t get_tile_count() const;
        uint32_t get_margin() const;
        uint32_t get_spacing() const;
        uint32_t get_tile_width() const;
        uint32_t get_tile_height() const;
        uint32_t get_image_width() const;
        uint32_t get_image_height() const;
        std::string get_image_path() const;
        graphics::Texture get_texture() const;
    };

    class TilesetCollection
    {
    private:
        std::vector<std::unique_ptr<Tileset>> m_tilesets;

    public:
        TilesetCollection() = default;
        TilesetCollection(const TilesetCollection&) = delete;
        void add_tileset(uint32_t first_tile_id, const std::string& id, const std::string& source,
            uint32_t columns, uint32_t width, uint32_t height, uint32_t count);
        [[nodiscard]] const Tileset& tileset_from_id(const std::string& id) const;
        [[nodiscard]] const Tileset& tileset_from_tile_id(uint32_t tile_id) const;
        [[nodiscard]] size_t size() const;
        [[nodiscard]] std::vector<uint32_t> get_tilesets_first_tiles_ids() const;
        void clear();
    };
} // namespace obe::scene
