#pragma once

#include <cstdint>

namespace obe::Tiles
{
    struct TileInfo
    {
        bool flippedHorizontally = false;
        bool flippedVertically = false;
        bool flippedDiagonally = false;
        uint32_t tileId = 0;
    };

    TileInfo getTileInfo(uint32_t tileId);
    uint32_t stripTileFlags(uint32_t tileId);

    struct TextureQuadsIndex
    {
        uint8_t q0 = 0;
        uint8_t q1 = 1;
        uint8_t q2 = 2;
        uint8_t q3 = 3;

        void transform(const TileInfo& info);
    };

    void applyTextureQuadsTransforms(const TileInfo& info, TextureQuadsIndex& quads);
}
