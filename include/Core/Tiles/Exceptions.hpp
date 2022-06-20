#pragma once

#include <Exception.hpp>
#include <map>
#include <vector>

namespace obe::tiles::exceptions
{
    class UnknownTileId : public Exception<UnknownTileId>
    {
    public:
        using Exception::Exception;
        UnknownTileId(uint32_t tile_id, uint32_t max_tile_id,
            std::map<std::string, std::pair<uint32_t, uint32_t>> tilesets, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to load tile with id '{}' when maximum tile id is '{}'", tile_id,
                max_tile_id);
            std::string hint_msg = "The following tilesets are loaded :\n";
            std::string tileset_hint_list;
            for (const auto& [tileset_id, min_max_id] : tilesets)
            {
                tileset_hint_list += fmt::format("    - {} [min_id={}, max_id={}]\n", tileset_id,
                    min_max_id.first, min_max_id.second);
            }
            hint_msg += tileset_hint_list;
            this->hint(hint_msg);
        }
    };

    class UnknownTileset : public Exception<UnknownTileset>
    {
    public:
        using Exception::Exception;
        UnknownTileset(const std::string& tileset_id, const std::vector<std::string>& tilesets_ids,
            DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to find Tileset with id '{}'", tileset_id);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(tileset_id, tilesets_ids, 5);
            std::ranges::transform(suggestions, suggestions.begin(), utils::string::quote);
            this->hint(
                "Maybe you meant one of these tilesets : ({})", fmt::join(suggestions, ", "));
        }
    };

    class TilePositionOutsideLayer : public Exception<TilePositionOutsideLayer>
    {
    public:
        using Exception::Exception;
        TilePositionOutsideLayer(
            uint32_t x, uint32_t y, uint32_t width, uint32_t height, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to access Tile with position [x={}, y={}] which is "
                        "outside of Layer with size [width={}, height={}]",
                x, y, width, height);
        }
    };

    class UnknownTileLayer : public Exception<UnknownTileLayer>
    {
    public:
        using Exception::Exception;
        UnknownTileLayer(
            const std::string& layer_id, const std::vector<std::string>& layer_ids, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to find Tile Layer with id '{}'", layer_id);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(layer_id, layer_ids, 5);
            std::ranges::transform(suggestions
                , suggestions.begin(), utils::string::quote);
            this->hint("Maybe you meant one of these layers : ({})", fmt::join(suggestions, ", "));
        }
    };
}
