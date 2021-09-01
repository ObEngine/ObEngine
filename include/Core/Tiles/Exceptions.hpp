#pragma once

#include <Exception.hpp>
#include <map>
#include <vector>

namespace obe::Tiles::Exceptions
{
    class UnknownTileId : public Exception
    {
    public:
        UnknownTileId(uint32_t tileId, uint32_t maxTileId,
            std::map<std::string, std::pair<uint32_t, uint32_t>> tilesets, DebugInfo info)
            : Exception("UnknownTileId", info)
        {
            this->error(
                "Impossible to load tile with id '{}' when maximum tile id is '{}'",
                tileId, maxTileId);
            std::string hintMsg = "The following tilesets are loaded :\n";
            std::string tilesetHintList;
            for (const auto& [tilesetId, minMaxId] : tilesets)
            {
                tilesetHintList += fmt::format("    - {} [min_id={}, max_id={}]\n",
                    tilesetId, minMaxId.first, minMaxId.second);
            }
            hintMsg += tilesetHintList;
            this->hint(hintMsg);
        }
    };

    class UnknownTileset : public Exception
    {
    public:
        UnknownTileset(const std::string& tilesetId,
            const std::vector<std::string>& tilesetsIds, DebugInfo info)
            : Exception("UnknownTileset", info)
        {
            this->error("Impossible to find Tileset with id '{}'", tilesetId);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(tilesetId.data(), tilesetsIds, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Maybe you meant one of these tilesets : ({})",
                fmt::join(suggestions, ", "));
        }
    };

    class TilePositionOutsideLayer : public Exception
    {
    public:
        TilePositionOutsideLayer(
            uint32_t x, uint32_t y, uint32_t width, uint32_t height, DebugInfo info)
            : Exception("TilePositionOutsideLayer", info)
        {
            this->error("Impossible to access Tile with position [x={}, y={}] which is "
                        "outside of Layer with size [width={}, height={}]",
                x, y, width, height);
        }
    };

    class UnknownTileLayer : public Exception
    {
    public:
        UnknownTileLayer(const std::string& layerId,
            const std::vector<std::string>& layerIds, DebugInfo info)
            : Exception("UnknownTileLayer", info)
        {
            this->error("Impossible to find Tile Layer with id '{}'", layerId);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(layerId.data(), layerIds, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Maybe you meant one of these layers : ({})",
                fmt::join(suggestions, ", "));
        }
    };
}