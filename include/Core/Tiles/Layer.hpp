#pragma once

#include <Collision/PolygonalCollider.hpp>
#include <Graphics/Renderable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <string>
#include <vector>

namespace obe::tiles
{
    class TileScene;

    class TileLayer : public graphics::Renderable
    {
    private:
        std::unordered_map<uint32_t, sf::Vertex*> m_positions;
        std::unordered_map<uint32_t, sf::VertexArray> m_cache;
        const TileScene& m_scene;
        std::unordered_map<uint32_t, collision::PolygonalCollider*> m_colliders;

        std::string m_id;
        uint32_t m_x;
        uint32_t m_y;
        uint32_t m_width;
        uint32_t m_height;
        double m_opacity = 1.0;
        std::vector<uint32_t> m_data;

        void build_tile(uint32_t x, uint32_t y, uint32_t tile_id);
        void clear_tile(uint32_t x, uint32_t y);
        void update_quad(sf::Vertex* quad, uint32_t tile_id) const;
        static void clear_quad(sf::Vertex* quad);

    public:
        TileLayer(const TileScene& scene, const std::string& id, int32_t layer, uint32_t x,
            uint32_t y, uint32_t width, uint32_t height, std::vector<uint32_t> data);

        [[nodiscard]] std::string get_id() const;

        void build();
        /**
         * \brief Draws all elements of the TileLayer on the screen
         */
        void draw(graphics::RenderTarget& surface, const scene::Camera& camera) override;

        void set_tile(uint32_t x, uint32_t y, uint32_t tile_id);
        uint32_t get_tile(uint32_t x, uint32_t y) const;
    };
} // namespace obe::tiles
