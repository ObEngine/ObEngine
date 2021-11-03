#include <tuple>

#include <Tiles/Tile.hpp>

namespace obe::Tiles
{
    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    TileInfo getTileInfo(uint32_t tileId)
    {
        TileInfo info;
        info.flippedHorizontally = (tileId & FLIPPED_HORIZONTALLY_FLAG);
        info.flippedVertically = (tileId & FLIPPED_VERTICALLY_FLAG);
        info.flippedDiagonally = (tileId & FLIPPED_DIAGONALLY_FLAG);

        info.tileId = stripTileFlags(tileId);

        return info;
    }

    uint32_t stripTileFlags(uint32_t tileId)
    {
        return tileId
            & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
    }

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
}
