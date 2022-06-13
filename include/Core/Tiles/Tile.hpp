#pragma once

#include <cstdint>

namespace obe::tiles
{
    struct TileInfo
    {
        bool flip_horizontal = false;
        bool flip_vertical = false;
        bool flip_diagonal = false;
        uint32_t tile_id = 0;
    };

    TileInfo get_tile_info(uint32_t tile_id);
    uint32_t strip_tile_flags(uint32_t tile_id);

    struct TextureQuadsIndex
    {
        uint8_t q0 = 0;
        uint8_t q1 = 1;
        uint8_t q2 = 2;
        uint8_t q3 = 3;

        void transform(const TileInfo& info);
    };

    void apply_texture_quads_transforms(const TileInfo& info, TextureQuadsIndex& quads);
}
