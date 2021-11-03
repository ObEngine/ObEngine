#pragma once

#include <vector>

#include <Tiles/Tile.hpp>
#include <Tiles/Tileset.hpp>
#include <Time/TimeUtils.hpp>

namespace obe::Tiles
{
    class TileLayer;

    class AnimatedTile
    {
    private:
        const Tileset& m_tileset;
        std::vector<std::pair<sf::Vertex*, TileInfo>> m_quads;
        size_t m_index = 0;
        Time::TimeUnit m_clock;
        std::vector<Time::TimeUnit> m_sleeps;
        std::vector<uint32_t> m_tileIds;
        bool m_started = false;

    public:
        AnimatedTile(const Tileset& tileset, std::vector<uint32_t> tileIds,
            std::vector<Time::TimeUnit> sleeps);
        void attachQuad(sf::Vertex* quad, TileInfo tileInfo = TileInfo {});
        void dettachQuad(sf::Vertex* quad);
        void start();
        void stop();
        [[nodiscard]] uint32_t getId() const;
        void update();
    };

    using AnimatedTiles = std::vector<AnimatedTile*>;
}
