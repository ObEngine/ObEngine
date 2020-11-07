#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <vili/node.hpp>

#include <Graphics/RenderTarget.hpp>
#include <Scene/Camera.hpp>
#include <Tiles/Animation.hpp>
#include <Tiles/Layer.hpp>
#include <Tiles/Tileset.hpp>
#include <Types/Serializable.hpp>

namespace obe::Tiles
{
    class TileScene : public Types::Serializable
    {
    private:
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_tileWidth;
        uint32_t m_tileHeight;

        std::vector<std::unique_ptr<TileLayer>> m_layers;
        std::vector<std::unique_ptr<AnimatedTile>> m_animatedTiles;
        TilesetCollection m_tilesets;

        void build();

    public:
        vili::node dump() const;
        void load(const vili::node& data) override;

        void update();

        TileLayer& getLayer(const std::string& id) const;
        AnimatedTiles getAnimatedTiles() const;
        std::vector<Graphics::Renderable*> getRenderables() const;
    };
}
