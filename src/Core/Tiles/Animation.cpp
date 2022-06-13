#include <utility>

#include <Tiles/Animation.hpp>

namespace obe::tiles
{
    void update_quad(
        sf::Vertex* quad, const Tileset& tileset, uint32_t tile_id, TileInfo additional_tile_info)
    {
        if (!tile_id)
            return;

        TileInfo tile_info = get_tile_info(tile_id);
        tile_info.flip_diagonal
            = tile_info.flip_diagonal ^ additional_tile_info.flip_diagonal;
        tile_info.flip_horizontal
            = tile_info.flip_horizontal ^ additional_tile_info.flip_horizontal;
        tile_info.flip_vertical
            = tile_info.flip_vertical ^ additional_tile_info.flip_vertical;

        const uint32_t first_tile_id = tileset.get_first_tile_id();

        const uint32_t tile_width = tileset.get_tile_width();
        const uint32_t tile_height = tileset.get_tile_height();

        const int texture_x = (tile_id - first_tile_id) % (tileset.get_image_width() / tile_width);
        const int texture_y = (tile_id - first_tile_id) / (tileset.get_image_width() / tile_width);

        TextureQuadsIndex quads;
        quads.transform(tile_info);

        quad[quads.q0].texCoords = sf::Vector2f(texture_x * tile_width, texture_y * tile_height);
        quad[quads.q1].texCoords = sf::Vector2f((texture_x + 1) * tile_width, texture_y * tile_height);
        quad[quads.q2].texCoords
            = sf::Vector2f((texture_x + 1) * tile_width, (texture_y + 1) * tile_height);
        quad[quads.q3].texCoords = sf::Vector2f(texture_x * tile_width, (texture_y + 1) * tile_height);
    }

    AnimatedTile::AnimatedTile(
        const Tileset& tileset, std::vector<uint32_t> tile_ids, std::vector<time::TimeUnit> sleeps)
        : m_tileset(tileset)
        , m_tile_ids(std::move(tile_ids))
        , m_sleeps(std::move(sleeps))
    {
    }

    void AnimatedTile::attach_quad(sf::Vertex* quad, TileInfo tile_info)
    {
        m_quads.emplace_back(quad, tile_info);
    }

    void AnimatedTile::detach_quad(sf::Vertex* quad)
    {
        std::erase_if(m_quads,
            [&quad](const std::pair<sf::Vertex*, TileInfo>& item)
            { return item.first == quad; });
    }

    void AnimatedTile::start()
    {
        m_started = true;
        m_clock = time::epoch();
    }

    void AnimatedTile::stop()
    {
        m_started = false;
    }

    uint32_t AnimatedTile::get_id() const
    {
        return m_tile_ids[0];
    }

    void AnimatedTile::update()
    {
        if (m_started && time::epoch() - m_clock >= m_sleeps[m_index])
        {
            m_index++;
            if (m_index == m_sleeps.size())
            {
                m_index = 0;
            }
            m_clock = time::epoch();
            for (const auto& quad : m_quads)
            {
                update_quad(quad.first, m_tileset, m_tile_ids[m_index], quad.second);
            }
        }
    }
}
