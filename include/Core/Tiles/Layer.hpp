#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include <Graphics/RenderTarget.hpp>
#include <Graphics/Renderable.hpp>
#include <Scene/Camera.hpp>
#include <Tiles/Animation.hpp>
#include <Tiles/Tile.hpp>
#include <Tiles/Tileset.hpp>

namespace obe::Tiles
{
    struct TextureQuadsIndex
    {
        uint8_t q0 = 0;
        uint8_t q1 = 1;
        uint8_t q2 = 2;
        uint8_t q3 = 3;

        void transform(const TileInfo& info);
    };

    class TileLayer : public Graphics::Renderable
    {
    private:
        std::unordered_map<uint32_t, sf::Vertex*> m_positions;
        std::unordered_map<uint32_t, sf::VertexArray> m_cache;
        const TilesetCollection& m_tilesets;
        const AnimatedTiles m_animations;

        std::string m_id;
        uint32_t m_x;
        uint32_t m_y;
        uint32_t m_width;
        uint32_t m_height;
        bool m_visible = true;
        double m_opacity = 1.0;
        std::vector<uint32_t> m_data;

        void buildTile(uint32_t x, uint32_t y, uint32_t tileId);
        void updateQuad(sf::Vertex* quad, uint32_t tileId) const;

    public:
        TileLayer(const TilesetCollection& tilesets, const AnimatedTiles animations,
            const std::string& id, int32_t layer, uint32_t x, uint32_t y, uint32_t width,
            uint32_t height, const std::vector<uint32_t>& data);

        [[nodiscard]] std::string getId() const;

        void build();
        /**
         * \brief Draws all elements of the TileLayer on the screen
         */
        void draw(Graphics::RenderTarget& surface, const Scene::Camera& camera) override;

        void setTile(uint32_t x, uint32_t y, uint32_t tileId);
        uint32_t getTile(uint32_t x, uint32_t y);
    };
}
