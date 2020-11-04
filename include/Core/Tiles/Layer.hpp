#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include <Graphics/RenderTarget.hpp>
#include <Graphics/Renderable.hpp>
#include <Scene/Camera.hpp>
#include <Tiles/Tileset.hpp>

namespace obe::Tiles
{
    struct TilePosition
    {
        uint32_t x = 0;
        uint32_t y = 0;

        bool operator<(const TilePosition& position) const
        {
            return x == position.x && y == position.y;
        }
    };

    struct TilePositionHash
    {
        std::size_t operator()(const TilePosition& position) const
        {
            std::size_t h1 = std::hash<decltype(TilePosition::x)>()(position.x);
            std::size_t h2 = std::hash<decltype(TilePosition::y)>()(position.y);

            return h1 ^ h2;
        }
    };

    class TileLayer : public Graphics::Renderable
    {
    private:
        // std::unordered_map<TilePosition, sf::Vertex*, TilePositionHash> m_positions;
        std::unordered_map<uint32_t, sf::VertexArray> m_cache;
        const TilesetCollection& m_tilesets;

        std::string m_id;
        uint32_t m_x;
        uint32_t m_y;
        uint32_t m_width;
        uint32_t m_height;
        bool m_visible = true;
        double m_opacity = 1.0;
        std::vector<uint32_t> m_data;

    public:
        TileLayer(const TilesetCollection& tilesets, const std::string& id, int32_t layer,
            uint32_t x, uint32_t y, uint32_t width, uint32_t height,
            const std::vector<uint32_t>& data);

        std::string getId() const;

        void build();
        /**
         * \brief Draws all elements of the TileLayer on the screen
         */
        void draw(Graphics::RenderTarget& surface, const Scene::Camera& camera) override;

        void setTile(uint32_t x, uint32_t y, uint32_t tileId);
        uint32_t getTile(uint32_t x, uint32_t y);
    };
}
