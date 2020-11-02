#pragma once

#include <Exception.hpp>
#include <map>
#include <vector>

namespace obe::Tiles::Exceptions
{
    class UnknownTileId : public Exception
    {
    public:
        UnknownTileId(
            uint32_t tileId, uint32_t maxTileId, std::map<std::string, std::pair<uint32_t, uint32_t>> tilesets, DebugInfo info)
            : Exception("UnknownTileId", info)
        {
            this->error("Impossible to load tile with id '{}' when maximum tile id is '{}'", tileId, maxTileId);
            std::string hintMsg = "The following tilesets are loaded :\n";
            std::string tilesetHintList;
            for (const auto& [tilesetId, minMaxId] : tilesets)
            {
                tilesetHintList += fmt::format("    - {} [min_id={}, max_id={}]\n", tilesetId,
                    minMaxId.first, minMaxId.second);
            }
            hintMsg += tilesetHintList;
            this->hint(hintMsg);
        }
    };

}