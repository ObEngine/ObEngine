#pragma once

#include <Graphics/RenderTarget.hpp>
#include <Scene/Camera.hpp>
#include <Tiles/Animation.hpp>
#include <Tiles/Layer.hpp>
#include <Tiles/Tileset.hpp>
#include <Types/Serializable.hpp>
#include <cstdint>
#include <memory>
#include <vector>
#include <vili/node.hpp>

namespace obe::scene
{
    class Scene;
}

/**
 * \additionalinclude{Scene/Scene.hpp}
 */
namespace obe::tiles
{
    class TileScene : public types::Serializable
    {
    private:
        scene::Scene& m_scene;

        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_tile_width;
        uint32_t m_tile_height;
        bool m_smooth = false;

        std::vector<std::unique_ptr<TileLayer>> m_layers;
        std::vector<std::unique_ptr<AnimatedTile>> m_animated_tiles;
        std::vector<std::unique_ptr<collision::PolygonalCollider>> m_collider_models;
        std::vector<vili::node> m_game_objects_models;
        TilesetCollection m_tilesets;

        void build();

    public:
        explicit TileScene(scene::Scene& scene);
        TileScene(const TileScene&) = delete;
        [[nodiscard]] vili::node schema() const override;
        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;

        void update() const;
        void clear();

        [[nodiscard]] std::vector<TileLayer*> get_all_layers() const;
        [[nodiscard]] std::vector<std::string> get_layers_ids() const;
        [[nodiscard]] TileLayer& get_layer(const std::string& id) const;
        [[nodiscard]] AnimatedTiles get_animated_tiles() const;
        [[nodiscard]] const TilesetCollection& get_tilesets() const;
        [[nodiscard]] std::vector<graphics::Renderable*> get_renderables() const;
        [[nodiscard]] std::vector<collision::PolygonalCollider*> get_collider_models() const;
        [[nodiscard]] const std::vector<vili::node>& get_game_objects_models() const;

        [[nodiscard]] uint32_t get_width() const;
        [[nodiscard]] uint32_t get_height() const;
        [[nodiscard]] uint32_t get_tile_width() const;
        [[nodiscard]] uint32_t get_tile_height() const;
        [[nodiscard]] bool is_anti_aliased() const;

        [[nodiscard]] scene::Scene& get_scene() const;
    };
} // namespace obe::tiles
