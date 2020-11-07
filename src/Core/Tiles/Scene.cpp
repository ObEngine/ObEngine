#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>

#include "Debug/Logger.hpp"

namespace obe::Tiles
{
    void TileScene::build()
    {
        Debug::Log->info("Build TileScene @{} with Animations @{}", fmt::ptr(this),
            fmt::ptr(&m_animatedTiles));
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

        const vili::node& tilesets = data["sources"];
        for (const auto& [tilesetId, tileset] : tilesets.items())
        {
            m_tilesets.addTileset(tileset["firstTileId"], tilesetId,
                tileset["image"]["path"], tileset["columns"], tileset["tile"]["width"],
                tileset["tile"]["height"], tileset["tilecount"]);

            if (tileset.contains("animations"))
            {
                for (const vili::node& animation : tileset.at("animations"))
                {
                    const Tileset& animationTileset = m_tilesets.tilesetFromId(tilesetId);
                    std::vector<Time::TimeUnit> sleeps;
                    std::vector<uint32_t> tileIds;
                    for (const vili::node& frame : animation.at("frames"))
                    {
                        const uint32_t sleepMilliseconds = frame.at("clock");
                        sleeps.push_back(
                            static_cast<double>(sleepMilliseconds) * Time::milliseconds);
                        tileIds.push_back(frame.at("tileid").as<vili::integer>()
                            + tileset.at("firstTileId").as<vili::integer>());
                    }
                    m_animatedTiles.push_back(std::make_unique<AnimatedTile>(
                        animationTileset, tileIds, sleeps));
                }
            }
        }

        AnimatedTiles animations = this->getAnimatedTiles();

        const vili::node& layers = data["layers"];
        for (const auto& [layerId, layer] : layers.items())
        {
            std::vector<uint32_t> tiles;
            tiles.reserve(layer["tiles"].size());
            for (const uint32_t tile : layer["tiles"])
            {
                tiles.push_back(tile);
            }
            m_layers.push_back(std::make_unique<TileLayer>(m_tilesets, animations,
                layerId, layer["layer"], layer["x"], layer["y"], layer["width"],
                layer["height"], tiles));
        }

        this->build();

        for (auto& animation : m_animatedTiles)
        {
            animation->start();
        }
    }

    void TileScene::update()
    {
        for (auto& animation : m_animatedTiles)
        {
            animation->update();
        }
    }

    TileLayer& TileScene::getLayer(const std::string& id) const
    {
        for (const auto& layer : m_layers)
        {
            if (layer->getId() == id)
            {
                Debug::Log->info("GetLayer TileScene @{} with Animations @{}",
                    fmt::ptr(this), fmt::ptr(&m_animatedTiles));
                return *layer;
            }
        }
    }

    AnimatedTiles TileScene::getAnimatedTiles() const
    {
        AnimatedTiles animations;
        for (const auto& animation : m_animatedTiles)
        {
            animations.push_back(animation.get());
        }
        return animations;
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
