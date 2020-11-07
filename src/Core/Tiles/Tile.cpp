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
            & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG
                | FLIPPED_DIAGONALLY_FLAG);
    }
}
