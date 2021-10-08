#include <utility>

#include <Tiles/Animation.hpp>

namespace obe::Tiles
{
    void updateQuad(
        sf::Vertex* quad, const Tileset& tileset, uint32_t tileId, TileInfo additionalTileInfo)
    {
        if (!tileId)
            return;

        TileInfo tileInfo = getTileInfo(tileId);
        tileInfo.flippedDiagonally
            = tileInfo.flippedDiagonally ^ additionalTileInfo.flippedDiagonally;
        tileInfo.flippedHorizontally
            = tileInfo.flippedHorizontally ^ additionalTileInfo.flippedHorizontally;
        tileInfo.flippedVertically
            = tileInfo.flippedVertically ^ additionalTileInfo.flippedVertically;

        const uint32_t firstTileId = tileset.getFirstTileId();

        const uint32_t tileWidth = tileset.getTileWidth();
        const uint32_t tileHeight = tileset.getTileHeight();

        const int textureX = (tileId - firstTileId) % (tileset.getImageWidth() / tileWidth);
        const int textureY = (tileId - firstTileId) / (tileset.getImageWidth() / tileWidth);

        TextureQuadsIndex quads;
        quads.transform(tileInfo);

        quad[quads.q0].texCoords = sf::Vector2f(textureX * tileWidth, textureY * tileHeight);
        quad[quads.q1].texCoords = sf::Vector2f((textureX + 1) * tileWidth, textureY * tileHeight);
        quad[quads.q2].texCoords
            = sf::Vector2f((textureX + 1) * tileWidth, (textureY + 1) * tileHeight);
        quad[quads.q3].texCoords = sf::Vector2f(textureX * tileWidth, (textureY + 1) * tileHeight);
    }

    AnimatedTile::AnimatedTile(
        const Tileset& tileset, std::vector<uint32_t> tileIds, std::vector<Time::TimeUnit> sleeps)
        : m_tileset(tileset)
        , m_tileIds(std::move(tileIds))
        , m_sleeps(std::move(sleeps))
    {
    }

    void AnimatedTile::attachQuad(sf::Vertex* quad, TileInfo tileInfo)
    {
        m_quads.emplace_back(quad, tileInfo);
    }

    void AnimatedTile::dettachQuad(sf::Vertex* quad)
    {
        m_quads.erase(std::remove_if(m_quads.begin(), m_quads.end(),
                          [&quad](const std::pair<sf::Vertex*, TileInfo>& item)
                          { return item.first == quad; }),
            m_quads.end());
    }

    void AnimatedTile::start()
    {
        m_started = true;
        m_clock = Time::epoch();
    }

    void AnimatedTile::stop()
    {
        m_started = false;
    }

    uint32_t AnimatedTile::getId() const
    {
        return m_tileIds[0];
    }

    void AnimatedTile::update()
    {
        if (m_started && Time::epoch() - m_clock >= m_sleeps[m_index])
        {
            m_index++;
            if (m_index == m_sleeps.size())
            {
                m_index = 0;
            }
            m_clock = Time::epoch();
            for (auto& quad : m_quads)
            {
                updateQuad(quad.first, m_tileset, m_tileIds[m_index], quad.second);
            }
        }
    }
}
