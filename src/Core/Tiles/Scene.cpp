#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>

namespace obe::Tiles
{
    void TileScene::build()
    {
        for (auto& layer : m_layers)
        {
            layer->build();
        }
    }

    vili::node TileScene::dump() const
    {
        return vili::object {};
    }

    void TileScene::load(const vili::node& data)
    {
        m_width = data["width"];
        m_height = data["height"];
        m_tileWidth = data["tileWidth"];
        m_tileHeight = data["tileHeight"];
        const vili::node& layers = data["layers"];
        for (const auto& [layerId, layer] : layers.items())
        {
            std::vector<uint32_t> tiles;
            tiles.reserve(layer["tiles"].size());
            for (const uint32_t tile : layer["tiles"])
            {
                tiles.push_back(tile);
            }
            m_layers.push_back(
                std::make_unique<TileLayer>(m_tilesets, layerId, layer["layer"],
                    layer["x"], layer["y"], layer["width"], layer["height"], tiles));
        }
        const vili::node& tilesets = data["sources"];
        for (const auto& [tilesetId, tileset] : tilesets.items())
        {
            m_tilesets.addTileset(tileset["firstTileId"], tilesetId,
                tileset["image"]["path"], tileset["columns"], tileset["tile"]["width"],
                tileset["tile"]["height"], tileset["tilecount"]);
        }
        this->build();
    }

    TileLayer& TileScene::getLayer(const std::string& id) const
    {
        for (const auto& layer : m_layers)
        {
            if (layer->getId() == id)
            {
                return *layer;
            }
        }
    }

    std::vector<Graphics::Renderable*> TileScene::getRenderables() const
    {
        std::vector<Graphics::Renderable*> result;
        for (const auto& layer : m_layers)
        {
            result.push_back(layer.get());
        }
        return result;
    }
}
