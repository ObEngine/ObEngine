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

namespace obe::Scene
{
    class Scene;
}

/**
 * \additionalinclude{Scene/Scene.hpp}
 */
namespace obe::Tiles
{
    class TileScene : public Types::Serializable
    {
    private:
        Scene::Scene& m_scene;

        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_tileWidth;
        uint32_t m_tileHeight;
        bool m_smooth = false;

        std::vector<std::unique_ptr<TileLayer>> m_layers;
        std::vector<std::unique_ptr<AnimatedTile>> m_animatedTiles;
        std::vector<std::unique_ptr<collision::PolygonalCollider>> m_colliderModels;
        std::vector<vili::node> m_gameObjectsModels;
        TilesetCollection m_tilesets;

        void build();

    public:
        explicit TileScene(Scene::Scene& scene);
        TileScene(const TileScene&) = delete;
        [[nodiscard]] vili::node schema() const override;
        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;

        void update();
        void clear();

        [[nodiscard]] std::vector<TileLayer*> getAllLayers() const;
        [[nodiscard]] std::vector<std::string> getLayersIds() const;
        [[nodiscard]] TileLayer& getLayer(const std::string& id) const;
        [[nodiscard]] AnimatedTiles getAnimatedTiles() const;
        [[nodiscard]] const TilesetCollection& getTilesets() const;
        [[nodiscard]] std::vector<graphics::Renderable*> getRenderables() const;
        [[nodiscard]] std::vector<collision::PolygonalCollider*> getColliderModels() const;
        [[nodiscard]] const std::vector<vili::node>& getGameObjectsModels() const;

        [[nodiscard]] uint32_t getWidth() const;
        [[nodiscard]] uint32_t getHeight() const;
        [[nodiscard]] uint32_t getTileWidth() const;
        [[nodiscard]] uint32_t getTileHeight() const;
        [[nodiscard]] bool isSmooth() const;

        [[nodiscard]] Scene::Scene& getScene() const;
    };
}
