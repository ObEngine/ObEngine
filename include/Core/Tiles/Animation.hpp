#pragma once

#include <Tiles/Tile.hpp>
#include <Tiles/Tileset.hpp>
#include <Time/TimeUtils.hpp>
#include <vector>

namespace obe::tiles
{
    class TileLayer;

    class AnimatedTile
    {
    private:
        const Tileset& m_tileset;
        std::vector<std::pair<sf::Vertex*, TileInfo>> m_quads;
        size_t m_index = 0;
        time::TimeUnit m_clock;
        std::vector<time::TimeUnit> m_sleeps;
        std::vector<uint32_t> m_tile_ids;
        bool m_started = false;

    public:
        AnimatedTile(const Tileset& tileset, std::vector<uint32_t> tile_ids,
            std::vector<time::TimeUnit> sleeps);
        void attach_quad(sf::Vertex* quad, TileInfo tile_info = TileInfo {});
        void detach_quad(sf::Vertex* quad);
        void start();
        void stop();
        [[nodiscard]] uint32_t get_id() const;
        void update();
    };

    using AnimatedTiles = std::vector<AnimatedTile*>;
} // namespace obe::tiles
