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

        std::vector<std::unique_ptr<TileLayer>> m_layers;
        std::vector<std::unique_ptr<AnimatedTile>> m_animatedTiles;
        std::vector<std::unique_ptr<Collision::PolygonalCollider>> m_colliderModels;
        std::vector<vili::node> m_gameObjectsModels;
        TilesetCollection m_tilesets;

        void build();

    public:
        explicit TileScene(Scene::Scene& scene);
        vili::node dump() const;
        void load(const vili::node& data) override;

        void update();
        void clear();

        TileLayer& getLayer(const std::string& id) const;
        AnimatedTiles getAnimatedTiles() const;
        const TilesetCollection& getTilesets() const;
        std::vector<Graphics::Renderable*> getRenderables() const;
        std::vector<Collision::PolygonalCollider*> getColliderModels() const;
        const std::vector<vili::node>& getGameObjectsModels() const;

        uint32_t getWidth() const;
        uint32_t getHeight() const;
        uint32_t getTileWidth() const;
        uint32_t getTileHeight() const;

        Scene::Scene& getScene() const;
    };
}
