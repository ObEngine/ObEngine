#include <tuple>

#include <Tiles/Tile.hpp>

namespace obe::tiles
{
    constexpr unsigned FLIP_HORIZONTAL_FLAG = 0x80000000;
    constexpr unsigned FLIP_VERTICAL_FLAG = 0x40000000;
    constexpr unsigned FLIP_DIAGONAL_FLAG = 0x20000000;

    TileInfo get_tile_info(uint32_t tile_id)
    {
        TileInfo info;
        info.flip_horizontal = (tile_id & FLIP_HORIZONTAL_FLAG);
        info.flip_vertical = (tile_id & FLIP_VERTICAL_FLAG);
        info.flip_diagonal = (tile_id & FLIP_DIAGONAL_FLAG);

        info.tile_id = strip_tile_flags(tile_id);

        return info;
    }

    uint32_t strip_tile_flags(uint32_t tile_id)
    {
        return tile_id & ~(FLIP_HORIZONTAL_FLAG | FLIP_VERTICAL_FLAG | FLIP_DIAGONAL_FLAG);
    }

    void TextureQuadsIndex::transform(const TileInfo& info)
    {
        if (info.flip_diagonal)
        {
            std::swap(q0, q2);
        }
        if (info.flip_horizontal)
        {
            std::swap(q0, q1);
            std::swap(q2, q3);
        }
        if (info.flip_vertical)
        {
            std::swap(q0, q3);
            std::swap(q1, q2);
        }
    }

    void apply_texture_quads_transforms(const TileInfo& info, TextureQuadsIndex& quads)
    {
        if (info.flip_diagonal)
        {
            std::swap(quads.q0, quads.q2);
        }
        if (info.flip_horizontal)
        {
            std::swap(quads.q0, quads.q1);
            std::swap(quads.q2, quads.q3);
        }
        if (info.flip_vertical)
        {
            std::swap(quads.q0, quads.q3);
            std::swap(quads.q1, quads.q2);
        }
    }
}
